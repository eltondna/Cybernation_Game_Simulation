#ifndef _PARAMS_HPP
#define _PARAMS_HPP

enum CYBER_PARAMETER{
    COHESION,
    CYBERNATION_LEVEL,
    HUMAN_RELATION,
    ENVIRONMENT,
    TECHNOLOGY
};

class params{
    private:
        int cohesion         = 10;
        int cybernationLevel = 2;
        int HumanRelation    = 7;
        int environmemts     = 7;
        int Technology       = 7;
    public:
        // Constructor & Destructor
        params(){};
        params(int l, int r, int e, int t, int c);
        ~params(){};
        
        // Getter
        inline int getCybernationLevel(){return cybernationLevel;}
        inline int getHumanRelation(){return HumanRelation;}
        inline int getEnvironment(){return environmemts;}
        inline int getTechnology(){return Technology;}
        inline int getCohesion(){return cohesion;}
        // Setter
        void setCybernationLevel(int l);
        void setHumanRelation(int r);
        void setEnvironment(int e);
        void setTechnology(int t);
        void setCohesion(int c);

};


#endif