#pragma once
#include "dgurn.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>

static inline int mapv2b(std::map<std::string, int>* dict, std::string node, int*serial) {
	if ((*dict)[node] == 0) {
		int ret = (*serial)++;
		(*dict)[node] = ret;
		return ret;

	}
	else return (*dict)[node];
}
dgurn* fromntfile(std::string path, int groundtruthsum);
