#include "params.hpp"


params::params(int l, int r, int e, int s, int c)
:cybernationLevel(l),relations(r),environmemts(e),steer(s), conflict(c){

}

inline int params::getCybernationLevel()
{
    return cybernationLevel;
}

inline int params::getRelation()
{
    return relations;
}

inline int params::getEnvironment()
{
    return environmemts;
}

inline int params::getSteer()
{
    return steer;
}

inline int params::getConflict()
{
    return conflict;
}

void params::setCybernationLevel(int l)
{
    if (l < 0 || l > 20)
        return;
    this->cybernationLevel = l;
}

void params::setRelation(int r)
{
    if (r > 20 || r < 0 || r > this->conflict)
        return;
    this->relations = r;
}

void params::setEnvironment(int e)
{
    if (e > 20 || e < 0 || e > this->conflict)
        return;
    this->environmemts = e;
}

void params::setSteer(int s)
{
    if (s > 20 || s < 0 || s > this->conflict)
        return;
    this->steer = s;
}

void params::setConflict(int c)
{
    if (c > 20 || c < 0)
        return;
    
    this->conflict = c;
    // Push back resources
    this->environmemts = c < this->environmemts ? c : this->environmemts;
    this->relations    = c < this->relations    ? c : this->relations;
    this->steer        = c < this->steer        ? c : this->steer;
    return;
}
