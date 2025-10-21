#pragma once

namespace clog
{
    class ICongestionStrategy
    {
        public:
            virtual void execute() = 0; 
            virtual ~ICongestionStrategy() = default;
    };
};



