#pragma once
#include <string>
#include <vector>
#include <Aws.h>

namespace clog::aws {
    class IS3 {

    public:
        virtual void uploadS3File(const Aws::String &bucketName, const std::shared_ptr<Aws::IOStream> file, const std::string fileName);
        virtual std::vector<std::string> listS3Buckets() const;
        virtual ~IS3() = default;
    
        private:
        std::string _region_;
        std::string _endpoint;    
    };
}
