
#include "urn.h"
#include <random>
#include <map>
#include <iostream>
#include <iomanip>
#include <cmath>
urn::urn(int noballs) { this->setnoball(noballs); this->weights = std::map<int, int>(); }
urn::urn(int noballs, int mode) { //grw is short for general random weights
	this->setnoball(noballs);
	if (mode == 1)this->generateuniweights();
	else if (mode == 2)this->generatenormweights();
	else this->generaterandweights();
}
int urn::getnoball() { return noball; }
void urn::setnoball(int newno) { this->noball = newno; }
int urn::getweight(int index) { return weights[index]; }
void urn::setweight(int index, int weight) { this->weights[index] = weight; }
int urn::getsum() { return this->sum; }
void urn::setsum(int sum) { this->sum = sum; }
void urn::generateuniweights() {
	this->sum = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(1, noball);
	for (int i = 0; i < this->noball; i++) {
		int weight = distrib(gen);
		this->setweight(i, weight);
		this->sum += weight;
	}
}
void urn::generatenormweights() {
	this->sum = 0;
	std::random_device rd;
	std::mt19937 gen(rd());
	std::normal_distribution<> distrib(-10, noball);
	for (int i = 0; i < this->noball; i++) {
		int weight = (int)abs(distrib(gen)) % noball + 1;
		this->setweight(i, weight);
		this->sum += weight;
	}
}

void urn::generaterandweights() {
	this->sum = 0;
	std::srand(time(0));
	for (int i = 0; i < this->noball; i++) {
		int weight = std::rand() % noball + 1;
		this->setweight(i, weight);
		this->sum += weight;
	}
}
void urn::printweights() {
	int width = 0, maxno = this->noball;
	for (; maxno > 0; width++)maxno /= 10;
	std::cout << width << std::endl;
	for (int i = 0; i < this->noball; i++) {
		std::cout << std::setw(width) << std::setfill(' ') << this->getweight(i)<< ",";
		if (i % 10 == 9)std::cout << std::endl;
	}
}

urn::urn(struct params p) {
	int noballs = p.noball;
	int mode = p.mode;
	this->setnoball(noballs);
	if (mode == 1)this->generateuniweights();
	else if (mode == 2)this->generatenormweights();
	else this->generaterandweights();
}