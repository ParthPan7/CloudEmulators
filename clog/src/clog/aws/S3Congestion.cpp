#include "S3Congestion.hpp"
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>

namespace clog::aws
{
    class S3Congestion : ICongestion
    {   
        public: 
            S3Congestion(std::unique_ptr<IS3> s3)
            {
                _s3 = std::move(s3);
            }

        private:
            Aws::S3::S3Client _s3Client;
            std::unique_ptr<IS3> _s3;
            void uploadFile(const Aws::String &bucketName, const std::shared_ptr<Aws::IOStream> file, const std::string fileName)
            {
                _s3->uploadS3File(bucketName, file, fileName);
            }

        protected:    
            void generate() override
            {
                Aws::String bucketName = "test-bucket";
                Aws::SDKOptions options;
                Aws::InitAPI(options);
                {                   
                    int thread_count = 10; 
                    std::vector<std::thread> threads;
                    auto start = std::chrono::steady_clock::now();
                    for (int i = 0; i < thread_count; ++i) 
                    {
                        auto data = std::make_shared<Aws::StringStream>();
                        *data << "Payload-" << i;
                        threads.emplace_back(uploadFile, bucketName, std::ref(data), "test-object-" + std::to_string(i));
                    }
                    for (auto& t : threads) t.join();
                    auto end = std::chrono::steady_clock::now();

                    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
                    std::cout << "Completed " << thread_count << " uploads in " << elapsed << "s\n";
                }
                Aws::ShutdownAPI(options);    
            }
    };
};