#include "dgurn.h"
#include <random>
#include <queue>
#include <cmath>
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
	for (int i = 0; i < noball; i++)this->graph[i] = std::set<int>();
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
	//reachable.insert(index);
	auto end = graph[index].end();
	for (auto itr = graph[index].begin(); itr != end; itr++) {
		level.push(*itr);
		reachable.insert(*itr);
	}
	std::cout << reachable.size() << std::endl;
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
		for (int i = 0; i < length-1; i++)path.push_back(vertexes[i]);
	}
	path.push_back(vertice);
	drawcycle(path);
}
void dgurn::drawcycle(std::vector<int> path) {
	int length = path.size(),start = path[0];
	for (int i = 1; i < length-1; i++) {
		if (graph[start].find(path[i]) == graph[start].end())graph[start].insert(path[i]);
		start = path[i];
	}
}

void dgurn::randcylify(int maxno, int maxlength) {
	int noballs = this->getnoball();
	maxlength = std::min(noballs, maxlength);
	srand(time(0));
	int nocycle = rand() % maxno + 1;
	for (int i = 0; i < nocycle; i++) {
		int vertice = rand() % noballs, len = rand()%maxlength + 1;
		spawncycle(vertice, len);
	}
}

dgurn::dgurn(struct params p) {
	int noballs = p.noball, maxnocycle = p.maxnocycle, maxcyclelen = p.maxcyclelen;
	double prob = p.prob;
	this->graph = std::map<int, std::set<int>>();
	this->setnoball(noballs);
	this->generateepgraph(prob);
	if (maxnocycle > 0) {
		randcylify(maxnocycle, maxcyclelen);
	}
	this->computesum();
}

dgurn::dgurn(std::vector<std::vector<int>> *edges, int noballs, int groundtruthsum) {
	this->graph = std::map<int, std::set<int>>();
	this->setnoball(noballs);
	int noedge = edges->size();
	for (int i = 0; i < noballs; i++)this->graph[i] = std::set<int>();
	for (std::vector<int> v : (*edges)) {
		this->graph[v[0]].insert(v[1]);
	}
	if (groundtruthsum < 0) {
		clock_t start, end;
		start = clock();
		this->computesum();
		end = clock();
		std::cout << "Calculation for sum has taken " << end - start << " milliseconds.\n";
	}
	else this->setsum(groundtruthsum);
}

//d:\ggg.txt -1