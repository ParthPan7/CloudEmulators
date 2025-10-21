#pragma once
#include <memory>
#include "IJitterCommand.hpp"
namespace clog::jitter_orchestrator
{
    class Scheduler 
    {
        public:
         void addTask(std::shared_ptr<IJitterCommand> command, int intervalSec);
         void start();
         void stop();
    };
};