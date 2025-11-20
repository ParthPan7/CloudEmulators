#include <aws_jitter/DynamoDBDownloadCongestionStrategy.hpp>
#include <iostream>
#include <aws/dynamodb/model/GetItemRequest.h>
#include <aws/dynamodb/model/PutItemRequest.h>
namespace clog::aws_jitter
{
	DynamoDBDownloadCongestionStrategy::DynamoDBDownloadCongestionStrategy(Aws::String tableName, Aws::Client::ClientConfiguration config):
	_tableName(std::move(tableName)), _dynamoDBClient(Aws::Auth::AWSCredentials(Aws::String("test"),Aws::String("test")), config)
	{}

	DynamoDBDownloadCongestionStrategy::~DynamoDBDownloadCongestionStrategy() {}

    void DynamoDBDownloadCongestionStrategy::execute()
    {
        std::cout << "[DynamoDB] Upload to table : " << _tableName << std::endl;
        try
        {
            Aws::DynamoDB::Model::GetItemRequest request;
            request.SetTableName(_tableName);
            request.AddKey("id", Aws::DynamoDB::Model::AttributeValue(std::to_string(1)));
            auto outcome = _dynamoDBClient.GetItem(request);
            if (outcome.IsSuccess())
            {
                const auto& item = outcome.GetResult().GetItem();
                if (!item.empty())
                {
                    std::cout << "Read timestamp " << std::time(nullptr) << ":\n";
                    for (const auto& field : item)
                    {
                        if (field.second.GetS().size() > 0)
                            std::cout << field.first << ": " << field.second.GetS() << std::endl;
                        else if (field.second.GetN().size() > 0)
                            std::cout << field.first << ": " << field.second.GetN() << std::endl;
                    }
                }
                else
                {
                    std::cerr << "Read failed: "
                        << outcome.GetError().GetMessage() << std::endl;
                }
            }

        }
        catch (const std::exception& e)
        {
            std::cerr << "Exception during GetItem :" << e.what() << std::endl;
        }
    }
};