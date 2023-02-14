#include "testkit.h"
#include <iostream>
void testcase1()  {
	std::cout << "Input the number of testcases, the number of balls, the maxcost and the distribution of weights, 1 for uniform, 2 for normal, 3 for random\n";
	int noinstances, noballs, maxcost, distrib;
	std::cin >> noinstances >> noballs>> maxcost>>distrib;
	testTest(noinstances, noballs, maxcost, distrib);
}

void testcase2() {
	std::cout << "Input the number of testcases, the number of balls, the maxcost, the probalility for each edge to be spawned, the max number of cycles and the max cycle length\n";
	std::cout << "Input 0 for max number of cycle to prevent cycle creation.\n";
	int noinstances, noballs, maxcost, maxnocycle, maxcyclelen;
	double prob;
	std::cin >> noinstances >> noballs >> maxcost >> prob >> maxnocycle >> maxcyclelen;
	dgtestTest(noinstances, noballs, maxcost, prob, maxnocycle, maxcyclelen);
}