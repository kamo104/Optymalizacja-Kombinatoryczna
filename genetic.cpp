#include "genetic.h"
#include "graph.h"
#include "greedy.h"

std::vector<int> generateRandomSequence(int size){
    return generateRandomSequenceInRange(size,0,size);
}

std::vector<int> generateRandomSequenceInRange(int size, int rangeStart, int rangeEnd){
    std::vector<int> sequence;
    std::priority_queue< std::pair<int,int>, std::vector<std::pair<int,int>>, std::function<bool(std::pair<int,int>, std::pair<int,int>)>> pq(comparePairs);
    int rangeSpan = rangeEnd-rangeStart;
    for(int i=rangeStart;i<rangeEnd;i++) pq.push(std::make_pair(rand()%rangeSpan+rangeStart,i));

    while(size--){
        sequence.push_back(pq.top().second);
        pq.pop();
    }
    return sequence;
}



void Genetic::generatePopulation(){
    std::vector<std::vector<int>> population;

    for(int i=0;i<this->populationSize;i++) population.push_back(generateRandomSequence(this->graph->size()));

    this->population = population;
}

int Genetic::scorePopulation(){
    std::vector<std::pair<int,int>> scores;
    for(int i=0;i<this->populationSize;i++){
        std::pair<int,int> scorePerson;
        scorePerson.first = greedy(this->graph,this->population[i]);
        scorePerson.second = i;
        scores.push_back(scorePerson);
    } 
    sort(scores.begin(),scores.end());
    this->scores = scores;
    return scores[0].first;
}

void Genetic::selectElite(){
    std::vector<int> elite;

    int eliteCutoff = this->scores.size()*this->elitePercent/100;

    for (int i=0;i<eliteCutoff;i++) elite.push_back(this->scores[i].second);

    this->elites = elite;
}

void Genetic::selectParents(){
    int parentsAmount = this->scores.size()*this->parentPercent/100;

    this->parents = generateRandomSequenceInRange(parentsAmount,0,this->scores.size());
}

std::vector<int> Genetic::mutateSequence(std::vector<int> sequence){
    std::vector<int> newSequence = sequence;
    for(int i=0;i<newSequence.size();i++){
        int chance = rand()%10000;
        // if the chance is higher than mutation chance dont mutate, if it's not => mutate
        if(chance>this->mutationChance){
            continue;
        }
        // pick a random member of sequence that comes after i
        int member = rand()%(newSequence.size()-i) + i;

        // switch places between i and member
        int save = newSequence[i];
        newSequence[i]=newSequence[member];
        newSequence[member] = save;
    }
    return newSequence;
}

std::vector<int> Genetic::crossover(std::vector<int> seq1,std::vector<int> seq2){
    
    return seq1;
}

void Genetic::generateChildren(){
    int childrenAmount = this->scores.size()-this->elites.size();

    int mutatedChildrenAmount = childrenAmount*(100-this->crossoverPercent)/100;

    int crossoverChildrenAmount = childrenAmount-mutatedChildrenAmount;

    std::vector<std::vector<int>> children;

    while(mutatedChildrenAmount--){
        int selectedParent = rand()%this->parents.size();
        children.push_back(this->mutateSequence(this->population[this->parents[selectedParent]]));
    }
    while(crossoverChildrenAmount--){
        int p1 = rand()%this->parents.size();
        int p2 = rand()%this->parents.size();
        children.push_back(this->crossover(this->population[this->parents[p1]],this->population[this->parents[p2]]));
    }
    this->children = children;
}

void Genetic::updatePopulation(){
    //keep elites and replace everyone else with the new children
    std::vector<std::vector<int>> newPopulation;
    for(int &elite:this->elites) newPopulation.push_back(this->population[elite]);
    for(std::vector<int> &child:this->children) newPopulation.push_back(child);
    
}

Genetic::Genetic(Graph* graph){
    this->graph = graph;
    this->populationSize=1;
    this->elitePercent=10;
    this->parentPercent=20;
    this->crossoverPercent=50;
}
