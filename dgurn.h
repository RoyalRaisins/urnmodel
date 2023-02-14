#include "urn.h"
#include <utility>
#include <map>
#include <set>
class dgurn:public urn {  //dgurn stands for directed graph urn
private:
	std::map<int, std::set<int>> graph;
	int j;
public:
	dgurn():urn() {};
	dgurn(int noballs, double prob);
	dgurn(int noballs, double prob, int mode);
	dgurn(struct params p);

	void generateepgraph(double prob); //each edge has equal probability to be generated, probability will not be precise due to limitation of computor, ep stands for equal probability
	int getweight(int index);
	void computesum();

	void spawncycle(int vertice, int length);
	void randcylify(int maxno, int maxlength);
	void drawcycle(std::vector<int> path);
};
