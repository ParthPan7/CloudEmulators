#pragma once
#include <string>
#include <vector>
#include <aws/core/Aws.h>

namespace clog::aws_jitter {
    class IS3 {

    public:
        virtual void uploadS3File(const Aws::String &bucketName, const std::shared_ptr<Aws::IOStream> file, const std::string fileName) const=0;
        virtual std::vector<std::string> listS3Buckets() const=0;
        virtual ~IS3() = default;
    
        private:
        std::string _region_;
        std::string _endpoint;    
    };
}
