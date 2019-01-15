#ifndef PROJ2_ASTAR_H
#define PROJ2_ASTAR_H

#include "Searcher.h"
#include <unordered_set>
#include <list>
#include <string.h>
#include "BackTrace.h"
#include <map>

using namespace std;
template <class Solution, class T>
class Astar: public Searcher<Solution, T> {
    //members
    int nodesEvaluated;
    BackTrace<T>* back;
    double cost;


public:
    //constructor
    Astar() {
        this->nodesEvaluated = 0;
        cost = -1;
    }

    /**
     *
     * @return the price
     */
    double getCost(){
        return this->cost;
    }

    //distructor
    virtual ~Astar(){};

    /**
     *
     * @return the number of nodes evaluated
     */
    int getNumberOfNodesEvaluated(){
        return this->nodesEvaluated;
    }

    /**
     * A star search
     * @param toSearch the graph
     * @return the nodes by A*
     */
    string search(Searchable<T>* toSearch){
        list<State<T>*> open;
        map<State<T>*, double> costHash;
        list<State<T>*> backTraceList;
        State<T>* goal = toSearch->getGoalState();

        //the state of the goal
        string name = goal->getState();
        char* divide = const_cast<char *>(name.c_str());
        int goalI = stoi(strtok(divide, ","));
        int goalJ = stoi(strtok(NULL, ","));

        //get all nodes
        open.push_back(toSearch->getInitialState());
        costHash.insert(pair<State<T>*, double>(toSearch->getInitialState(), toSearch->getInitialState()->getCost()));

        //go on all the nodes
        while(!open.empty()){
            //get the first
            State<T>* state = open.front();
            open.pop_front();
            //get the price
            double stateCost = costHash.find(state)->second;
            //count +1
            this->nodesEvaluated++;

            //if we get to the goal
            if(state->equals(goal)){
                return this->back->backTrace(state, toSearch, cost);
            }

            //get the neighbors
            list<State<T>*> succerssors = toSearch->getAllPossibleStates(state);

            //go on all the neighbors
            while (!succerssors.empty()){
                //get the first
                State<T>* temp = succerssors.front();
                succerssors.pop_front();

                string nameTemp = temp->getState();
                char* divideTemp = const_cast<char *>(nameTemp.c_str());
                int tempI = stoi(strtok(divideTemp, ","));
                int tempJ = stoi(strtok(NULL, ","));

                double h = abs(tempI - goalI) + abs(tempJ - goalJ);
                double g = temp->getCost() + stateCost;
                double newCost = h + g;

                //dot visited
                if (costHash.count(temp)) {
                    double preCost = costHash.find(temp)->second;
                    if (newCost < preCost){
                        temp->setParent(state);
                        costHash.insert(pair<State<T>*, double>(temp, newCost));
                    }
                    //visited
                } else {
                    open.push_back(temp);
                    temp->setParent(state);
                    costHash.insert(pair<State<T>*, double>(temp, newCost));
                }
            }
        }
        printf("No route found.");
        return "-1";
    }
};

#endif //PROJ2_ASTAR_H
