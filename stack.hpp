#ifndef STACK_H
#define STACK_H
#include <string>

enum STACK_TYPE{
    WILD,
    WASTE,
    DEVA,
    DEVB
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