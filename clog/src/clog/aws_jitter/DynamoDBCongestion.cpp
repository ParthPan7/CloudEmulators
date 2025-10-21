#include "aws_jitter/DynamoDBCongestion.hpp"

namespace clog::aws_jitter
{
    DynamoDBCongestion::DynamoDBCongestion(std::unique_ptr<IDynamoDB> dynamoDB)
    {
        _dynamoDB = std::move(dynamoDB);
    }

    DynamoDBCongestion::~DynamoDBCongestion() {}
    
    void DynamoDBCongestion::putItem(const Aws::String& tableName, int id) const
    {
        _dynamoDB->putItem(tableName, id);
    }

    void DynamoDBCongestion::getItem(const Aws::String& tableName, int id) const
    {
        _dynamoDB->getItem(tableName, id);
    }

    void DynamoDBCongestion::generateUploadCongestion() const
    {
        Aws::SDKOptions options;
        Aws::InitAPI(options);
        {
            Aws::Client::ClientConfiguration config;
            Aws::String tableName = "MyDemoTable";

            int threads = 10; // concurrent inserts
            std::vector<std::thread> workers;

            auto start = std::chrono::steady_clock::now();
            for (int i = 0; i < threads; ++i) 
            {
                workers.emplace_back([this, tableName, i](){
                    putItem(tableName, i);
                });
            }

            for (auto& t : workers) t.join();

            auto end = std::chrono::steady_clock::now();
            auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();
            std::cout << "Completed " << threads << " inserts in " << elapsed << "s\n";
        }
        Aws::ShutdownAPI(options);        
    }

    void DynamoDBCongestion::generateDownloadCongestion() const 
    {

    }

    void DynamoDBCongestion::generate() const
    {
        generateUploadCongestion();
    }
};
