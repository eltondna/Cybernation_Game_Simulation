#include "GameSetting.hpp"

GameSetting::GameSetting()
{
    this->pool      = feedBackPool();
    this->parameter = params();
    this->round     = 1;
}

GameSetting::GameSetting(feedBackPool _pool, params _parameter, int _round)
{
    this->pool          = _pool;
    this->parameter     = _parameter;
    this->round         = _round;
}
