#include "include.hpp"
using namespace std;

/* Terminal Display*/
void menu(std::vector<stacks> & stkVector, 
          std::vector<STACK_EFFECT> & effVector, 
          int & fbTokenNumber, 
          int & numTurns);
void GamePlayDisplay(const vector<stacks> & stk, 
                      const vector<STACK_EFFECT> &feedBackTokensVector,
                      const params & currentGameParams,
                      int round);

/* Interface Function */

/* Main simulation Loop */
void run_simulation(std::vector<stacks> stkVector, 
                    std::vector<STACK_EFFECT> fbTokenVector,
                    int & fbTokenReserve, 
                    int & numTurns, 
                    params & parameters);

void  createDefaultStack(vector<stacks> & stkVector, vector<STACK_EFFECT> & fbTokenVector);
void  equipFeedbackToken(vector<stacks> & stkVector, vector<STACK_EFFECT> & fbTokenVector, string input);

void  handle_effect(int turn, vector<stacks> & stk, params & parameter, STACK_EFFECT effect);
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
        /* Resources */ 
    vector<stacks> stkVector;
    vector<STACK_EFFECT> fbTokenVector;
    int fbTokenNumber = 0;
    int numTurns      = 0;
    params parameters = params();
    
    while (true){
        menu(stkVector, fbTokenVector, fbTokenNumber, numTurns);
        run_simulation(stkVector, fbTokenVector, fbTokenNumber, numTurns, parameters);
        cout << "Press any key to simulate again" << endl;
        cout << "Press q to quit" << endl;

        if (tolower(cin.get()) == 'q')
            break;
        cin.get();
    }
}

void 
menu(std::vector<stacks> & stkVector, std::vector<STACK_EFFECT> & fbTokenVector, int & fbTokenNumber, int & numTurns){
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
            createDefaultStack(stkVector, fbTokenVector);
        else 
            equipFeedbackToken(stkVector, 
                               fbTokenVector, 
                               stackTypeStr);

        if (stkVector.size() != 11){
            cout << "Please enter 11 stacks" << endl;
            exit(-1);
        }
        // 2. Get Feedback Token amount
        cout << "Please enter the max number of feedback tokens of each kind" << endl;
        (cin >> fbTokenNumber).get();

        // 3. Get number of simulation turn
        cout << "Please enter the number of simulation turns" << endl;
        (cin >> numTurns).get();

    }catch (exception e){
        cout << "Invalid Input" << endl;
    }
}


void run_simulation(std::vector<stacks> stkVector, 
                    std::vector<STACK_EFFECT> fbTokenVector,
                    int & fbTokenReserve, 
                    int & numTurns, 
                    params & parameters){

    int TurnCounter = 0;
    srand(time(nullptr));
    vector<stacks> stacksChoices;
    stacksChoices.push_back(stkVector[0]);

    /* Run "numTurns" time simulation */
    while (TurnCounter++ < numTurns){
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
                handle_effect(selectedStack, stkVector, parameters, feedbackToken);
                counter++;

            }
            cout << endl << endl;
            /* Print out round result */
            equipFeedbackToken(stkVector, fbTokenVector,"");
            GamePlayDisplay(stkVector, fbTokenVector, parameters, TurnCounter);

        }catch(exception e){
            cout << "Run Simulation Error" << endl;
            cout << e.what() << endl;
        }

    }

}

void 
handle_effect(int stackNo, vector<stacks> & stk, params & parameter, STACK_EFFECT effect){

    // cout << "Effect=" << effect 
    //  << " | stackNo=" << stackNo 
    //  << " | stk.size()=" << stk.size() << endl;

    int cohesion = 0; 
    switch (effect){
        case EFFECT_TURN_WILD:
            TurnWild(stackNo, stk);
            break;
        case EFFECT_LOSE_CO:
            cohesion = parameter.getCohesion();
            parameter.setCohesion(cohesion - 2);
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

// ! Turn which STACK into STACK_WASTE 
void 
TurnWaste(int turn, vector<stacks>& stk){
    int index = turn -1;
    stk[index].setType(STACK_WASTE);
}

// ! Turn which STACK into STACK_WILD
void 
TurnWild(int turn, vector<stacks>& stk){
    int index = turn -1;
    stk[index].setType(STACK_WILD);
}

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
GamePlayDisplay(const vector<stacks> & stk, 
                const vector<STACK_EFFECT> &feedBackTokensVector,
                const params & currentGameParams,
                int round){
    
    // Display Stack Layout:
    cout << "ROUND " << round << endl;
    cout << "----------------------------------------------------------"<< endl;
    cout << "1. STACK STATE" << endl;

    for (auto e : stk){
        cout << "Stack: " << e.getPosition() << " " << "State: " << e.toString() << endl;
    }
    cout << "----------------------------------------------------------"<< endl;
    cout << "2. TOTAL FEEDBACK TOKEN: " << feedBackTokensVector.size() << endl;
    for (auto e : feedBackTokensVector){
        cout << e << endl;
    }
    cout << "----------------------------------------------------------"<< endl;
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
    if (input == ""){
        for (auto e : stkVector)
            fbTokenVector.push_back(STACK_EFFECT(e.getType()));
    }
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