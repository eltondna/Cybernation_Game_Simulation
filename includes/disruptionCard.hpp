#ifndef _DISRUPTION_CARD_HPP
#define _DISRUPTION_CARD_HPP
#include <string>
#include <vector>
#include "stack.hpp"
#include "params.hpp"

enum DISRUPTION_TYPE{
    DISRUPT,
    BOOST
};

enum DISRUPTION_EFFECT{
    // ! Stack
    TurnWaste,
    TurnWild,
    TurnDevA,
    TurnDevB,

    // ! Resources
    Co, 
    HR,
    Cy,
    Tech,
    Env,
    Resources,
    Token,
    Trade,

    // ! Rule
    CapEnv,
    IgnoreCohesionEffect,
    
    // ! Metadata
    SwapGoal,
    DrawGoal,
    MovPpl

};

class disruptionCard{
private:
    std::string c_name;
    std::string c_des;
    DISRUPTION_TYPE c_type;

    std::vector<int> c_stackTarget;
    std::vector<std::pair<DISRUPTION_EFFECT,int>> c_effect;
    std::vector<std::pair<DISRUPTION_EFFECT,int>> c_cancelCost;

    std::vector<STACK_TYPE> c_stackCondition;
    std::vector<CYBER_PARAMETER> c_relationshipCondition;
    
    bool c_cond;
    bool c_cancel;

public:
    disruptionCard(std::string name, std::string des, DISRUPTION_TYPE type, 
                   std::vector<int> stackTarget, 
                   std::vector<std::pair<DISRUPTION_EFFECT,int>> effect,
                   std::vector<std::pair<DISRUPTION_EFFECT,int>> cancelCost,
                   bool cond, 
                   bool cancel,
                   std::vector<STACK_TYPE> stackCondition,
                   std::vector<CYBER_PARAMETER> relationshipCondition);
    ~disruptionCard();;

    // ! Only Getter is needed
    std::string                                     getCardName();
    std::string                                     getCardDescription();
    DISRUPTION_TYPE                                 getCardDisruptionType();
    std::vector<int>                                getCardStackTarget();
    std::vector<std::pair<DISRUPTION_EFFECT,int>>   getCardEffect();
    std::vector<std::pair<DISRUPTION_EFFECT,int>>   getCancelCost();
    std::vector<STACK_TYPE>                         getStackCondition();
    std::vector<CYBER_PARAMETER>                    getRelationshipCondition();

};





#endif