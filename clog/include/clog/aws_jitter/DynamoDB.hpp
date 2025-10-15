#pragma once 
#include "IDynamoDB.hpp"

namespace clog::aws_jitter
{
    class DynamoDB : public IDynamoDB
    {
        void putItem(Aws::DynamoDB::DynamoDBClient& client, const Aws::String& tableName, int id) const override;
        void getItem(Aws::DynamoDB::DynamoDBClient& client, const Aws::String& tableName, int id) const override;
        ~DynamoDB();
    };
};