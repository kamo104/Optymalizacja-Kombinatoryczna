#ifndef GRAPH_H    
#define GRAPH_H

#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <random>
#include <functional>
#include <fstream>

bool comparePairs(std::pair<int,int>, std::pair<int,int>);
bool compareTuples(std::tuple<int,int,int>, std::tuple<int,int,int>);

class Graph{
    public:
    std::vector<std::vector<int>> graph;

    private:
    void joinGraphs(std::vector<std::vector<int>>& g1,std::vector<std::vector<int>>& g2);


    public:
    int size();

    void generateRandomGraph(int size, int numOfEdges);

    void readFromSTDIN();

    void readFromStream(std::ifstream &stream);
    
    void print();

    void printToStream(std::ofstream &stream);

    Graph();
    
    Graph(int size, int numberOfEdges);
    
};

#endif