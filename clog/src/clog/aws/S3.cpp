#include "S3.hpp"
#include "IS3.hpp"
#include "ICongestion.hpp"
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/PutObjectRequest.h>

namespace clog::aws
{
  class S3: public IS3
  {
        private:
            Aws::S3::S3Client _s3Client;

        public: 
            S3(Aws::Client::ClientConfiguration config)
            {
                _s3Client = Aws::S3::S3Client(config);
            }

        protected:    
            void uploadS3File(const Aws::String &bucketName, const std::shared_ptr<Aws::IOStream> file, const std::string fileName) override
            {
                Aws::S3::Model::PutObjectRequest request;
                request.SetBucket(bucketName);
                request.SetKey(fileName);
                request.SetBody(file);

                auto outcome  = _s3Client.PutObject(request);
                if(outcome.IsSuccess())
                {
                    std::cout << "file " << fileName << " is uploaded to bucket : " << bucketName << std::endl;
                }
                else
                {
                    std::cout << "error uploading file " << fileName << std::endl;
                }
            }
  };  
};
