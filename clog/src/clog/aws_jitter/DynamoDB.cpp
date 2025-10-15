#include "DynamoDB.hpp"
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/dynamodb/model/GetItemRequest.h>
#include <aws/dynamodb/model/PutItemRequest.h>

namespace clog::aws_jitter
{
    void DynamoDB::putItem(Aws::DynamoDB::DynamoDBClient& client, const Aws::String& tableName, int id) const
    {
        try 
        {
            Aws::DynamoDB::Model::PutItemRequest request;
            request.SetTableName(tableName);

            Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue> item;
            item["Id"] = Aws::DynamoDB::Model::AttributeValue(std::to_string(id));
            item["Name"] = Aws::DynamoDB::Model::AttributeValue("dummy_name" + std::to_string(id));
        
            request.SetItem(item);
            auto outcome = client.PutItem(request);
            if (outcome.IsSuccess())
            {   
                std::cout << "Order inserted successfully to dynamoDB table : " << tableName <<std::endl;
            }
            else 
            {
                std::cout << "Put Item failed to DynamoDB table : " << tableName << outcome.GetError().GetMessage() <<std::endl;
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << "Exception during PutItem :" << e.what() << std::endl;
        }
        
    }
    
    void DynamoDB::getItem(Aws::DynamoDB::DynamoDBClient& client, const Aws::String& tableName, int id) const
    {
        try
        {
            Aws::DynamoDB::Model::GetItemRequest request;
            request.SetTableName(tableName);

            Aws::Map<Aws::String, Aws::DynamoDB::Model::AttributeValue> key;
            key["Id"] = Aws::DynamoDB::Model::AttributeValue(std::to_string(id));

            request.SetKey(key);
            auto outcome = client.GetItem(request);
            if (outcome.IsSuccess())
            {
                const auto& item = outcome.GetResult().GetItem();
                if (!item.empty()) 
                {
                    std::cout << "Item retrieved successfully." << std::endl;
                } 
                else 
                {
                    std::cout << "Item not found." << std::endl;
                }
            }   
        }
        catch(const std::exception& e)
        {
            std::cerr << "Exception ocuured during retrieving item from DYnamoDB table" <<e.what() << '\n';
        }
    }    
};