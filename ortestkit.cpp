#include "testkit.h"
#include "dgurn.h"
#include <cmath>
#include <string>
#include <iostream>
void testinstance::recordedsample(sampler* s) {
	maxcost = s->getmaxcost();
	groundtruth = s->getgtsum();
	estimate = s->dosample();
	nosample = s->getnosample();
	budgetleft = s->getbudget();
	deviation = estimate / groundtruth; //wrong!!!!!
	return;
}

double testinstance::getdeviation() {
	return deviation;
}

double getprecision(std::vector<testinstance*> instances, double targetdeviation) {
	int len = instances.size(), nohits = 0;
	for (int i = 0; i < len; i++) {
		if (instances[i]->getdeviation() <= targetdeviation)nohits++;
	}
	return ((double)nohits / len);
}

void printprecisionresult(double epsilon, double param) {
	bool success = ((1 - 2 * epsilon) <= param);
	std::string result = success ? "successful" : "failed";
	std::cout << "¦Å: "<< epsilon << ", the hitrate is " << param << ", " << "test " << result << std::endl;
}

double getaverageprecision(std::vector<testinstance*> instances) {
	int len = instances.size();
	double sum = 0;
	for (int i = 0; i < len; i++)sum += instances[i]->getdeviation();
	return (sum / len);
}

void testTest(int notestinstances, int noball, int maxcost, int distrib) {
	std::vector<testinstance*> results;
	for (int i = 0; i < notestinstances; i++) {
		urn u(noball, distrib);
		sampler samp(maxcost, &u);
		testinstance* instance = new testinstance();
		results.push_back(instance);
		instance->recordedsample(&samp);
	}
	double average = getaverageprecision(results);
	std::cout << "the average precision is " << average << std::endl;
	std::vector<double> epsilons = { 0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45 };
	int noep = epsilons.size();
	for (int i = 0; i < noep; i++) {
		double precision = getprecision(results, 1/epsilons[i]);
		printprecisionresult(epsilons[i],precision);
	}
}



void dgtestTest(int notestinstances, int noball, int maxcost, double prob) {
	/*std::vector<testinstance*> results;
	for (int i = 0; i < notestinstances; i++) {
		dgurn u(noball, prob);
		sampler samp(maxcost, &u);
		testinstance* instance = new testinstance();
		results.push_back(instance);
		instance->recordedsample(&samp);
	}*/
	
	struct params p(noball, 0, prob);
	std::vector<testinstance*> results = generateinstances<dgurn>(notestinstances, noball, maxcost, p);
	std::vector<double> epsilons = { 0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45 };
	int noep = epsilons.size();
	double average = getaverageprecision(results);
	std::cout << "the average precision is " << average << std::endl;
	for (int i = 0; i < noep; i++) {
		double precision = getprecision(results, 1 / epsilons[i]);
		printprecisionresult(epsilons[i], precision);
	}
}


void dgtestcycled(int notestinstances, int noball, int maxcost, double prob) {

}

template<class T> T* urncreator(struct params p) {
	return new T(p);
}

template<class T> std::vector<testinstance*> generateinstances(int notestinstances, int noball, int maxcost, struct params p) {
	T* (*creator)(struct params) = urncreator<T>;
	std::vector<testinstance*> results;
	for (int i = 0; i < notestinstances; i++) {
		T* u = creator(p);
		sampler* samp = new sampler(maxcost, u);
		testinstance* instance = new testinstance();
		results.push_back(instance);
		instance->recordedsample(samp);
	}
	return results;
}