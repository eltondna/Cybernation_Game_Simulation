#include "include.hpp"
using namespace std;



/* Interface Declaration */
void menu(std::vector<stacks> & stkVector, int & fbTokenNumber, int & numTurns);
void run_simulation(std::vector<stacks> stkVector, 
                    int & fbTokenNumber, 
                    int & numTurns, 
                    params & parameters);

/* ! Handle feedback token effect */
void handle_effect(vector<stacks> & stk, params & parameter, STACK_EFFECT effect);
int  DamageControl(int turn, vector<stacks> stk);
int  Optimisation(int turn, vector<stacks> stk);


/* Debug Function */
ostream & operator << (ostream & os, STACK_EFFECT effect){
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



int main(int argc, char* argv[]){
    int flag = 0;

    while (!flag){
        /* Resources */ 
        vector<stacks> stkVector;
        int fbTokenNumber = 0;
        int numTurns      = 0;
        params parameters = params();


        menu(stkVector, fbTokenNumber, numTurns);
        run_simulation(stkVector, fbTokenNumber, numTurns, parameters);
        cout << "Press any key to simulate again" << endl;
        cout << "Press q to quit" << endl;

        if (tolower(cin.get()) == 'q')
            break;
        cin.get();
    }

}

void 
menu(std::vector<stacks> & stkVector, int & fbTokenNumber, int & numTurns){
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
                    int & fbTokenNumber, 
                    int & numTurns, 
                    params & parameters){
   
    try{
         // ! 1. Draw feedback Token and solve it
        srand(time(nullptr));
        int counter = 0;
        while (counter++ < 11){
            int size            = stkVector.size();
            int pos             =  rand() % size;
            auto card = stkVector[pos];

            cout << "Draw " << card.toString() << " from position " << card.getPosition() << endl;
            cout << "Feedback Token Effect: " << card.getEffect() << endl << endl;
            stkVector.erase(stkVector.begin() + pos);
        // ! 2. Handle Effect
            handle_effect(stkVector, parameters, card.getEffect());
        // ！3. Place feedback token on the stack top

        }
    }catch(exception e){
        cout << e.what() << endl;
    }
}

void handle_effect(vector<stacks> & stk, params & parameter, STACK_EFFECT effect){
    switch (effect){
        case EFFECT_TURN_WILD:
            int stackPosition = Optimisation(stk);
            break;
        case EFFECT_LOSE_CO:
            int cohesion = parameter.getCohesion();
            parameter.setCohesion(cohesion - 2);
            break;
        case EFFECT_TURN_WASTE:
            int stackPosition = DamageControl(stk);
            break;
        case EFFECT_SOLVE_DISRUPT:
            break;
    }
    return;
}

// ! Turn which STACK into STACK_WASTE 
int DamageControl(int turn, vector<stacks> stk){
    return 0;
}

// ! Turn which STACK into STACK_WILD
int Optimisation(int turn, vector<stacks> stk){
    return 0;
}
