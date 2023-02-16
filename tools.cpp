#include "tools.h"

dgurn* fromntfile(std::string path, int groundtruthsum) {
	std::ifstream ntfile;
	int serial = 1;
	std::map<std::string, int> dict;
	ntfile.open(path);
	if (!ntfile.is_open()) {
		std::cout << "file not open!" << std::endl;
		return nullptr;
	}
	std::vector<std::vector<int>> edges;
	while (ntfile) {
		std::string line, node1, node2;
		std::getline(ntfile, line);
		int pos = line.find(' '), ver1, ver2;
		pos++;
		node1 = line.substr(0, pos - 1);
		if (node1.size() <= 6)continue;
		pos = line.find(' ', pos) + 1;
		int end = line.find(' ', pos);
		node2 = line.substr(pos, end - pos);
		if (node1 == node2)std::cout << node1 << std::endl;
		ver1 = mapv2b(&dict, node1, &serial);
		ver2 = mapv2b(&dict, node2, &serial);
		edges.push_back(std::vector<int>({ ver1 - 1, ver2 - 1 }));

	}
	return new dgurn(&edges, serial - 1, groundtruthsum);
}
