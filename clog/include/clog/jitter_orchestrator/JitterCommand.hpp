#pragma once
#include "ICongestionStrategy.hpp"
#include "IJitterCommand.hpp"
#include <memory>
namespace clog::jitter_orchestrator
{
    class JitterCommand : public IJitterCommand
    {
        private:
             std::shared_ptr<ICongestionStrategy> _congestionStrategy;    
        public:
            JitterCommand(std::shared_ptr<ICongestionStrategy> congestionStrategy);
            void execute() const override; 

    };
}
