/* ! Feedback Token Effect */
enum STACK_EFFECT{
    EFFECT_TURN_WILD,
    EFFECT_LOSE_CO,
    EFFECT_TURN_WASTE,
    EFFECT_SOLVE_DISRUPT,
    EFFECT_UNKNOWM
}; 

class feedBackPool{
    private:
        int TurnWildToken;
        int LoseCohToken;
        int TurnWasteToken;
        int SolveDisruptToken;
    public:
        feedBackPool(){
            TurnWildToken = TurnWasteToken = 
            LoseCohToken = SolveDisruptToken = 10;
        };
        feedBackPool(int wild, int lose, int waste, int solve):
        TurnWildToken(wild), LoseCohToken(lose), TurnWasteToken(waste),
        SolveDisruptToken(solve){

        };
        ~feedBackPool();
        
        inline int getTurnWildToken(){return TurnWildToken;};
        inline int getLoseCohToken(){return LoseCohToken;};
        inline int getTurnWasteToken(){return TurnWasteToken;};
        inline int getSolveDisruptToken(){return SolveDisruptToken;};


        inline void setTurnWildToken(int num){this->TurnWildToken = num;};
        inline void setLoseCohToken(int num){this->LoseCohToken = num;};
        inline void setTurnWasteToken(int num){this->TurnWasteToken = num;};
        inline void setSolveDisruptToken(int num){this->SolveDisruptToken = num;};

};