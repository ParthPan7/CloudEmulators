#pragma once
#include <aws/core/Aws.h>
#include <aws/dynamodb/DynamoDBClient.h>

namespace clog::aws_jitter
{
    class IDynamoDB
    {
        public:
         virtual void putItem(const Aws::String& tableName, int id) const=0;
         virtual void getItem(const Aws::String& tableName, int id) const=0;
         virtual ~IDynamoDB()=default;
    };
}; 