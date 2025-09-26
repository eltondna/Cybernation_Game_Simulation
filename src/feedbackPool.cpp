#include "../includes/feedBackPool.hpp"

bool feedBackPool::drawFromPool(STACK_EFFECT token)
{
    switch (token){
        case EFFECT_TURN_WILD:
            if (TurnWildToken > 0){
                --TurnWildToken;
                return true;
            }
            break;
        case EFFECT_LOSE_CO:
            if (LoseCohToken > 0){
                --LoseCohToken;
                return true;
            }
            break;
        case EFFECT_TURN_WASTE:
            if (TurnWasteToken > 0){
                --TurnWasteToken;
                return true;
            }
            break;
        case EFFECT_SOLVE_DISRUPT:
            if (SolveDisruptToken > 0){
                --SolveDisruptToken;
                return true;
            }
            break;
        default: break;
    }
    return false;
}

void feedBackPool::putBackToPool(STACK_EFFECT token)
{
    switch (token){
        case EFFECT_TURN_WILD:
            ++TurnWildToken;
            break;
        case EFFECT_LOSE_CO:
            ++LoseCohToken;
            break;
        case EFFECT_TURN_WASTE:
            ++TurnWasteToken;
            break;
        case EFFECT_SOLVE_DISRUPT:
            ++SolveDisruptToken;
            break;
    }
}