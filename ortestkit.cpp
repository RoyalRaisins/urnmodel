#include "testkit.h"
#include "dgurn.h"
#include "simpleurn.h"
#include "tools.h"

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
	struct params p(noball, distrib, 0);
	std::vector<testinstance*> results = generateinstances<simpleurn>(notestinstances, noball, maxcost, p); //classes with virtual functions do not work well with template
	double average = getaverageprecision(results);
	std::cout << "the average precision is " << average << std::endl;
	std::vector<double> epsilons = { 0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45 };
	int noep = epsilons.size();
	for (int i = 0; i < noep; i++) {
		double precision = getprecision(results, 1/epsilons[i]);
		printprecisionresult(epsilons[i],precision);
	}
}



void dgtestTest(int notestinstances, int noball, int maxcost, double prob, int maxnocycle, int maxcyclelen) {
	struct params p(noball, 0, prob, maxnocycle, maxcyclelen);
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
		clock_t start, end;
		start = clock();
		instance->recordedsample(samp);
		end = clock();
		std::cout << "Sampling for instance " << i << " has taken " << end - start << " milliseconds.\n";

	}
	return results;
}

void inputtest(std::string path,int groundtruthsum) {
	dgurn* urn = fromntfile(path, groundtruthsum);
	std::vector<testinstance*> results;
	results.push_back(new testinstance);
	sampler* samp = new sampler(urn->getnoball() * 2, urn);
	clock_t start, end;
	start = clock();
	results[0]->recordedsample(samp);
	end = clock();
	std::cout << "Sampling for the instance has taken " << end - start << " milliseconds.\n";

	std::vector<double> epsilons = { 0.05,0.1,0.15,0.2,0.25,0.3,0.35,0.4,0.45 };
	int noep = epsilons.size();
	double average = getaverageprecision(results);
	std::cout << "the average precision is " << average << std::endl;
	for (int i = 0; i < noep; i++) {
		double precision = getprecision(results, 1 / epsilons[i]);
		printprecisionresult(epsilons[i], precision);
	}

}