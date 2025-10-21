#pragma once
#include <aws/core/auth/AWSCredentials.h>
#include "IJitterFactory.hpp"
namespace clog::jitter_orchestrator
{
    class AwsJitterFactory: public IJitterFactory
    {
         private:
            Aws::Client::ClientConfiguration config;
         public:   
            AwsJitterFactory();
            ~AwsJitterFactory();
            std::shared_ptr<IJitterCommand> create(const std::string& type) override = 0;
    };
};