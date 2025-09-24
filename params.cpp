#include "params.hpp"


params::params(int l, int r, int e, int t, int c)
:cybernationLevel(l),HumanRelation(r),environmemts(e),Technology(t), cohesion(c){

}

inline int params::getCybernationLevel()
{
    return cybernationLevel;
}

inline int params::getHumanRelation()
{
    return HumanRelation;
}

inline int params::getEnvironment()
{
    return environmemts;
}

inline int params::getTechnology()
{
    return Technology;
}

inline int params::getCohesion()
{
    return cohesion;
}

void params::setCybernationLevel(int l)
{
    if (l < 0 || l > 20)
        return;
    this->cybernationLevel = l;
}

void params::setHumanRelation(int r)
{
    if (r > 20 || r < 0 || r > this->cohesion)
        return;
    this->HumanRelation = r;
}

void params::setEnvironment(int e)
{
    if (e > 20 || e < 0 || e > this->cohesion)
        return;
    this->environmemts = e;
}

void params::setTechnology(int t)
{
    if (t > 20 || t < 0 || t > this->cohesion)
        return;
    this->Technology = t;
}

void params::setCohesion(int c)
{
    if (c > 20 || c < 0)
        return;
    
    this->cohesion = c;
    // Push back resources
    this->environmemts      = c < this->environmemts  ? c : this->environmemts;
    this->HumanRelation     = c < this->HumanRelation ? c : this->HumanRelation;
    this->Technology        = c < this->Technology    ? c : this->Technology;
    return;
}
