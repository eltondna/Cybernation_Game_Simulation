#include "stack.hpp"
#include <iostream>
#include <vector>
using namespace std;

void menu(std::vector<stacks> & stkVector, int & fbTokenNumber, int & numTurns);
void run_simulation(std::vector<stacks> & stkVector, int & fbTokenNumber, int & numTurns);

int main(int argc, char* argv[]){
    int flag = 0;

    while (!flag){
        /* Resources */ 
        vector<stacks> stkVector;
        int fbTokenNumber = 0;
        int numTurns      = 0;
        char result[1024] = {0};


        menu(stkVector, fbTokenNumber, numTurns);
        run_simulation(stkVector, fbTokenNumber, numTurns);
        cout << "Press any key to simulate again" << endl;
        cout << "Press q to quit" << endl;

        if (cin.get() == 'q')
            exit(0);
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
            cout << "Random" << endl;
            exit(0);
        }

        for (auto e : stackTypeStr){
            if (e != ' '){
                int i = e - '0' - 1;
                stkVector.push_back(stacks(STACK_TYPE(i)));
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


void 
run_simulation(std::vector<stacks> & stkVector, int & fbTokenNumber, int & numTurns){
    // 1. 


}
