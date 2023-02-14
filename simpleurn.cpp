
#include "simpleurn.h"
#include <random>
#include <map>
#include <iostream>
#include <iomanip>
#include <cmath>

simpleurn::simpleurn(int noballs):urn(noballs) {}
simpleurn::simpleurn(int noballs, int mode):urn(noballs,mode){}
simpleurn::simpleurn(struct params p) :urn(p) {}

int simpleurn::getweight(int index) { return ((urn*)this)->getweight(index); }
int simpleurn::getsum() { return ((urn*)this)->getsum(); }
