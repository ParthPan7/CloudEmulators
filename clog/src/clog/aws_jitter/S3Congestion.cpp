#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>
#include <iostream>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include "aws_jitter/IS3.hpp"
#include "aws_jitter/S3Congestion.hpp"

namespace clog::aws_jitter
{
      
         
            S3Congestion::S3Congestion(std::unique_ptr<IS3> s3)
            {
                _s3 = std::move(s3);
            }

            S3Congestion::~S3Congestion()
            {
            }

            void S3Congestion::uploadFile(const Aws::String &bucketName, const std::shared_ptr<Aws::IOStream> file, const std::string fileName) const
            {
                _s3->uploadS3File(bucketName, file, fileName);
            }
    
            void S3Congestion::generate() const
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
                        threads.emplace_back([this, bucketName, data, i]() {
                            uploadFile(bucketName, data, "test-object-" + std::to_string(i));
                        });
                    }
                    for (auto& t : threads) t.join();
                    auto end = std::chrono::steady_clock::now();

                    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
                    std::cout << "Completed " << thread_count << " uploads in " << elapsed << "s\n";
                }
                Aws::ShutdownAPI(options);    
            }
    
};