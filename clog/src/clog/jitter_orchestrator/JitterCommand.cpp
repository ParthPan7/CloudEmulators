#include "jitter_orchestrator/JitterCommand.hpp"

namespace clog::jitter_orchestrator
{

    JitterCommand::JitterCommand(std::shared_ptr<ICongestionStrategy> congestionStrategy): _congestionStrategy(std::move(congestionStrategy))
    {

    }

    void JitterCommand::execute() const
    {
        _congestionStrategy->execute();
    } 
}
