#ifndef _GAMESETTING_HPP
#define _GAMESETTING_HPP
#include "feedBackPool.hpp"
#include "params.hpp"
#include "stack.hpp"
#include "disruptionCard.hpp"
#include <vector>

class GameSetting{
    private:
        /* ! Feedback Token Pool */
        feedBackPool              pool;
        /* ! Resources and Conflicts */
        params                    parameter;
        /* ! Number of round */
        int                       round;
        /* ! Stack */
        std::vector<stacks>       stkVector;
        /* ! FeedBack Token Bag */
        std::vector<STACK_EFFECT> fbTokenVector;
        /* ! Disruption Card Manager */
        disruptionCardManager      disruptionManager;
    public:
        GameSetting();
        GameSetting(feedBackPool _pool, 
                    params _parameter, 
                    int _round, 
                    std::vector<stacks> stkVector,
                    std::vector<STACK_EFFECT> fbTokenVector);
        ~GameSetting(){};
    
    public:
        bool                        updatePool(STACK_EFFECT token, bool extract);
        bool                        updateparams(CYBER_PARAMETER p, int val);
        void                        updateRound();

        feedBackPool &              getPool(){return pool;};
        params &                    getParameter(){return parameter;};
        int &                       getRound(){return round;};
        std::vector<stacks> &       getstkVector(){return stkVector;};
        std::vector<STACK_EFFECT> & getFbTokenVector(){return fbTokenVector;};
        disruptionCardManager &     getDisruptionManager(){return disruptionManager;};

        void setPool(feedBackPool _pool){this->pool = _pool;};
        void setParameter(params _param){this->parameter = _param;};
        void setRound(int _round){this->round = _round;};
        void setstkVector(std::vector<stacks> _stkVector){this->stkVector = _stkVector;};
        void setFbTokenVector(std::vector<STACK_EFFECT> _fbTokenVector){this->fbTokenVector = _fbTokenVector;};
};


#endif