#include "greedy.h"
#include "graph.h"

int greedy(Graph* graph, std::vector<int> sequence){ //std::vector<int> sequence
    std::vector<int> coloring(graph->size(),0); 
    // colors start from 1, 0 is uncolored

    //for each node check with its neighbours which color is available
    for(auto &i : sequence){
        
        std::vector<int> neighColors;

        for(int &neigh : graph->graph[i]) neighColors.push_back(coloring[neigh]);

        std::sort(neighColors.begin(),neighColors.end());

        // smallest available color
        int smallestAvailable=1;
        for(int &neighColor : neighColors){
            if(neighColor == 0 || neighColor < smallestAvailable) continue;  //if the neigh is 0 dont count up
            else if(neighColor==smallestAvailable) smallestAvailable++;
            else break; // if we were counting up and the next color is not matching (neighColor!=smallestAvailable)
        } 
        coloring[i] = smallestAvailable;
    }

    //check coloring for largest color
    int largest=1;
    for(int &color : coloring) color > largest ? largest = color : largest=largest;
    return largest;
}