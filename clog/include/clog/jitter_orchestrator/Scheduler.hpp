#pragma once
#include <memory>
#include "IJitterCommand.hpp"
#include <thread>
#include <mutex>
#include <atomic>
#include <vector>

namespace clog::jitter_orchestrator
{
    class Scheduler 
    {
        public:
         void addTask(std::shared_ptr<IJitterCommand> command, int intervalSec);
         void start();
         void stop();

        private:
            struct Task
            {
                std::shared_ptr<IJitterCommand> command;
                int intervalSec = 0;
                std::thread worker;
                std::atomic<bool> running{ false };
            };

            std::vector<std::shared_ptr<Task>> _tasks;
            std::atomic<bool> _schedulerRunning{ false };
            std::mutex _taskMutex;
    };
};