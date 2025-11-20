#include "jitter_orchestrator/AwsJitterFactory.hpp"
#include "jitter_orchestrator/JitterCommand.hpp"
#include "aws_jitter/DynamoDBUploadCongestionStrategy.hpp"
#include <aws_jitter/DynamoDBDownloadCongestionStrategy.hpp>
#include <JitterCommands.hpp>
#include <memory>
namespace clog::jitter_orchestrator
{
    
    AwsJitterFactory::AwsJitterFactory()
    {
        config.endpointOverride = "http://localhost:4566";
        config.checksumConfig.requestChecksumCalculation = Aws::Client::RequestChecksumCalculation::WHEN_REQUIRED;
        config.checksumConfig.responseChecksumValidation = Aws::Client::ResponseChecksumValidation::WHEN_REQUIRED; 
        config.scheme = Aws::Http::Scheme::HTTP;
        config.verifySSL = false;
    }

    AwsJitterFactory::~AwsJitterFactory()
    {

    }

    std::shared_ptr<IJitterCommand> AwsJitterFactory::create(const JitterCommands& command)
    {
        switch (command)
        {
            case JitterCommands::DYNAMODB_UPLOAD:
                return std::make_shared<JitterCommand>(
                    std::make_shared<clog::aws_jitter::DynamoDBUploadCongestionStrategy>(Aws::String("MyDemoTable"), config));
            case JitterCommands::DYNAMODB_DOWNLOAD:
                return std::make_shared<JitterCommand>(
                    std::make_shared<clog::aws_jitter::DynamoDBDownloadCongestionStrategy>(Aws::String("MyDemoTable"), config));

            default:
                throw std::invalid_argument("Unknown jitter command type: ");
        }        
    }

};