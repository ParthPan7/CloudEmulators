#include <QApplication>
#include <QLabel>
#include <aws/core/Aws.h>
#include <aws/s3/S3Client.h>
#include <aws/s3/model/ListBucketsRequest.h>
#include <iostream>
#include <jitter_orchestrator/Scheduler.hpp>
#include "jitter_orchestrator/IJitterFactory.hpp"
#include "jitter_orchestrator/AwsJitterFactory.hpp"
#include "aws_jitter/S3.hpp"
#include "aws_jitter/S3Congestion.hpp"
#include "aws_jitter/IDynamoDB.hpp"
#include "aws_jitter/DynamoDB.hpp"
#include "aws_jitter/DynamoDBCongestion.hpp"
#include "JitterCommands.hpp"

using namespace clog;
using namespace clog::aws_jitter;
using namespace clog::jitter_orchestrator;
int main(int argc, char *argv[])
{
     Aws::SDKOptions options;
     
     Aws::InitAPI(options);
     {
      
     }
     
    std::unique_ptr<IJitterFactory> awsResourceAllocFactory = std::make_unique<AwsJitterFactory>();
    if (awsResourceAllocFactory == nullptr) { std::cout << "AWS Resource Alloc. Factory has failed.."; }
    std::shared_ptr<IJitterCommand> dynamoDBUploadPutCmd = awsResourceAllocFactory->create(JitterCommands::DYNAMODB_UPLOAD);
    Scheduler scheduler;
    scheduler.addTask(dynamoDBUploadPutCmd, 10);
    std::shared_ptr<IJitterCommand> dynamoDBDownloadGetCmd = awsResourceAllocFactory->create(JitterCommands::DYNAMODB_DOWNLOAD);
    scheduler.addTask(dynamoDBDownloadGetCmd, 10);
    scheduler.start();

    std::this_thread::sleep_for(std::chrono::minutes(1));
    std::cout << " scheduler stopping now...";
    scheduler.stop();
    QApplication app(argc, argv);
    QLabel label("Qt + AWS SDK (Windows Ready)");
    label.resize(400, 200);
    label.show();
     
    int ret = app.exec();
    Aws::ShutdownAPI(options);
    return ret;
}
