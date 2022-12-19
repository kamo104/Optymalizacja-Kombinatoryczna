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
#include "genetic.h"
#include "greedy.h"

using namespace std::chrono;

//  TODO make academy (save some weaker specimen and grow them)

// possible arguments: 
// -g (--generate) [nodesNum] [edgesNum] [outputFile]
// -r (--read) [filename]
// -s (--solve) (whether or not to solve the generated/read graph)
// --print (prints the generated/read graph to stdout)
// -p (--population) [populationSize]
// -e (--elite) [elitePercent] (what percentage of the population is considered "elite" (int))
// --parent [parentPercent] (what percentage of the population will become parents)
// -c (--crossover) [crossoverPercent] (what percantage of all children(excluding the elite) will come from crossover)
// -m (--mutation) [mutationChance] (the probability of a random mutation at every step of a solving sequence)(1/10000)
// -f (--run-for) [runTime] (in seconds)
int main(int argc, char *argv[]){
    Graph graph;
    Genetic solver(&graph);
    bool solve=false;
    int runTime=180;
    //część losowo, a część zachłannie osobników wygenerować

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
        else if(std::strcmp(argv[i],"-p")==0 || std::strcmp(argv[i],"--population")==0){
            solver.populationSize = atoi(argv[i+1]);
            i+=1;
        }
        else if(std::strcmp(argv[i],"-e")==0 || std::strcmp(argv[i],"--elite")==0){
            solver.elitePercent = atoi(argv[i+1]);
            i+=1;
        }
        else if(std::strcmp(argv[i],"--parent")==0){
            solver.parentPercent = atoi(argv[i+1]);
            i+=1;
        }
        else if(std::strcmp(argv[i],"-c")==0 || std::strcmp(argv[i],"--crossover")==0){
            solver.crossoverPercent = atoi(argv[i+1]);
            i+=1;
        }
        else if(std::strcmp(argv[i],"-m")==0 || std::strcmp(argv[i],"--mutation")==0){
            solver.mutationChance = atoi(argv[i+1]);
            i+=1;
        }
        else if(std::strcmp(argv[i],"-s")==0 || std::strcmp(argv[i],"--solve")==0){
            solve=true;
        }
        else if(std::strcmp(argv[i],"-f")==0 || std::strcmp(argv[i],"--run-for")==0){
            runTime = atoi(argv[i+1]);
            i+=1;
        }
        else if(std::strcmp(argv[i],"--print")==0){
            std::cout << "\n";
            graph.print();
            std::cout << "\n\n";
        }
    }
    
    // IF -s NOT PRESENT END EXECUTION
    if(!solve) return 0;

    // GENERATING INITIAL POPULATION
    solver.generatePopulation();

    std::cout << solver.runFor(runTime) << std::endl;


    std::cout << "ended successfully!!" << std::endl;
    // TIMING
    // auto start = high_resolution_clock::now();

    // PUT THE SOLVING FUNCTION HERE

    // auto stop = high_resolution_clock::now();

    // double duration = (double)duration_cast<nanoseconds>(stop - start).count();

    // std::cout << "duration: " << duration*pow(10,-8) << "seconds" << "\n";
    
    return 0;
}