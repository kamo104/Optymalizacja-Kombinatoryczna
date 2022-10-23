#include <stdio.h>
#include <vector>
#include <queue>
#include <algorithm>
#include <iostream>
#include <random>
#include <functional>

bool Compare(std::pair<int,int> a, std::pair<int,int> b){   
    return a.first>b.first;
}

class Graph{
    public:
    std::vector<std::vector<int>> graph;

    private:
    void joinGraphs(std::vector<std::vector<int>>& g1,std::vector<std::vector<int>>& g2){ // takes references to graphs as inputs g1 <- g2
        // pick random node n1 from g1 and n2 from g2
        // create connection from n1 to n2 in a copy of g2
        // return the connected graph

        std::vector<int> g1Nodes(0,0);
        std::vector<int> g2Nodes(0,0);

        //get all nodes from the both graphs
        for(int i=0;i<g1.size();i++) if (g1[i].size()) g1Nodes.push_back(i);
        for(int i=0;i<g2.size();i++) if (g2[i].size()) g2Nodes.push_back(i);


        //pick the random points
        int n1=g1Nodes[rand()%g1Nodes.size()];
        int n2=g2Nodes[rand()%g2Nodes.size()];

        // add the edge from n1 to n2 in g1
        g1[n1].push_back(n2);
        g1[n2].push_back(n1);

        // add every edge from g2 to g1
        for (auto &node : g2Nodes) for(auto &neigh : g2[node]) g1[node].push_back(neigh);
        return;
    }


    public:
    void generateRandomGraph(int size){
        graph.clear();
        // [size] components
        // joining [size] single components in random places such that we are left with one coherent component
        std::vector<std::vector<std::vector<int>>> components; // list of graphs to connect
        std::vector<int> t1(0,0); // vector of size 0
        std::vector<std::vector<int>> t2(size,t1); // vector of size [size] with t1 in every row
        for(int i=0;i<size;i++){
            t2[i].push_back(i); // connection node0 -> node0 means that it's a one node graph
            components.push_back(t2);
            t2[i].clear();
        }
        std::priority_queue< std::pair<int,int>, std::vector<std::pair<int,int>>, std::function<bool(std::pair<int,int>, std::pair<int,int>)> > pq(Compare);

        for(int i=0;i<size;i++) pq.push(std::make_pair(rand()%size,i));
        int g1 = pq.top().second;
        pq.pop();
        while(pq.size()>0){
            int g2 = pq.top().second;
            pq.pop();
            this->joinGraphs(components[g1],components[g2]);
        }

        this->graph = components[g1];
        return;
    }
    void readFromSTDIN(){

    }

    Graph(){
    }
    
    Graph(int size){
        this->generateRandomGraph(size);
    }
    
};