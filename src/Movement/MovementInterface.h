#pragma once

class MovementInterface
{
    public:
        void virtual init() = 0;
        void virtual run(int32_t value) = 0;
};