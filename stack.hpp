#ifndef _STACK_HPP
#define _STACK_HPP
#include "include.hpp"

/* ! Tile Type */ 
enum STACK_TYPE{
    WILD,
    WASTE,
    DEVA,
    DEVB
};

/* ! Feedback Token Effect */
enum STACK_EFFECT{
    TURN_WILD,
    LOSE_CO,
    TURN_WASTE,
    SOLVE_DISRUPT
}; 


class stacks{
    private:
        STACK_TYPE type;
    public:
        stacks(STACK_TYPE type){this->type = type;}
        std::string toString(){
            {
            switch (this->type){
                case WILD:
                    return "WILD";
                    break;
                case WASTE:
                    return "WASTE";
                    break;
                case DEVA:
                    return "DEVA";
                    break;
                case DEVB:
                    return "DEVB";
                    break;
            }
            return "";
        }
        }
};

#endif