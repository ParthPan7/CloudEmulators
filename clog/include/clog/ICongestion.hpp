#pragma once 

namespace clog
{
    class ICongestion
    {
        public:
            virtual void generate() const = 0;
            virtual ~ICongestion() = default;
    };
};
