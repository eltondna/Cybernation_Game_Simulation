#include "../includes/stack.hpp"


STACK_TYPE 
stacks::getType()
{
    return this->type;
}


void stacks::setType(STACK_TYPE type)
{   
    this->type = type;
}

STACK_EFFECT stacks::getEffect()
{
    switch (this->type){
        case STACK_WILD:
            return STACK_EFFECT::EFFECT_TURN_WILD;
            break;
        case STACK_WASTE:
            return STACK_EFFECT::EFFECT_LOSE_CO;
            break;
        case STACK_DEVA:
            return STACK_EFFECT::EFFECT_TURN_WASTE;
            break;
        case STACK_DEVB:
            return STACK_EFFECT::EFFECT_SOLVE_DISRUPT;
            break;
        default:
            return STACK_EFFECT::EFFECT_UNKNOWM;
    }
}

stacks::stacks(STACK_TYPE type, int position)
{
    this->type     = type;
    this->position = position;
}

std::string
stacks::toString()
{
    switch (this->type){
        case STACK_WILD:
            return "WILD";
        case STACK_WASTE:
            return "WASTE";
        case STACK_DEVA:
            return "DEVA";
        case STACK_DEVB:
            return "DEVB";
        default:
            return "UNKNOWN";
    }
}

void stacks::setPosition(int pos)
{
    this->position = pos;
}

int stacks::getPosition()
{
    return this->position;
}