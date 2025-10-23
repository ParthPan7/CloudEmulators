#pragma once
#include<iostream>
#include <memory>
#include "IJitterCommand.hpp"
namespace clog::jitter_orchestrator
{
    class IJitterFactory
    {   
        public:
            virtual ~IJitterFactory() = default;
            virtual std::shared_ptr<IJitterCommand> create(const std::string& congestionType) = 0;
    };
};