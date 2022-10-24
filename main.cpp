#include "graph.h"
#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <random>
#include <fstream>



int greedy(Graph &graph){
    int size = graph.graph.size();
    std::vector<int> coloring(size,0);
    // colors start with 1, 0 is uncolored

    //for each node check with its neighbours which color is available
    for(int i=0;i<size;i++){
        std::vector<int> neighColors;
        for(int &neigh : graph.graph[i]){
            neighColors.push_back(coloring[neigh]);
        }
        std::sort(neighColors.begin(),neighColors.end());

        // smallest available color
        int available=1;
        for(int &neighColor : neighColors) if(neighColor==available) available++;
        coloring[i] = available;
    }

    //check coloring for largest color
    int largest=0;
    for(int &color : coloring) color >largest ? largest = color : largest=largest;
    return largest;
}

int main(int argc, char *argv[]){ // arg1 = graph size, arg2 = edges num, arg3 = output file name
    // INITIALIZATION WHEN PIPING
    Graph graph;
    graph.readFromSTDIN(); // Ctrl+Z+ender or Ctrl+D+enter to stop

    // INITIALIZATION WHEN GENERATING
    // Graph graph(atoi(argv[1]), atoi(argv[2]));

    // EXPORT
    // std::ofstream fout(argv[3]);
    // graph.printInstance(fout);

    // RUNNING GREEDY
    std::cout<<greedy(graph);
    return 0;
}