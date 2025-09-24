#ifndef _STACK_HPP
#define _STACK_HPP
#include <string>

/* ! Tile Type */ 
enum STACK_TYPE{
    STACK_WILD,
    STACK_WASTE,
    STACK_DEVA,
    STACK_DEVB
};

/* ! Feedback Token Effect */
enum STACK_EFFECT{
    EFFECT_TURN_WILD,
    EFFECT_LOSE_CO,
    EFFECT_TURN_WASTE,
    EFFECT_SOLVE_DISRUPT
}; 


class stacks{
    private:
        int             position;
        STACK_TYPE      type;
        STACK_EFFECT    effect;
    public:
        stacks(STACK_TYPE type, int position);
        std::string     toString();
        int             getPosition();
        STACK_TYPE      getType();
        STACK_EFFECT    getEffect();
        void            setType(STACK_TYPE type);
        
};

STACK_TYPE 
stacks::getType()
{
    return this->type;
}

inline STACK_EFFECT stacks::getEffect()
{
    return this->effect;
}

inline void stacks::setType(STACK_TYPE type)
{   
    this->type = type;
    switch (this->type){
        case STACK_WILD:
            this->effect = EFFECT_TURN_WILD;
            break;
        case STACK_WASTE:
            this->effect = EFFECT_LOSE_CO;
            break;
        case STACK_DEVA:
            this->effect = EFFECT_TURN_WASTE;
            break;
        case STACK_DEVB:
            this->effect = EFFECT_SOLVE_DISRUPT;
            break;
    }
}

inline stacks::stacks(STACK_TYPE type, int position)
{
    this->type     = type;
    this->position = position;
    switch (this->type){
        case STACK_WILD:
            this->effect = EFFECT_TURN_WILD;
            break;
        case STACK_WASTE:
            this->effect = EFFECT_LOSE_CO;
            break;
        case STACK_DEVA:
            this->effect = EFFECT_TURN_WASTE;
            break;
        case STACK_DEVB:
            this->effect = EFFECT_SOLVE_DISRUPT;
            break;
    }
}

std::string
stacks::toString()
{
    switch (this->type){
        case STACK_WILD:
            return "WILD";
            break;
        case STACK_WASTE:
            return "WASTE";
            break;
        case STACK_DEVA:
            return "DEVA";
            break;
        case STACK_DEVB:
            return "DEVB";
            break;
    }
    return "";   
}

inline int stacks::getPosition()
{
    return this->position;
}

#endif