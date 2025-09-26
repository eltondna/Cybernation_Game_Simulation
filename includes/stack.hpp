#ifndef _STACK_HPP
#define _STACK_HPP
#include <string>
#include "feedBackPool.hpp"

/* ! Tile Type */ 
enum STACK_TYPE{
    STACK_WILD,
    STACK_WASTE,
    STACK_DEVA,
    STACK_DEVB,
    STACK_UNKNOWN
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


#endif