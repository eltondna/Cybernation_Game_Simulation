#ifndef _FEEDBACKPOOL_HPP
#define _FEEDBACKPOOL_HPP

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
        int total;
    public:
        feedBackPool(int each = 10){
            TurnWildToken = TurnWasteToken = 
            LoseCohToken = SolveDisruptToken = each;
            total = (each << 2);
        };

        feedBackPool(int wild, int lose, int waste, int solve):
        TurnWildToken(wild), LoseCohToken(lose), TurnWasteToken(waste),
        SolveDisruptToken(solve), total(wild + lose + waste + solve){
        };
        ~feedBackPool(){};
        
        inline int getTurnWildToken(){return TurnWildToken;};
        inline int getLoseCohToken(){return LoseCohToken;};
        inline int getTurnWasteToken(){return TurnWasteToken;};
        inline int getSolveDisruptToken(){return SolveDisruptToken;};


        inline void setTurnWildToken(int num){this->TurnWildToken = num > 0 ? num : this->TurnWildToken;};
        inline void setLoseCohToken(int num){this->LoseCohToken = num >  0 ? num : this->LoseCohToken;};
        inline void setTurnWasteToken(int num){this->TurnWasteToken = num >  0 ? num : this->TurnWasteToken;};
        inline void setSolveDisruptToken(int num){this->SolveDisruptToken = num >  0 ? num : this->SolveDisruptToken;};

        bool drawFromPool(STACK_EFFECT token);
        void putBackToPool(STACK_EFFECT token);
        int getPoolSize(){return total;};
};

#endif