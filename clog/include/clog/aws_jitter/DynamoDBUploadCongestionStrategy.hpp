#pragma once
#include "ICongestionStrategy.hpp"
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/core/Aws.h>

namespace clog::aws_jitter
{
    class DynamoDBUploadCongestionStrategy : public ICongestionStrategy
    {
        private:
            Aws::String _tableName;
            static std::atomic<int> _id;
            Aws::DynamoDB::DynamoDBClient _dynamoDBClient;
            int getNextItemId();
        public:
            void execute() override;
            DynamoDBUploadCongestionStrategy(Aws::String tableName, Aws::Client::ClientConfiguration config);
            ~DynamoDBUploadCongestionStrategy();
    };    
}
