#include "jitter_orchestrator/AwsJitterFactory.hpp"
#include "jitter_orchestrator/JitterCommand.hpp"
#include "aws_jitter/DynamoDBUploadCongestionStrategy.hpp"
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

    std::shared_ptr<IJitterCommand> AwsJitterFactory::create(const std::string& type)
    {
        if (type == "dynamoDB_upload") 
        {
            return std::make_shared<JitterCommand>(
            std::make_shared<clog::aws_jitter::DynamoDBUploadCongestionStrategy>(Aws::String("MyDemoTable"), config));
        }
        throw std::invalid_argument("Unknown jitter command type: " + type);
    }

};