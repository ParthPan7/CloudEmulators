#include "aws_jitter/S3.hpp"
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/core/auth/AWSCredentials.h>
#include <aws/s3/model/PutObjectRequest.h>

namespace clog::aws_jitter
{
   
            S3::S3(Aws::Client::ClientConfiguration config)
            {
                Aws::Auth::AWSCredentials creds(Aws::String("test"), Aws::String("test"));
                _s3Client = Aws::S3::S3Client(creds, config,
                Aws::Client::AWSAuthV4Signer::PayloadSigningPolicy::Always, 
                false );
            }
            
            S3::~S3()
            {

            }

            std::vector<std::string> S3::listS3Buckets() const{

            }
            void S3::uploadS3File(const Aws::String &bucketName, const std::shared_ptr<Aws::IOStream> file, const std::string fileName) const
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
