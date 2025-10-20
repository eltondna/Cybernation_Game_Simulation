#include "../includes/include.hpp"


using namespace std;


/* PARAMETER */
const int MAX_ROUND = 50;
int VERSION   = 1;


/* Terminal Display */
void menu(GameSetting & GameResources);
void GamePlayDisplay(GameSetting & GameResource, int roundNum);

/* Interface Function */

/* Simulation Function */
void  run_simulation(GameSetting & GameResources);
void  createDefaultStack(vector<stacks> & stkVector, vector<STACK_EFFECT> & fbTokenVector);
void  equipFeedbackToken(vector<stacks> & stkVector, vector<STACK_EFFECT> & fbTokenVector, string input);

/* Helper Function */
void  handle_effect(int stackNo, GameSetting & GameResources, STACK_EFFECT effect);
void  handleDisruptionCard(int stackNo, GameSetting & GameResources);
int   randStackSelction(vector<stacks> & stk);
void  TurnWaste(int turn, vector<stacks> & stk);
void  TurnWild(int turn, vector<stacks> & stk);
void  OutputToJson(int & version, int & currentRound, GameSetting GameResource);


/* Debug Function */
ostream & operator << 
(ostream & os, STACK_EFFECT effect){
    switch (effect){
        case EFFECT_TURN_WILD:
            return os << "(Wild)";
        case EFFECT_LOSE_CO:
            return os << "(Co-2)";
        case EFFECT_TURN_WASTE:
            return os << "(Wast)";
        case EFFECT_SOLVE_DISRUPT:
            return os << "(Dspt)";
        default:    
            return os << "(UNKNOWN)";
    }
}

int 
main(int argc, char* argv[]){
    /* Game Resources */ 
    GameSetting          GameResources = GameSetting();

    while (true){
        menu(GameResources);
        run_simulation(GameResources);
        cout << "Press any key to simulate again" << endl;
        cout << "Press q to quit" << endl;

        if (tolower(cin.get()) == 'q')
            break;
        cin.get();
    }
}

void 
menu(GameSetting & GameResources){
    try{
        // 0. Get Version
        cout << "Please select version:" << endl;
        cout << "1 - Version 1 (Basic version)" << endl;
        cout << "2 - Version 2 (With disruption cards)" << endl;
        cout << "Enter version number (1 or 2): ";
        
        string versionInput;
        getline(cin, versionInput);
        
        try{
            int version = stoi(versionInput);
            if (version == 2){
                VERSION = 2;
                cout << "Version 2 selected - With disruption cards enabled" << endl;
                // Load disruption cards
                if (!GameResources.getDisruptionManager().loadCardsFromFile("data/disruption.json")){
                    cout << "Warning: Failed to load disruption cards, using Version 1 mode" << endl;
                    VERSION = 1;
                }
            } else {
                VERSION = 1;
                cout << "Version 1 selected - Basic version" << endl;
            }
        } catch (const std::exception& e){
            cout << "Invalid input, using default version 1" << endl;
            VERSION = 1;
        }
        
        // 1. Get TILEs Type
        cout << "Version " << VERSION << " Simulation" << endl;
        cout << "Please Enter Stack type in order (1 : Inner Stack ... 11: Last Outer Stack)" << endl;
        cout << "(Separate with whitespace)" << endl;
        cout << "Or enter nothing for random stack" << endl;
        cout << "Wild = 1, Wastes = 2, DevA = 3, DevB = 4" << endl;

        string stackTypeStr;
        getline(cin, stackTypeStr);
        // Testing Purpose
        if (stackTypeStr.size() == 0)
            createDefaultStack(GameResources.getstkVector(), 
                               GameResources.getFbTokenVector());
        else 
            equipFeedbackToken(GameResources.getstkVector(), 
                               GameResources.getFbTokenVector(), 
                               stackTypeStr);

        if (GameResources.getstkVector().size() != 11){
            cout << "Please enter 11 stacks" << endl;
            exit(-1);
        }

        // 2. Get Feedback Token amount
        string tokenNumberInput;
        cout << "Please enter the max number of feedback tokens of each kind" << endl;
        getline(cin, tokenNumberInput);

        try{
            int fbTokenNumber = stoi(tokenNumberInput);
            GameResources.setPool(feedBackPool(fbTokenNumber));
        }catch (const std::exception& e){
            cerr << "Invalid Max TokenNumber Input" << endl;
            exit(-1);
        }

        // 3. Get number of simulation turn
        cout << "Please enter the number of simulation turns" << endl;
        string simulationTurnInput;
        getline(cin, simulationTurnInput);

        try{
            int numTurns = stoi(simulationTurnInput); 
            GameResources.setRound(numTurns);
        }catch (const std::exception& e){
            cerr << "Invalid Simulation Turn Input" << endl;
            exit(-1);
        }

    }catch (const std::exception& e){
        cerr << "Invalid Input" << endl;
    }
}

void 
run_simulation(GameSetting & GameResources){

    int TurnCounter = 0;
    srand(time(nullptr));
    
    int round                            = GameResources.getRound();
    vector<stacks> &     stkVector       = GameResources.getstkVector();
    vector<STACK_EFFECT> & fbTokenVector = GameResources.getFbTokenVector();
    vector<stacks>       stacksChoices;  



    stacksChoices.push_back(stkVector[0]);

    /* Run "numTurns" time simulation */
    while (TurnCounter++ < round){
        // Reset stacksChoices at the beginning of each round
        stacksChoices.clear();
        stacksChoices.push_back(stkVector[0]);
        int counter = 1;
        try{
            while (counter < 12){
                // ! 1. Draw feedback Token and solve it
                int size               = fbTokenVector.size();
                int pos                = rand() % size;
                auto feedbackToken     = fbTokenVector[pos];

                if (counter == 1)
                    cout << "Draw FeedBack Token Stage: " << endl;
                // ! Stack 1, 8-11 is put back into the bags when resolved
                if (!(counter == 1 || counter >= 8))
                    fbTokenVector.erase(fbTokenVector.begin() + pos);
                else
                    // Put token back to pool for stack 1 and 8-11
                    GameResources.getPool().putBackToPool(feedbackToken);
                
                // ! 2. Place feedback token on the stack top
                // We want to select a random restricted stack  
                int selectedStack = 1;
                // Randomize stack choice to be put on
                if (counter == 2){
                    stacksChoices = vector<stacks>(stkVector.begin() + 1, stkVector.begin() + 7);
                }else if (counter == 8){
                    stacksChoices = vector<stacks>(stkVector.begin() + 7, stkVector.begin() + 11);
                }
                selectedStack = randStackSelction(stacksChoices);

                cout << counter << " " << feedbackToken << " Use on Stack : " << selectedStack << endl; 
                // ！3. Handle Effect
                handle_effect(selectedStack, GameResources, feedbackToken);
                // ！4. Draw from pool (reduce token count) - only for tokens that are not put back
                if (!(counter == 1 || counter >= 8))
                    GameResources.getPool().drawFromPool(feedbackToken);
                counter++;

            }
            cout << endl << endl;
            equipFeedbackToken(stkVector, fbTokenVector, "");

            /* ! Print out round result */
            GamePlayDisplay(GameResources, TurnCounter);

            /* ! File IO for visualization*/
            OutputToJson(VERSION, TurnCounter, GameResources);
            
        }catch(exception e){
            cout << "Run Simulation Error in Round " << TurnCounter << endl;
            cout << e.what() << endl;
        }
    }
}

void 
handle_effect(int stackNo, GameSetting & GameResources, STACK_EFFECT effect){
    vector<stacks> & stk = GameResources.getstkVector();
    int cohesion = 0; 

    switch (effect){
        case EFFECT_TURN_WILD:
            TurnWild(stackNo, stk);
            break;
        case EFFECT_LOSE_CO:
            cohesion = GameResources.getParameter().getCohesion();
            GameResources.getParameter().setCohesion(cohesion - 2);
            break;
        case EFFECT_TURN_WASTE:
            TurnWaste(stackNo, stk);
            break;
        // Need Disrupt Card
        case EFFECT_SOLVE_DISRUPT:
            handleDisruptionCard(stackNo, GameResources);
            break;
    }
    return;
}

// ! Turn a STACK into STACK_WASTE 
void 
TurnWaste(int turn, vector<stacks>& stk){
    int index = turn -1;
    stk[index].setType(STACK_WASTE);
}

// ! Turn a STACK into STACK_WILD
void 
TurnWild(int turn, vector<stacks>& stk){
    int index = turn -1;
    stk[index].setType(STACK_WILD);
}

// ! Random select a stk from a set of stk and return its position 
int 
randStackSelction(vector<stacks> & stk){
    int pos = 0;

    if (stk.size() != 1)
        pos = rand() % stk.size();
        
    int StackPos = stk[pos].getPosition();
    stk.erase(stk.begin() + pos);
    return StackPos;
}

void 
GamePlayDisplay(GameSetting & GameResource, int roundNum){
    
    // Display Stack Layout:
    cout << "**********************************************************"<< endl;
    cout << "*\t\t\tROUND " << roundNum  << "                          *"<< endl;
    cout << "**********************************************************"<< endl;
    cout << "\n1. STACK STATE" << endl << endl;

    for (auto e : GameResource.getstkVector()){
        cout << "Stack: " << e.getPosition() << " " << "State: " << e.toString() << endl;
    }


    cout << "\n2. TOTAL FEEDBACK TOKEN: " << GameResource.getFbTokenVector().size() << endl << endl;
    for (auto e : GameResource.getFbTokenVector()){
        cout << e << " ";
    }
    cout << endl << endl;
    cout << "**********************************************************"<< endl;
    cout << "*\t\t\tEnd Round                        *"<< endl;
    cout << "**********************************************************"<< endl;
}

// ! TODO: Could Randomize Initial State state
void 
createDefaultStack(vector<stacks> & stkVector, vector<STACK_EFFECT> & fbTokenVector){
    stkVector = {
        {STACK_TYPE::STACK_WILD, 1}   , {STACK_TYPE::STACK_WASTE, 2}, {STACK_TYPE::STACK_WILD, 3} , 
        {STACK_TYPE::STACK_WASTE, 4}  , {STACK_TYPE::STACK_WILD, 5} , {STACK_TYPE::STACK_WASTE, 6}, 
        {STACK_TYPE::STACK_WILD, 7}   , {STACK_TYPE::STACK_WASTE, 8}, {STACK_TYPE::STACK_WILD, 9} , 
        {STACK_TYPE::STACK_WASTE, 10} , {STACK_TYPE::STACK_DEVB, 11}
    };

    // Generate feedback tokens based on stack types
    for (auto e : stkVector){
        fbTokenVector.push_back(e.getEffect());
    }
}

void  
equipFeedbackToken(vector<stacks> & stkVector, vector<STACK_EFFECT> & fbTokenVector, string input){
    if (input == ""){
        fbTokenVector.clear();  // Clear before repopulating
        for (auto e : stkVector)
            fbTokenVector.push_back(STACK_EFFECT(e.getType()));
    } else {
        int counter = 0;
        for (auto e : input){
            if (e != ' '){
                int i = e - '0' - 1;
                stkVector.push_back(stacks(STACK_TYPE(i), ++counter));
                fbTokenVector.push_back(STACK_EFFECT(i));
            }
        }
    }
}


void  OutputToJson(int & version, int & currentRound, GameSetting GameResource){
    static nlohmann::json logArray = nlohmann::json::array();
    nlohmann::json jStruct;
    jStruct["version"]    = version;
    for (auto e : GameResource.getstkVector()){
        jStruct["board"]["hex"].push_back({
            {"id", e.getPosition()}, 
            {"type", e.toString()}
        });
    }
    jStruct["game_state"] = {
        {"current_round", currentRound},
        {"max_round",     GameResource.getRound()},
        {"bag_total",     80 - GameResource.getPool().getPoolSize()}
    };
    jStruct["tokens"]  = {
        {"Wilds",  GameResource.getPool().getTurnWildToken()},
        {"Wastes", GameResource.getPool().getLoseCohToken()},
        {"DevA",   GameResource.getPool().getTurnWasteToken()},
        {"DevB",   GameResource.getPool().getSolveDisruptToken()}
    };

    logArray.push_back(jStruct);

    if (currentRound == GameResource.getRound()){
        ofstream jsonFile("visualization/visualization.json");
        if (jsonFile.is_open()){
            jsonFile << logArray.dump(4);
            jsonFile.close();
        }
        cout << "JSON written to visualization/visualization.json" << endl;
    }
}

// Handle Disruption Card (Version 2)
void 
handleDisruptionCard(int stackNo, GameSetting & GameResources){
    // Check if deck is empty
    if (GameResources.getDisruptionManager().isDeckEmpty()){
        cout << "Disruption card deck is empty, cannot draw card" << endl;
        return;
    }
    
    // Draw a disruption card
    disruptionCard card = GameResources.getDisruptionManager().drawCard();
    
    // TEST MODE: Force use a card with tile change effects for testing
    static bool testMode = false;  // Disable test mode
    if (testMode) {
        // Create a test card based on VOLCANIC_ASH_1 with correct stackTarget
        nlohmann::json testCardData = {
            {"name", "VOLCANIC_ASH_1_TEST"},
            {"description", "Turn stack into wild unless pay 1 cybernation level"},
            {"type", "disrupt"},
            {"stackTarget", {1, 6, 7, 8, 11}},  // Correct target stacks
            {"effect", {"TurnWild"}},
            {"cost", {"Cy:-1"}},
            {"cond", ""},
            {"optional", {}},
            {"victoryImpact", "None"},
            {"cancel", true}
        };
        card = disruptionCard::fromJson(testCardData);
        cout << "TEST MODE: Using VOLCANIC_ASH_1 with correct stackTarget [1,6,7,8,11]" << endl;
    }
    
    cout << "Draw disruption card: " << card.getCardName() << endl;
    
    // Check if card has tile change effects
    if (!card.hasTileChangeEffect()){
        cout << "Card has no tile change effects, nothing happens" << endl;
        return;
    }
    
    // Get target stacks
    vector<int> targets = card.getCardStackTarget();
    vector<stacks> & stk = GameResources.getstkVector();
    
    // Apply effects to each target stack
    for (int targetId : targets){
        // Ensure target stack ID is valid
        if (targetId >= 1 && targetId <= 11){
            int stackIndex = targetId - 1; // Convert to 0-based index
            
            // Apply each effect
            for (auto effect : card.getCardEffect()){
                switch (effect.first){
                    case DISRUPTION_TURN_WILD:
                        cout << "Convert stack " << targetId << " to WILD" << endl;
                        cout.flush();
                        TurnWild(targetId, stk);
                        break;
                    case DISRUPTION_TURN_WASTE:
                        cout << "Convert stack " << targetId << " to WASTE" << endl;
                        TurnWaste(targetId, stk);
                        break;
                    case DISRUPTION_TURN_DEVA:
                        cout << "Convert stack " << targetId << " to DEVA" << endl;
                        stk[stackIndex].setType(STACK_TYPE::STACK_DEVA);
                        break;
                    case DISRUPTION_TURN_DEVB:
                        cout << "Convert stack " << targetId << " to DEVB" << endl;
                        stk[stackIndex].setType(STACK_TYPE::STACK_DEVB);
                        break;
                    default:
                        // Ignore other effects
                        break;
                }
            }
        }
    }
}