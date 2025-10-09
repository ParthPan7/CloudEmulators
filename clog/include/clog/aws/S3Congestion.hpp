#pragma once
#include "ICongestion.hpp"
#include "IS3.hpp"

namespace clog::aws
{
    class S3Congestion : public ICongestion
    {
        public:
            void generate() override;
            S3Congestion(std::unique_ptr<IS3> s3);
            ~S3Congestion();
    };
};