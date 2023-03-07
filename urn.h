#pragma once
#ifndef URN
#define URN

#include <random>
#include <map>
#include <iostream>
class urn {
private:
	std::map<int, int> weights;
	int noball = 1, sum = 0, maxweight;
public:
	urn() {};
	urn(int noballs);
	urn(int noballs, int mode);
	urn(struct params p);

	int getnoball();
	void setnoball(int newno);

	virtual int getweight(int index);
	void setweight(int index, int weight);

	virtual int getsum();
	void setsum(int sum);

	void generateuniweights();
	void generatenormweights();
	void generaterandweights();

	void printweights();
};


struct params {
	int noball;
	int mode;
	int maxnocycle, maxcyclelen;
	double prob;
	params(int nob, int mode, double prob) :noball(nob), mode(mode), prob(prob), maxnocycle(0), maxcyclelen(0) {};
	params(int nob, int mode, double prob, int noc, int cylen) :noball(nob), mode(mode), prob(prob), maxnocycle(noc), maxcyclelen(cylen) {};
	//mode is currently used to indicate the distribution of the balls' weights in the primitive case and whether to spawn cycles in the dg case.


};

#endif // DEBUG
