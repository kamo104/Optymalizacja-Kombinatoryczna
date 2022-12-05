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
    int populationSize;
    int elitePercent;
    int parentPercent;
    int crossoverPercent;
    int mutationChance;

    void generatePopulation();

    int scorePopulation();

    void selectElite();

    void selectParents();

    void generateChildren();

    void updatePopulation();

    Genetic(Graph* graph);
};

#endif