#ifndef PROJ2_SEARCHER_H
#define PROJ2_SEARCHER_H

#include "Searchable.h"

template <class Solution, class T>
class Searcher{

public:
    /**
     *
     * @param toSearch Searchable
     * @return the solution of the problem
     */
    virtual Solution search(Searchable<T>* toSearch) = 0;
    /**
     *
     * @return the number of the nodes
     */
    virtual int getNumberOfNodesEvaluated() = 0;
    /**
     *
     * @return the cost of the node
     */
    virtual double getCost() = 0;
    //distroctur
    virtual ~Searcher(){};

};

#endif //PROJ2_SEARCHER_H
