# genetic algorithm implementation in a graph coloring problem

## compilation command:

    g++ *.cpp -o main.exe

## possible arguments: 
* -g (--generate) \[nodesNum] \[edgesNum] \[outputFile]
* -r (--read) \[filename]
* -s (--solve) (whether or not to solve the generated/read graph)
* --print (prints the generated/read graph to stdout)
* -p (--population) \[populationSize]
* -e (--elite) \[elitePercent] (what percentage of the population is considered "elite" (int))
* --parent \[parentPercent] (what percentage of the population will become parents)
* -c (--crossover) \[crossoverPercent] (what percantage of all children(excluding the elite) will come from crossover)
* -m (--mutation) \[mutationChance] (the probability of a random mutation at every step of a solving sequence)(1/10000)
* -f (--run-for) \[runTime] (in seconds)