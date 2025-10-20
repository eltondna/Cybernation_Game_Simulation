#ifndef _DISRUPTION_CARD_HPP
#define _DISRUPTION_CARD_HPP
#include <string>
#include <vector>
#include "stack.hpp"
#include "params.hpp"
#include "nlohmann/json.hpp"

enum DISRUPTION_TYPE{
    DISRUPT,
    BOOST
};

enum DISRUPTION_EFFECT{
    // ! Stack
    DISRUPTION_TURN_WASTE,
    DISRUPTION_TURN_WILD,
    DISRUPTION_TURN_DEVA,
    DISRUPTION_TURN_DEVB,

    // ! Resources
    DISRUPTION_CO, 
    DISRUPTION_HR,
    DISRUPTION_CY,
    DISRUPTION_TECH,
    DISRUPTION_ENV,
    DISRUPTION_RESOURCES,
    DISRUPTION_TOKEN,
    DISRUPTION_TRADE,

    // ! Rule
    DISRUPTION_CAP_ENV,
    DISRUPTION_IGNORE_COHESION_EFFECT,
    
    // ! Metadata
    DISRUPTION_SWAP_GOAL,
    DISRUPTION_DRAW_GOAL,
    DISRUPTION_MOV_PPL

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
    // Default constructor
    disruptionCard();
    
    disruptionCard(std::string name, std::string des, DISRUPTION_TYPE type, 
                   std::vector<int> stackTarget, 
                   std::vector<std::pair<DISRUPTION_EFFECT,int>> effect,
                   std::vector<std::pair<DISRUPTION_EFFECT,int>> cancelCost,
                   bool cond, 
                   bool cancel,
                   std::vector<STACK_TYPE> stackCondition,
                   std::vector<CYBER_PARAMETER> relationshipCondition);
    
    // JSON constructor
    disruptionCard(const nlohmann::json& cardData);
    
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

    // Helper methods
    bool hasTileChangeEffect() const;
    static DISRUPTION_EFFECT parseEffectString(const std::string& effectStr);
    static DISRUPTION_TYPE parseTypeString(const std::string& typeStr);
    static disruptionCard fromJson(const nlohmann::json& cardData);





};

// Disruption card manager class
class disruptionCardManager{
private:
    std::vector<disruptionCard> deck;      // Card deck
    std::vector<disruptionCard> discard;   // Discard pile
    
public:
    disruptionCardManager();
    ~disruptionCardManager(){};
    
    // Load all cards from JSON file
    bool loadCardsFromFile(const std::string& filename);
    
    // Draw a card (remove from deck, put into discard pile)
    disruptionCard drawCard();
    
    // Check if deck is empty
    bool isDeckEmpty() const {return deck.empty();};
    
    // Get remaining deck size
    int getDeckSize() const {return deck.size();};
    
    // Get discard pile size
    int getDiscardSize() const {return discard.size();};
    
    // Reshuffle (put discard pile back to deck)
    void reshuffle();
};

#endif