#include "dgurn.h"
#include <random>
#include <queue>
dgurn::dgurn(int noballs,double prob) {
	this->graph = std::map<int,std::set<int>>();
	this->setnoball(noballs); 
	this->generateepgraph(prob);
	this->computesum();
}

void dgurn::generateepgraph(double prob) {
	int noball = this->getnoball();
	std::random_device rd;
	std::mt19937 gen(rd());
	double upperlimit = 1 / prob;
	std::uniform_real_distribution<> distrib(0, upperlimit);
	for (int i = 0; i < noball; i++) {
		for (int j = 0; j < noball && j != i; j++) {
			double rand = distrib(gen);
			if (rand <= 1) this->graph[i].insert(j);
		}
	}
}
void dgurn::computesum() {
	int sum = 0;
	int noball = this->getnoball();
	for (int i = 0; i < noball; i++)sum += this->getweight(i);
	this->setsum(sum);
}

int dgurn::getweight(int index) {
	std::queue<int> level;
	std::set<int> reachable;
	reachable.insert(index);
	auto end = graph[index].end();
	for (auto itr = graph[index].begin(); itr != end; itr++) {
		level.push(*itr);
		reachable.insert(*itr);
	}
	while (!level.empty()) {
		std::set<int> nextlevelset;
		while (!level.empty()) {
			int vertice = level.front();
			level.pop();
			end = graph[vertice].end();
			for (auto itr = graph[vertice].begin(); itr != end; itr++) {
				if (reachable.find(*itr) == reachable.end()) {
					nextlevelset.insert(*itr);
					reachable.insert(*itr);
				}
			}
		}
		for (auto itr = nextlevelset.begin(); itr != nextlevelset.end(); itr++) {
			level.push(*itr);
		}
	}
	return reachable.size();
}

void dgurn::spawncycle(int vertice,int length) {
	int noball = this->getnoball(), start = vertice;
	
	std::random_device rd;
	std::mt19937 gen(rd());
	std::vector<int> path;
	path.push_back(vertice);
	std::uniform_int_distribution<> distrib(0, noball - 1);
	if (length < noball / 2) {
		std::set<int> incycle;
		incycle.insert(vertice);
		for (; length > 1; length--) {
			int candi = distrib(gen);
			while (incycle.find(candi) != incycle.end()) {
				candi = distrib(gen);
			}
			path.push_back(candi);
			incycle.insert(candi);
		}
	}
	else {
		std::vector<int> vertexes;
		for (int i = 0; i < noball; i++) {
			if(i!=vertice)vertexes.push_back(i);
		}
		srand(time(0));
		std::random_shuffle(vertexes.begin(), vertexes.end());
		for (int i = 0; i < length; i++)path.push_back(vertexes[i]);
	}
	path.push_back(vertice);
	drawcycle(path);
}
void dgurn::drawcycle(std::vector<int> path) {
	int length = path.size(),start = path[0];
	for (int i = 1; i < length-1; i++) {
		if (graph[start].find(path[i]) != graph[start].end())graph[start].insert(path[i]);
		start = path[i];
	}
}

dgurn::dgurn(struct params p) {
	int noballs = p.noball;
	double prob = p.prob;
	this->graph = std::map<int, std::set<int>>();
	this->setnoball(noballs);
	this->generateepgraph(prob);
	this->computesum();
}