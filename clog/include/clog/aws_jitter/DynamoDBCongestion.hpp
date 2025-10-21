#include "ICongestion.hpp"
#include "IDynamoDB.hpp"

namespace clog::aws_jitter
{
    class DynamoDBCongestion : public ICongestion
    {
         public:
            void generate() const override;
            DynamoDBCongestion(std::unique_ptr<IDynamoDB> dynamoDB);
            ~DynamoDBCongestion();
        private:
            std::unique_ptr<IDynamoDB> _dynamoDB;
            void putItem(const Aws::String& tableName, int id) const;  
            void getItem(const Aws::String& tableName, int id) const;
            void generateUploadCongestion() const;
            void generateDownloadCongestion() const;
    };    
};