#pragma once
#ifndef ALGORITHM
#define ALGORITHM
#include "urn.h"

class sampler {
private:
	int sum, nosample, maxcost, budget, noball;
	std::uniform_int_distribution<> distrib;
	std::mt19937 gen;
	urn *u;
public:
	int getmaxcost();
	int getnosample();
	int getbudget();
	int getgtsum();
	sampler(int maxcost);
	sampler(int maxcost, urn* u);
	void sampleonce();
	bool prepareRandgen();
	double dosample();
	int getunirandno();
};

#endif