#pragma once
#ifndef URN
#define URN

#include <random>
#include <map>
#include <iostream>
class urn {
private:
	std::map<int, int> weights;
	int noball = 1, sum = 0;
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
	double prob;
	params(int nob, int mode, double prob) :noball(nob), mode(mode), prob(prob) {};
};

#endif // DEBUG
