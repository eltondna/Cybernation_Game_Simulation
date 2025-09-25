#ifndef _GAMESETTING_HPP
#define _GAME_SETTING_HPP
#include "feedBackPool.hpp"
#include "params.hpp"

class GameSetting{
    private:
        /* ! Feedback Token Pool (Bag)*/
        feedBackPool pool;
        /* ! Resources and Conflicts */
        params       parameter;
        /* ! Number of round */
        int          round;

    public:
        GameSetting();
        GameSetting(feedBackPool _pool, params _parameter, int _round);
        ~GameSetting();

        bool updatePool(STACK_EFFECT token, bool extract);
        bool updateparams(CYBER_PARAMETER p, int val, bool increment);
        bool updateRound();
};


#endif