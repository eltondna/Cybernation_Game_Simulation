#include "../includes/disruptionCard.hpp"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <random>

// Default constructor
disruptionCard::disruptionCard(){
    c_name = "";
    c_des = "";
    c_type = DISRUPT;
    c_cond = false;
    c_cancel = false;
}

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

// JSON constructor
disruptionCard::disruptionCard(const nlohmann::json& cardData){
    fromJson(cardData);
}

// Helper methods
bool disruptionCard::hasTileChangeEffect() const{
    for(const auto& effect : c_effect){
        if(effect.first == DISRUPTION_TURN_WASTE || effect.first == DISRUPTION_TURN_WILD || 
           effect.first == DISRUPTION_TURN_DEVA || effect.first == DISRUPTION_TURN_DEVB){
            return true;
        }
    }
    return false;
}

DISRUPTION_EFFECT disruptionCard::parseEffectString(const std::string& effectStr){
    if(effectStr == "TurnWaste") return DISRUPTION_TURN_WASTE;
    if(effectStr == "TurnWild") return DISRUPTION_TURN_WILD;
    if(effectStr == "TurnDevA") return DISRUPTION_TURN_DEVA;
    if(effectStr == "TurnDevB") return DISRUPTION_TURN_DEVB;
    if(effectStr == "Co") return DISRUPTION_CO;
    if(effectStr == "HR") return DISRUPTION_HR;
    if(effectStr == "Cy") return DISRUPTION_CY;
    if(effectStr == "Tech") return DISRUPTION_TECH;
    if(effectStr == "Env") return DISRUPTION_ENV;
    if(effectStr == "Resources") return DISRUPTION_RESOURCES;
    if(effectStr == "Token") return DISRUPTION_TOKEN;
    if(effectStr == "Trade") return DISRUPTION_TRADE;
    if(effectStr == "CapEnv") return DISRUPTION_CAP_ENV;
    if(effectStr == "IgnoreCohesionEffect") return DISRUPTION_IGNORE_COHESION_EFFECT;
    if(effectStr == "SwapGoal") return DISRUPTION_SWAP_GOAL;
    if(effectStr == "DrawGoal") return DISRUPTION_DRAW_GOAL;
    if(effectStr == "MovPpl") return DISRUPTION_MOV_PPL;
    return DISRUPTION_CO; // Default fallback
}

DISRUPTION_TYPE disruptionCard::parseTypeString(const std::string& typeStr){
    if(typeStr == "disrupt") return DISRUPT;
    if(typeStr == "boost") return BOOST;
    return DISRUPT; // Default fallback
}

disruptionCard disruptionCard::fromJson(const nlohmann::json& cardData){
    disruptionCard card;
    
    // Parse basic information
    card.c_name = cardData.value("name", "");
    card.c_des = cardData.value("description", "");
    card.c_type = parseTypeString(cardData.value("type", "disrupt"));
    card.c_cancel = cardData.value("cancel", true);
    card.c_cond = cardData.value("cond", "") != "";
    
    // Parse stackTarget or target
    if(cardData.contains("stackTarget") && cardData["stackTarget"].is_array()){
        for(const auto& targetId : cardData["stackTarget"]){
            if(targetId.is_number()){
                card.c_stackTarget.push_back(targetId.get<int>());
            }
        }
    } else if(cardData.contains("target") && cardData["target"].is_array()){
        for(const auto& targetId : cardData["target"]){
            if(targetId.is_number()){
                card.c_stackTarget.push_back(targetId.get<int>());
            }
        }
    } else if(cardData.contains("target") && cardData["target"].is_string() && cardData["target"] == "Any"){
        // If "Any", means can affect any stack, we use 1-11 for now
        for(int i = 1; i <= 11; i++){
            card.c_stackTarget.push_back(i);
        }
    }
    
    // Parse effects
    if(cardData.contains("effect") && cardData["effect"].is_array()){
        for(const auto& effect : cardData["effect"]){
            if(effect.is_string()){
                std::string effectStr = effect.get<std::string>();
                // Parse effect with value (e.g., "Co:-2", "HR:+1")
                if(effectStr.find(":") != std::string::npos){
                    std::string effectName = effectStr.substr(0, effectStr.find(":"));
                    std::string effectValue = effectStr.substr(effectStr.find(":") + 1);
                    int value = std::stoi(effectValue);
                    card.c_effect.push_back({parseEffectString(effectName), value});
                } else {
                    card.c_effect.push_back({parseEffectString(effectStr), 0});
                }
            }
        }
    }
    
    // Parse cost
    if(cardData.contains("cost") && cardData["cost"].is_array()){
        for(const auto& cost : cardData["cost"]){
            if(cost.is_string()){
                std::string costStr = cost.get<std::string>();
                if(costStr.find(":") != std::string::npos){
                    std::string costName = costStr.substr(0, costStr.find(":"));
                    std::string costValue = costStr.substr(costStr.find(":") + 1);
                    int value = std::stoi(costValue);
                    card.c_cancelCost.push_back({parseEffectString(costName), value});
                } else {
                    card.c_cancelCost.push_back({parseEffectString(costStr), 0});
                }
            }
        }
    }
    
    return card;
}

// DisruptionCardManager implementation
disruptionCardManager::disruptionCardManager(){
    deck = std::vector<disruptionCard>();
    discard = std::vector<disruptionCard>();
}

bool disruptionCardManager::loadCardsFromFile(const std::string& filename){
    try{
        std::ifstream file(filename);
        if(!file.is_open()){
            std::cerr << "Cannot open file: " << filename << std::endl;
            return false;
        }
        
        nlohmann::json jsonData;
        file >> jsonData;
        file.close();
        
        if(!jsonData.is_array()){
            std::cerr << "JSON file format error: should be array" << std::endl;
            return false;
        }
        
        // Clear existing deck
        deck.clear();
        discard.clear();
        
        // Load all cards
        int loadedCount = 0;
        for(const auto& cardData : jsonData){
            try {
                disruptionCard card = disruptionCard::fromJson(cardData);
                deck.push_back(card);
                loadedCount++;
            } catch (const std::exception& e) {
                std::cerr << "Error loading card: " << e.what() << std::endl;
            }
        }
        std::cout << "Loaded " << loadedCount << " cards from " << jsonData.size() << " total cards" << std::endl;
        
        // Shuffle deck randomly
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(deck.begin(), deck.end(), g);
        
        std::cout << "Successfully loaded " << deck.size() << " disruption cards" << std::endl;
        return true;
        
    } catch(const std::exception& e){
        std::cerr << "Failed to load disruption cards: " << e.what() << std::endl;
        return false;
    }
}

disruptionCard disruptionCardManager::drawCard(){
    if(deck.empty()){
        std::cerr << "Deck is empty, cannot draw card" << std::endl;
        return disruptionCard(); // Return empty card
    }
    
    // Draw first card
    disruptionCard drawnCard = deck.front();
    deck.erase(deck.begin());
    
    // Put into discard pile
    discard.push_back(drawnCard);
    
    return drawnCard;
}

void disruptionCardManager::reshuffle(){
    // Put all cards from discard pile back to deck
    for(const auto& card : discard){
        deck.push_back(card);
    }
    
    // Clear discard pile
    discard.clear();
    
    // Reshuffle deck
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(deck.begin(), deck.end(), g);
    
    std::cout << "Reshuffle completed, deck has " << deck.size() << " cards" << std::endl;
}

