#ifndef _PARAMS_HPP
#define _PARAMS_HPP

class params{
    private:
        int cohesion         = 10;
        int cybernationLevel = 2;
        int HumanRelation    = 7;
        int environmemts     = 7;
        int Technology       = 7;
    public:
        // Constructor & Destructor
        params();
        params(int l, int r, int e, int t, int c);
        ~params(){};

        // Getter
        inline int getCybernationLevel();
        inline int getHumanRelation();
        inline int getEnvironment();
        inline int getTechnology();
        inline int getCohesion();
        // Setter
        void setCybernationLevel(int l);
        void setHumanRelation(int r);
        void setEnvironment(int e);
        void setTechnology(int t);
        void setCohesion(int c);

};


#endif