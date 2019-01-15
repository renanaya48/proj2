#ifndef PROJ2_BESTFS_H
#define PROJ2_BESTFS_H

#include <unordered_set>
#include <list>
#include <string.h>
#include "BackTrace.h"
#include "Searcher.h"

using namespace std;
template <class Solution, class T>
class BestFS: public Searcher<Solution, T> {
    //members
    int nodesEvaluated;
    BackTrace<T>* back;
    double cost;

public:
    //constructor
    BestFS(){
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
    virtual ~BestFS(){};
/**
 *
 * @return the number of nodes evaluated
 */
    int getNumberOfNodesEvaluated(){
        return this->nodesEvaluated;
    }

/**
 *
 * @param open the nodes
 * @param state the states
 * @return who should be first
 */
    list<State<T>*> sort(list<State<T>*> open, State<T>* state){
        list<State<T>*> result;
        State<T>* stateOpen;
        //no nodes
        if (open.empty()){
           result.push_back(state);
        } else {
            //get the first node
            stateOpen = open.front();
            open.pop_front();
            //check who should be first
            if (stateOpen->getCost() >= state->getCost()){
                result.push_back(state);
            } else {
                //put the best in the result
                result.push_back(stateOpen);
            }
        }

        //return the best
        return result;
    }

    /**
     *
     * @param toSearch the graph to search
     * @return the nodes by best BFS
     */
    string search(Searchable<T>* toSearch){
        list<State<T>*> open;
        unordered_set<State<T>*> close;
        list<State<T>*> backTraceList;
        State<T>* goal = toSearch->getGoalState();

        //get all the nodes
        open.push_back(toSearch->getInitialState());

        //go on all the nodes
        while(!open.empty()){
            //get the first node
            State<T>* state = open.front();
            open.pop_front();
            //mark as visited
            close.insert(state);
            //count +1
            this->nodesEvaluated++;

            //if we get to the goal state
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
                //if not visited
                if (!close.count(temp)){

                    string name = temp->getState();
                    string parentName = state->getState();

                    char *divide = const_cast<char *>(name.c_str());
                    int childI = stoi(strtok(divide, ","));
                    int childJ = stoi(strtok(NULL, ","));

                    char *divideParent = const_cast<char *>(parentName.c_str());
                    int parentI = stoi(strtok(divideParent, ","));
                    int parentJ = stoi(strtok(NULL, ","));

                    //check who should be first by order
                    if (childJ < parentJ) {
                        continue;
                    }
                    if (childI < parentI){
                        continue;
                    }
                    temp->setParent(state);
                    open = sort(open, temp);
                }
            }
        }
        printf("No route found.");
        return "-1";
    }

};


#endif //PROJ2_BESTFS_H
