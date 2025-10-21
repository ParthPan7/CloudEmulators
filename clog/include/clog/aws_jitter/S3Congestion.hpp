#pragma once
#include "ICongestion.hpp"
#include "IS3.hpp"

namespace clog::aws_jitter
{
    class S3Congestion : public ICongestion
    {
        public:
            void generate() const override;
            S3Congestion(std::unique_ptr<IS3> s3);
            ~S3Congestion();
        private:
          Aws::S3::S3Client _s3Client;
          std::unique_ptr<IS3> _s3; 
          void uploadFile(const Aws::String &bucketName, const std::shared_ptr<Aws::IOStream> file, const std::string fileName) const;   
    };
};