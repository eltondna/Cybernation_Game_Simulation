#include "../includes/include.hpp"
using namespace std;

/* Terminal Display */
void menu(GameSetting & GameResources);
void GamePlayDisplay(GameSetting & GameResource, int roundNum);

/* Interface Function */

/* Main simulation Loop */
void  run_simulation(GameSetting & GameResources);

void  createDefaultStack(vector<stacks> & stkVector, vector<STACK_EFFECT> & fbTokenVector);
void  equipFeedbackToken(vector<stacks> & stkVector, vector<STACK_EFFECT> & fbTokenVector, string input);

void  handle_effect(int stackNo, GameSetting & GameResources, STACK_EFFECT effect);
void  TurnWaste(int turn, vector<stacks> & stk);
void  TurnWild(int turn, vector<stacks> & stk);
int   randStackSelction(vector<stacks> & stk);


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
        // 1. Get TILEs Type
        cout << "Version 1 Simulation" << endl;
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
        int fbTokenNumber = 0;
        cout << "Please enter the max number of feedback tokens of each kind" << endl;
        (cin >> fbTokenNumber).get();
        GameResources.setPool(feedBackPool(fbTokenNumber));


        // 3. Get number of simulation turn
        int numTurns = 0; 
        cout << "Please enter the number of simulation turns" << endl;
        (cin >> numTurns).get();
        GameResources.setRound(numTurns);

    }catch (exception e){
        cout << "Invalid Input" << endl;
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
                
                // ! 2. Place feedback token on the stack top
                // We want to select a random restricted stack  
                int selectedStack   = 1;
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
                counter++;

            }
            cout << endl << endl;
            /* Print out round result */
            equipFeedbackToken(stkVector, fbTokenVector, "");
            GamePlayDisplay(GameResources, TurnCounter);

        }catch(exception e){
            cout << "Run Simulation Error" << endl;
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
    if (stk.size() == 1)
        return 1;
    else {
        int pos = rand() % stk.size();
        int StackPos = stk[pos].getPosition();
        stk.erase(stk.begin() + pos);
        return StackPos;
    }
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
        {STACK_TYPE::STACK_WASTE, 10} , {STACK_TYPE::STACK_DEVA, 11}
    };

    fbTokenVector = {
        {STACK_EFFECT::EFFECT_TURN_WILD}, {STACK_EFFECT::EFFECT_LOSE_CO}  , {STACK_EFFECT::EFFECT_TURN_WILD},
        {STACK_EFFECT::EFFECT_LOSE_CO}  , {STACK_EFFECT::EFFECT_TURN_WILD}, {STACK_EFFECT::EFFECT_LOSE_CO}  ,
        {STACK_EFFECT::EFFECT_TURN_WILD}, {STACK_EFFECT::EFFECT_LOSE_CO}  , {STACK_EFFECT::EFFECT_TURN_WILD}, 
        {STACK_EFFECT::EFFECT_LOSE_CO}  , {STACK_EFFECT::EFFECT_TURN_WASTE}
    };
}

void  
equipFeedbackToken(vector<stacks> & stkVector, vector<STACK_EFFECT> & fbTokenVector, string input){
    if (input == "")
        for (auto e : stkVector)
            fbTokenVector.push_back(STACK_EFFECT(e.getType()));
    else {
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