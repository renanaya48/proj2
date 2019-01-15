#ifndef PROJ2_BFS_H
#define PROJ2_BFS_H

#include "Searcher.h"
#include <unordered_set>
#include <list>
#include <string.h>
#include "BackTrace.h"

using namespace std;

template <class Solution, class T>
class BFS: public Searcher<Solution, T> {
    //members
    int nodesEvaluated;
    BackTrace<T>* back;
    double cost;

public:
    //constructor
    BFS(){
        this->nodesEvaluated = 0;
    }
/**
 *
 * @return the price
 */
    double getCost(){
        return this->cost;
    }
    //distructor
    virtual ~BFS(){};
/**
 * BFS scan
 * @param toSearch the graph
 * @return the node by BFS scan
 */
    string search(Searchable<T>* toSearch){
        list<State<T>*> open;
        unordered_set<State<T>*> openHash;
        unordered_set<State<T>*> close;
        list<State<T>*> backTraceList;
        State<T>* goal = toSearch->getGoalState();

        //all the nodes
        open.push_back(toSearch->getInitialState());
        openHash.insert(toSearch->getInitialState());

        //go on all the nodes
        while(!open.empty()){
            //get the first node
            State<T>* state = open.front();
            open.pop_front();
            openHash.erase(state);
            //mark the node as visited
            close.insert(state);
            //count +1 node
            this->nodesEvaluated++;

            //if we got to the goal state
            if(state->equals(goal)){
                return this->back->backTrace(state, toSearch, cost);
            }

            //get the neighbors
            list<State<T>*> succerssors = toSearch->getAllPossibleStates(state);

            //go on all the neighbors
            while (!succerssors.empty()){
                State<T>* temp = succerssors.front();
                succerssors.pop_front();
                //not visited
                if ((!close.count(temp)) && (!openHash.count(temp))){
                    open.push_back(temp);
                    temp->setParent(state);
                    openHash.insert(temp);
                } else if (openHash.count(temp)){
                    temp->setParent(state);
                    close.insert(temp);
                    openHash.erase(temp);
                }
            }
        }
        printf("No route found.");
        return "-1";
    }
/**
 *
 * @return the number of nodes evaluated
 */
    int getNumberOfNodesEvaluated(){
        return this->nodesEvaluated;
    }
};


#endif //PROJ2_BFS_H
