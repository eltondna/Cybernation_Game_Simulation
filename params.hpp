#ifndef _PARAMS_HPP
#define _PARAMS_HPP

class params{
    private:
        int conflict         = 10;
        int cybernationLevel = 7;
        int relations        = 7;
        int environmemts     = 7;
        int steer            = 7;
    public:
        // Constructor & Destructor
        params();
        params(int l, int r, int e, int s, int c);
        ~params(){};

        // Getter
        inline int getCybernationLevel();
        inline int getRelation();
        inline int getEnvironment();
        inline int getSteer();
        inline int getConflict();
        // Setter
        void setCybernationLevel(int l);
        void setRelation(int r);
        void setEnvironment(int e);
        void setSteer(int s);
        void setConflict(int c);

};


#endif