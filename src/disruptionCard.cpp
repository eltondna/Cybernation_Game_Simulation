#include "../includes/disruptionCard.hpp"


disruptionCard::disruptionCard(std::string name, 
                               std::string des, 
                               DISRUPTION_TYPE type, 
                               std::vector<int> stackTarget, 
                               std::vector<std::pair<DISRUPTION_EFFECT, int>> effect, 
                               std::vector<std::pair<DISRUPTION_EFFECT, int>> cancelCost, 
                               bool cond, 
                               bool cancel, 
                               std::vector<STACK_TYPE> stackCondition, 
                               std::vector<CYBER_PARAMETER> relationshipCondition) 
                               : c_name(name), c_des(des), c_type(type), c_stackTarget(stackTarget),
                                 c_effect(effect), c_cancelCost(cancelCost), c_cond(cond), c_cancel(cancel),
                                 c_stackCondition(stackCondition), c_relationshipCondition(relationshipCondition)

{
}

disruptionCard::~disruptionCard()
{
}

std::string disruptionCard::getCardName()
{
    return this->c_name;
}

std::string disruptionCard::getCardDescription(){
    return this->c_des;
}
DISRUPTION_TYPE disruptionCard::getCardDisruptionType(){
    return this->c_type;
}
std::vector<int> disruptionCard::getCardStackTarget(){
    return this->c_stackTarget;
}
std::vector<std::pair<DISRUPTION_EFFECT,int>> disruptionCard::getCardEffect(){
    return this->c_effect;
}
std::vector<std::pair<DISRUPTION_EFFECT,int>> disruptionCard:: getCancelCost(){
    return this->c_cancelCost;
}
std::vector<STACK_TYPE> disruptionCard::getStackCondition(){
    return this->c_stackCondition;
}
std::vector<CYBER_PARAMETER> disruptionCard::getRelationshipCondition(){
    return this->c_relationshipCondition;
}

