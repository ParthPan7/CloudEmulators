#include "aws_jitter/DynamoDBUploadCongestionStrategy.hpp"
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/GetItemRequest.h>
#include <aws/dynamodb/model/PutItemRequest.h>
namespace clog::aws_jitter
{
    std::atomic<int> DynamoDBUploadCongestionStrategy::_id{0};

    DynamoDBUploadCongestionStrategy::DynamoDBUploadCongestionStrategy(Aws::String tableName, Aws::Client::ClientConfiguration config) : 
    _tableName(std::move(tableName)), _dynamoDBClient(Aws::Auth::AWSCredentials(Aws::String("test"), Aws::String("test")), config)
    {
        
    }

    int DynamoDBUploadCongestionStrategy::getNextItemId() 
    {
        return _id.fetch_add(1, std::memory_order_relaxed);
    }

    void DynamoDBUploadCongestionStrategy::execute()
    {
        int id = getNextItemId();
        std::cout << "[DynamoDB] Upload to table : " << _tableName<< std::endl;
        try 
        {
            Aws::DynamoDB::Model::PutItemRequest request;
            request.SetTableName(_tableName);
            std::string dummy_name_prefix = "dummy_name";
            Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue> item;
            item["id"] = Aws::DynamoDB::Model::AttributeValue(std::to_string(id));
            item["name"] = Aws::DynamoDB::Model::AttributeValue(dummy_name_prefix.append(std::to_string(id)));
        
            request.SetItem(item);
            auto outcome = _dynamoDBClient.PutItem(request);
            if (outcome.IsSuccess())
            {   
                std::cout << "Order inserted successfully to dynamoDB table : " << _tableName <<std::endl;
            }
            else 
            {
                std::cout << "Put Item failed to DynamoDB table : " << _tableName << outcome.GetError().GetMessage() <<std::endl;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Exception during PutItem :" << e.what() << std::endl;
        }
    }

};