#include <iostream>
#include "urn.h"
#include "algorithm.h"
#include "testcases.h"
#include "tools.h"
int main()
{
   /* int noball;
    std::cout << "Input the number of balls in the urn\n";
    std::cin >> noball;
    urn* u = new urn(noball, true);
    std::cout << "The weights are:" << std::endl;
    u->printweights();
    std::cout << u->getsum()<<std::endl;
    std::cout << "Input the max cost allowed" << std::endl;
    int maxcost;
    std::cin >> maxcost;
    sampler samp(maxcost, u);
    double estimate = samp.dosample();
    std::cout << "estimate: " << estimate << ", actual value: " << u->getsum();*/
    int cont = 1;
    int choice;
    std::cout << "Should test data be generated or inputed? 1 for the former, others for the latter\n";
    std::cin >> choice;
    if (choice == 1) {
        while (cont == 1) {
            testcase1();
            //testcase2();
            std::cout << "continue? (1 for continue)" << std::endl;
            std::cin >> cont;
        }
    }
    else {
        testcase3();
    }
    return 0;
}

