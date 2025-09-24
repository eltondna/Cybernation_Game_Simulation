#ifndef _STACK_HPP
#define _STACK_HPP
#include <string>

/* ! Tile Type */ 
enum STACK_TYPE{
    STACK_WILD,
    STACK_WASTE,
    STACK_DEVA,
    STACK_DEVB,
    STACK_UNKNOWN
};

/* ! Feedback Token Effect */
enum STACK_EFFECT{
    EFFECT_TURN_WILD,
    EFFECT_LOSE_CO,
    EFFECT_TURN_WASTE,
    EFFECT_SOLVE_DISRUPT,
    EFFECT_UNKNOWM
}; 



class stacks{
    private:
        STACK_TYPE      type;
        int             position;

    public:
        stacks(STACK_TYPE type, int position);
        std::string     toString();
        
        void            setPosition(int pos);
        int             getPosition();
 
        STACK_TYPE      getType();
        void            setType(STACK_TYPE type);


        STACK_EFFECT    getEffect();
};

STACK_TYPE 
stacks::getType()
{
    return this->type;
}


inline void stacks::setType(STACK_TYPE type)
{   
    this->type = type;
}

inline STACK_EFFECT stacks::getEffect()
{
    switch (this->type){
        case STACK_WILD:
            return EFFECT_TURN_WILD;
            break;
        case STACK_WASTE:
            return EFFECT_LOSE_CO;
            break;
        case STACK_DEVA:
            return EFFECT_TURN_WASTE;
            break;
        case STACK_DEVB:
            return EFFECT_SOLVE_DISRUPT;
            break;
        default:
            return EFFECT_UNKNOWM;
    }
}

inline stacks::stacks(STACK_TYPE type, int position)
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

inline void stacks::setPosition(int pos)
{
    this->position = pos;
}

inline int stacks::getPosition()
{
    return this->position;
}

#endif