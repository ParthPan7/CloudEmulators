#pragma once
#include <string>
#include <vector>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include "IS3.hpp"
namespace clog::aws_jitter {
    class S3 : public IS3 {
        private:
              Aws::S3::S3Client _s3Client;
        public:
            void uploadS3File(const Aws::String &bucketName, const std::shared_ptr<Aws::IOStream> file, const std::string fileName) const override;
            std::vector<std::string> listS3Buckets() const override;
            S3(Aws::Client::ClientConfiguration config);
            ~S3();

        private:
            std::string _region_;
            std::string _endpoint;    
    };
}