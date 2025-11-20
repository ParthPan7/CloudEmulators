#pragma once
#include <clog/ICongestionStrategy.hpp>
#include <aws/dynamodb/DynamoDBClient.h>
#include <aws/core/Aws.h>

namespace clog::aws_jitter
{
	class DynamoDBDownloadCongestionStrategy : public ICongestionStrategy
	{
		private:
			Aws::String _tableName;
			Aws::DynamoDB::DynamoDBClient _dynamoDBClient;
		
		public:
			void execute() override;
			DynamoDBDownloadCongestionStrategy(Aws::String tableName, Aws::Client::ClientConfiguration config);
			~DynamoDBDownloadCongestionStrategy();
	};
}
