#pragma once

#include <vector>
#include <tuple>
#include <string>
#include <iostream>
#include <fstream>
#include <queue>
#include <limits>

using std::vector, std::tuple, std::string;
using std::ifstream, std::cout, std::endl;

class Graph {
private:
    int nodes;
    int edges;
    vector<std::vector<std::pair<int, int>>> adjList;

public:
    Graph();
    Graph(const string &fileName);

    void printAdjList();
    void shortestPath(int source, int destination);
};
