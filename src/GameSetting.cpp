#include "../includes/GameSetting.hpp"

GameSetting::GameSetting()
{
    this->pool          = feedBackPool();
    this->parameter     = params();
    this->round         = 1;
    this->stkVector     = std::vector<stacks>();
    this->fbTokenVector = std::vector<STACK_EFFECT>();
    this->disruptionManager = disruptionCardManager();
}

GameSetting::GameSetting(feedBackPool _pool, 
                         params _parameter, int _round, 
                         std::vector<stacks> _stkVector, 
                         std::vector<STACK_EFFECT> _fbTokenVector)
{

    this->pool          = _pool;
    this->parameter     = _parameter;
    this->round         = _round;
    this->stkVector     = _stkVector;
    this->fbTokenVector = _fbTokenVector;
}

bool GameSetting::updatePool(STACK_EFFECT token, bool extract)
{
    feedBackPool tokenPool =  this->getPool();
    // ! Could Check Extract State
    if (extract)
        return tokenPool.drawFromPool(token);
    tokenPool.putBackToPool(token);
    return true;
}

bool GameSetting::updateparams(CYBER_PARAMETER p, int val)
{
    switch (p){
        case COHESION:
            this->getParameter().setCohesion(val);
            break;
        case ENVIRONMENT:
            this->getParameter().setEnvironment(val);
            break;
        case HUMAN_RELATION:
            this->getParameter().setHumanRelation(val);
            break;
        case TECHNOLOGY:
            this->getParameter().setTechnology(val);
            break;
        case CYBERNATION_LEVEL:
            this->getParameter().setCybernationLevel(val);
        default: return false;
    }
    return true;
}

void GameSetting::updateRound()
{
    ++this->round;
}
