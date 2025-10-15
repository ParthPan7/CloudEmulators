#include <QApplication>
#include <QLabel>
#include <aws/core/Aws.h>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListBucketsRequest.h>
#include <iostream>
#include "aws_jitter/S3.hpp"
#include "aws_jitter/S3Congestion.hpp"
#include "aws_jitter/IDynamoDB.hpp"
#include "aws_jitter/DynamoDB.hpp"
#include "aws_jitter/DynamoDBCongestion.hpp"

using namespace clog;
using namespace clog::aws_jitter;

int main(int argc, char *argv[])
{
     Aws::SDKOptions options;
     
     Aws::InitAPI(options);
     {
         Aws::S3::S3Client s3_client;
         auto outcome = s3_client.ListBuckets();
         if (outcome.IsSuccess()) {
             std::cout << "Buckets:\n";
             for (auto const &bucket : outcome.GetResult().GetBuckets()) {
                 std::cout << "  " << bucket.GetName() << std::endl;
             }
         } else {
             std::cerr << "Error listing buckets: "
                       << outcome.GetError().GetMessage() << std::endl;
         }
     }
     
    Aws::Client::ClientConfiguration config;
    config.endpointOverride = "http://localhost:4566";
    config.checksumConfig.requestChecksumCalculation = Aws::Client::RequestChecksumCalculation::WHEN_REQUIRED;
    config.checksumConfig.responseChecksumValidation = Aws::Client::ResponseChecksumValidation::WHEN_REQUIRED; 
    config.scheme = Aws::Http::Scheme::HTTP;
    config.verifySSL = false;

    std::unique_ptr<IS3> s3 = std::make_unique<S3>(config);
    std::unique_ptr<ICongestion> s3Congestion =  std::make_unique<S3Congestion>(std::move(s3));
    s3Congestion->generate();

    std::unique_ptr<IDynamoDB> dynamoDB = std::make_unique<DynamoDB>(config);
    std::unique_ptr<ICongestion> dynamoDBCongestion = std::make_unique<DynamoDBCongestion>(std::move(dynamoDB));
    dynamoDBCongestion->generate();

    QApplication app(argc, argv);
    QLabel label("Qt + AWS SDK (Windows Ready)");
    label.resize(400, 200);
    label.show();
     
    int ret = app.exec();
    Aws::ShutdownAPI(options);
    return ret;
}
