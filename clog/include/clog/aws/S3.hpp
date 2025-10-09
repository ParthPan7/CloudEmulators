#pragma once
#include <string>
#include <vector>
#include <Aws.h>
#include "IS3.hpp"
namespace clog::aws {
    class S3 : public IS3 {
    
        public:
            void uploadS3File(const Aws::String &bucketName, const std::shared_ptr<Aws::IOStream> file, const std::string fileName) override;
            std::vector<std::string> listS3Buckets() const override;
            S3(Aws::Client::ClientConfiguration config);
            ~S3();

        private:
            std::string _region_;
            std::string _endpoint;    
    };
}