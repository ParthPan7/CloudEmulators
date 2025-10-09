#pragma once
#include <string>
#include <vector>

namespace awsclogger {
    class IS3Congestion{
    public:
        virtual void uploadS3File(const std::string &bucketName, const std::string filePath);
        virtual std::vector<std::string> listS3Buckets() const;
        virtual ~IS3Congestion() = 0;
    private:
        std::string region_;
        std::string endpoint_;    
    };
}
