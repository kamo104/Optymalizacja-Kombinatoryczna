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
    void generateRandomGraph(int size, int numOfEdges){
        graph.clear();
        // [size] components
        // joining [size] single components in random places such that we are left with one coherent component
        std::vector<int> t1(0,0); // vector of size 0
        std::vector<std::vector<int>> t2(size,t1); // vector of size [size] with t1 in every row
        std::vector<std::vector<std::vector<int>>> components; // list of graphs to connect

        // initialize components (each node connects only to itself)
        for(int i=0;i<size;i++){
            t2[i].push_back(i); // connection node0 -> node0 means that it's a one node graph
            components.push_back(t2);
            t2[i].clear();
        }

        // connect components to each other in a random order
        std::priority_queue< std::pair<int,int>, std::vector<std::pair<int,int>>, std::function<bool(std::pair<int,int>, std::pair<int,int>)> > pq(Compare);

        for(int i=0;i<size;i++) pq.push(std::make_pair(rand()%size,i));
        int g1 = pq.top().second;
        pq.pop();
        while(pq.size()>0){
            int g2 = pq.top().second;
            pq.pop();
            this->joinGraphs(components[g1],components[g2]);
        }

        // add random edges 
        // (we have [size]-1 edges)
        // pick two random nodes and make an edge between them
        while(numOfEdges-->size-1){
            int n1 = rand()%size;
            int n2 = rand()%size;
            bool add=1;
            if(n1==n2){
                numOfEdges++;
                continue;
            }
            for(int &node : components[g1][n1]){
                if (node == n2){
                    numOfEdges++;
                    add=0;
                    break;
                }
            }

            if(add){
                components[g1][n1].push_back(n2);
                components[g1][n2].push_back(n1);
            }
            
        }

        this->graph = components[g1];
        return;
    }

    void readFromSTDIN(){
        int size;
        int n1,n2;
        std::cin>> size;

        std::vector<int> t1(0,0); // vector of size 0
        std::vector<std::vector<int>> t2(size,t1); // vector of size [size] with t1 in every row
        for(int i=0;i<size;i++){
            t2[i].push_back(i);
        }
        while(std::cin>>n1>>n2){
            t2[n1-1].push_back(n2-1);
            t2[n2-1].push_back(n1-1);
        }
        this->graph = t2;
    }
    
    void print(){
        for(int i=0;i<graph.size();i++){
            for(int j=0;j<graph[i].size();j++){
                std::cout<<graph[i][j]<<" ";
            }
            std::cout<<std::endl;
        }
    }

    Graph(){
    }
    
    Graph(int size, int numberOfEdges){
        this->generateRandomGraph(size, numberOfEdges);
    }
    
};