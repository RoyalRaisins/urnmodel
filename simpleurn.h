#pragma once
#include "urn.h"

class simpleurn :public urn {
public:
	simpleurn() {};
	simpleurn(int noballs);
	simpleurn(int noballs, int mode);
	simpleurn(struct params p);

	int getweight(int index);
	int getsum();
};