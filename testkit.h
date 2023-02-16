#pragma once
#ifndef TESTKIT
#define TESTKIT

#include "algorithm.h"
#include <vector>
class testinstance {
	int groundtruth, nosample, budgetleft, maxcost;
	double estimate, deviation;
public:
	void recordedsample(sampler* s);
	double getdeviation();
};

double getprecision(std::vector<testinstance*> instances, double targetdeviation);

void testTest(int notestinstances, int noball, int maxcost, int distrib);
void dgtestTest(int notestinstances, int noball, int maxcost, double prob, int maxnocycle, int maxcyclelen);

void inputtest(std::string path,int groundtruthsum);

template<class T> std::vector<testinstance*> generateinstances(int notestinstances, int noball, int maxcost, struct params p);
template<class T> urn* urncreator(struct params p);
#endif // !TESTKIT
