#ifndef PROJ2_DFS_H
#define PROJ2_DFS_H

#include "Searcher.h"
#include "BackTrace.h"
#include <unordered_set>

using namespace std;
template <class Solution, class T>
class DFS: public Searcher<Solution, T> {
    //members
    int nodesEvaluated;
    BackTrace<T>* back;
    double cost;


public:
    //constructor
    DFS() {
        this->nodesEvaluated = 0;
    }
/**
 *
 * @return the cost of the node
 */
    double getCost(){
        return this->cost;
    }
/**
 *
 * @return the number of nodes evaluated
 */
    int getNumberOfNodesEvaluated() {
        return this->nodesEvaluated;
    }

    //distructor
    virtual ~DFS(){};


    /**
     * DFS scan
     * @param toSearch searchable
     * @return the nodes sorted by the DFS
     */
    string search(Searchable<T>* toSearch) {
        list<State<T>*> open;
        unordered_set<State<T>*> close;
        State<T>* state;
        State<T>* temp;
        State<T>* goal = toSearch->getGoalState();
        State<T>* start = toSearch->getInitialState();
        //all the nodes
        open.push_back(start);

        //go on all the nodes
        while (!open.empty()){
            //get the first node
            state = open.front();
            //pop from the list
            open.pop_front();

            //if we got to the goal state
            if(state->equals(goal)){
                return this->back->backTrace(state, toSearch, cost);
            }

            //if we didnt visit in the node
            if (!close.count(state)){
                //mark as visit
                close.insert(state);
                //count +1 node
                this->nodesEvaluated++;

                list<State<T>*> succerssors = toSearch->getAllPossibleStates(state);

                //for all the neighbors
                while (!succerssors.empty()){
                    temp = succerssors.front();
                    succerssors.pop_front();
                    if(close.count(temp))
                        continue;
                    temp->setParent(state);
                    open.push_back(temp);
                }
            }
        }
        printf("No route found.");
        return "-1";
    }

};

#endif //PROJ2_DFS_H
