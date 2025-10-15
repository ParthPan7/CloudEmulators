#pragma once 
#include "IDynamoDB.hpp"
#include <aws/core/Aws.h>

namespace clog::aws_jitter
{
    class DynamoDB : public IDynamoDB
    {
        public:
            void putItem(const Aws::String& tableName, int id) const override;
            void getItem(const Aws::String& tableName, int id) const override;
            ~DynamoDB();
            DynamoDB(Aws::Client::ClientConfiguration config);

        private:
            Aws::DynamoDB::DynamoDBClient _dynamoDBClient;
    };
};