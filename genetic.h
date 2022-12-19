#ifndef GENETIC_H
#define GENETIC_H

#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <random>
#include <fstream>
#include <chrono>
#include <cstring>
#include <iomanip>

#include "graph.h"

std::vector<int> generateRandomSequence(int size);

std::vector<int> generateRandomSequenceInRange(int size, int rangeStart, int rangeEnd);

std::vector<int> mutate(std::vector<int> sequence);

class Genetic{
    private:
    class Graph* graph;
    std::vector<std::vector<int>> population;
    std::vector<std::pair<int,int>> scores; // {(score, id in population),...}
    std::vector<int> parents; // ids in population
    std::vector<int> elites; // ids in population
    std::vector<std::vector<int>> children;

    std::vector<int> mutateSequence(std::vector<int> sequence);
    std::vector<int> crossover(std::vector<int> s1,std::vector<int> s2);


    public:
    int populationSize=10;
    int elitePercent=10;
    int parentPercent=20;
    int crossoverPercent=50;
    int mutationChance=100;
    // this->populationSize=1;
    // this->elitePercent=10;
    // this->parentPercent=20;
    // this->crossoverPercent=50;

    void generatePopulation();

    std::pair<int,int> scorePopulation();

    void selectElite();

    void selectParents();

    void generateChildren();

    void updatePopulation();

    int mainLoop(int times);

    int runFor(int time); // run for a given time in seconds
    
    Genetic(Graph* graph);
};

#endif