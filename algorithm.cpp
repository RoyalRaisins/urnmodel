#include "algorithm.h"

sampler::sampler(int maxcost) { 
	this->maxcost = this->budget = maxcost; 
	this->u = new urn(0); 
}
sampler::sampler(int maxcost, urn* u) {
	this->maxcost = this->budget = maxcost;
	this->u = u;
}

int sampler::getmaxcost(){
	return maxcost;
}

int sampler::getnosample() {
	return nosample;
}
int sampler::getbudget() {
	return budget;
}
void sampler::sampleonce() {
	int rand = getunirandno();
	int weight = this->u->getweight(rand);
	this->budget -= weight;
	this->sum += weight;
	this->nosample++;
}

int sampler::getunirandno() {
	return this->distrib(this->gen);
}

int sampler::getgtsum() {
	return u->getsum();
}
bool sampler::prepareRandgen() {
	std::random_device rd;
	std::mt19937 gen(rd());
	this->gen = gen;
	if (this->u->getnoball() == 0)return false;
	std::uniform_int_distribution<> distrib(1, this->u->getnoball());
	this->distrib = distrib;
}

double sampler::dosample() {
	this->budget = maxcost;
	this->nosample = 0;
	this->sum = 0;
	if (this->u->getnoball() == 0)return 0;
	this->noball = this->u->getnoball();
	this->prepareRandgen();
	while (this->budget > 0)this->sampleonce();
	double estimate = this->sum / this->nosample * this->noball;
	return estimate;
}