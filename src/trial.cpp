#include <iostream>
#include "../includes/nlohmann/json.hpp"
#include <vector>
#include "../includes/disruptionCard.hpp"
#include <fstream>

using namespace std;


void initializeDisruptionCardDeck(){
    std::ifstream fs("data/disruption.json");
    nlohmann::json disruptJson = nlohmann::json::parse(fs);
    cout << disruptJson << endl;
}

int main(){
    vector<disruptionCard> disruptionCardDeck;
    initializeDisruptionCardDeck();
}





