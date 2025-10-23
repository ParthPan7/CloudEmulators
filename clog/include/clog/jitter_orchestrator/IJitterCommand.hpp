#pragma once
#include "ICongestionStrategy.hpp"
#include <memory>
namespace clog::jitter_orchestrator
{
    class IJitterCommand 
    {
        private:
             std::shared_ptr<ICongestionStrategy> _congestionStrategy;    
        public:
            virtual ~IJitterCommand() = default;
            virtual void execute() const = 0; 
    };
}
