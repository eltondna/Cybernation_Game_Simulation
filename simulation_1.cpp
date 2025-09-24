#include "include.hpp"
using namespace std;



/* Interface Declaration */
void menu(std::vector<stacks> & stkVector, std::vector<STACK_EFFECT> & effVector, int & fbTokenNumber, int & numTurns);
void run_simulation(std::vector<stacks> stkVector, 
                    std::vector<STACK_EFFECT> fbTokenVector,
                    int & fbTokenNumber, 
                    int & numTurns, 
                    params & parameters);

/* ! Handle feedback token effect */
void  handle_effect(int turn, vector<stacks> & stk, params & parameter, STACK_EFFECT effect);
void  TurnWaste(int turn, vector<stacks> & stk);
void  TurnWild(int turn, vector<stacks> & stk);
int   randStackSelction(vector<stacks> & stk);


/* Debug Function */
ostream & operator << 
(ostream & os, STACK_EFFECT effect){
    switch (effect){
        case EFFECT_TURN_WILD:
            return os << "Turn Wild";
        case EFFECT_LOSE_CO:
            return os << "Lose Cohesion";
        case EFFECT_TURN_WASTE:
            return os << "Turn Waste";
        case EFFECT_SOLVE_DISRUPT:
            return os << "Solve Disrupt";
        default:    
            return os << "UNKNOWN";
    }
}



int 
main(int argc, char* argv[]){
    int flag = 0;

    while (!flag){
        /* Resources */ 
        vector<stacks> stkVector;
        vector<STACK_EFFECT> fbTokenVector;
        int fbTokenNumber = 0;
        int numTurns      = 0;
        params parameters = params();


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
        if (stackTypeStr.size() == 0){
            // Randomize the stack 
            stkVector = {
                {STACK_TYPE::STACK_WILD, 1}  , {STACK_TYPE::STACK_WASTE, 2}, {STACK_TYPE::STACK_WILD, 3} , 
                {STACK_TYPE::STACK_WASTE,4}  , {STACK_TYPE::STACK_WILD, 5} , {STACK_TYPE::STACK_WASTE, 6}, 
                {STACK_TYPE::STACK_WILD, 7}  , {STACK_TYPE::STACK_WASTE, 8}, {STACK_TYPE::STACK_WILD, 9} , 
                {STACK_TYPE::STACK_WASTE, 10}, {STACK_TYPE::STACK_DEVA,11}
            };
        }else {

            int counter = 0;
            for (auto e : stackTypeStr){
                if (e != ' '){
                    int i = e - '0' - 1;
                    stkVector.push_back(stacks(STACK_TYPE(i), ++counter));
                    fbTokenVector.push_back(STACK_EFFECT(i));
                }
            }
        }


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
                    int & fbTokenNumber, 
                    int & numTurns, 
                    params & parameters){
    try{
        // ! 1. Draw feedback Token and solve it
        srand(time(nullptr));
        int counter = 1;
        vector<stacks> stacksChoices;
        while (counter < 12){
            int size               = fbTokenVector.size();
            int pos                = rand() % size;
            auto feedbackToken     = fbTokenVector[pos];

            cout << "Draw Feedback Token Effect: " <<  feedbackToken << endl << endl;
            fbTokenVector.erase( fbTokenVector.begin() + pos);

            // ! 2. Place feedback token on the stack top
            vector<STACK_EFFECT> newFbVector;
            int selectedStack   = 1;

            // Randomize stack choice to be put on
            if (counter == 2){
                stacksChoices = vector<stacks>(stkVector.begin() + 1, stkVector.begin() + 6);
            }else if (counter == 8){
                stacksChoices = vector<stacks>(stkVector.begin() + 7, stkVector.end());
            }
            selectedStack = randStackSelction(stacksChoices);
            cout << "Use token on Stack : " << selectedStack << endl;

            // ！3. Handle Effect TODO 
            handle_effect(selectedStack, stkVector, parameters, feedbackToken);
            counter++;
        }
    }catch(exception e){
        cout << e.what() << endl;
    }
}

void handle_effect(int stackNo, vector<stacks> & stk, params & parameter, STACK_EFFECT effect){

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
            TurnWild(stackNo, stk);
            break;
        // Need Disrupt Card
        case EFFECT_SOLVE_DISRUPT:
            break;
    }
    return;
}

// ! Turn which STACK into STACK_WASTE 
void TurnWaste(int turn, vector<stacks>& stk){
    stk[turn].setType(STACK_WILD);
}

// ! Turn which STACK into STACK_WILD
void TurnWild(int turn, vector<stacks>& stk){
    stk[turn].setType(STACK_WASTE);
}

int randStackSelction(vector<stacks> & stk){
    int pos = rand() % stk.size();
    int StackPos = stk[pos].getPosition();
    stk.erase(stk.begin() + pos);
    return StackPos;
}
