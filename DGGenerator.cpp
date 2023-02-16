﻿// DGGenerator.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

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
            //testcase1();
            testcase2();
            std::cout << "continue? (1 for continue)" << std::endl;
            std::cin >> cont;
        }
    }
    else {
        testcase3();
    }
    return 0;
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
