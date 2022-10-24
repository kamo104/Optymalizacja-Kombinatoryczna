#include "graph.h"
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

using namespace std::chrono;

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

// possible arguments: 
// -g (--generate) [nodesNum] [edgesNum] [outputFile]
// -r (--read) [filename]
int main(int argc, char *argv[]){
    std::cout << std::setprecision(8) << std::fixed;
    Graph graph;
    
    // argument parsing
    for (int i=0;i<argc;i++){
        if(std::strcmp(argv[i],"-g")==0 || std::strcmp(argv[i],"--generate")==0){
            
            graph.generateRandomGraph(atoi(argv[i+1]),atoi(argv[i+2]));
            // EXPORT
            std::ofstream fout(argv[i+3]);
            graph.printToStream(fout);
            i+=3;
            continue;
        }
        else if(std::strcmp(argv[i],"-r")==0 || std::strcmp(argv[i],"--read")==0){
            std::ifstream fin(argv[i+1]);
            graph.readFromStream(fin);
            i+=1;
        }
    }

    // DEBUG
    // graph.generateRandomGraph(10,100);
    // graph.print();
    
    // RUNNING GREEDY
    auto start = high_resolution_clock::now();
    int result= greedy(graph);
    auto stop = high_resolution_clock::now();
    double duration = (double)duration_cast<nanoseconds>(stop - start).count();
    std::cout<<"min colors: "<< result << "\n";
    std::cout<<"duration: "<< duration*pow(10,-8) <<"seconds"<<"\n";
    
    return 0;
}