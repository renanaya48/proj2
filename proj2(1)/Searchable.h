#ifndef PROJ2_SEARCHABLE_H
#define PROJ2_SEARCHABLE_H


#include "State.h"
#include <list>

using namespace std;

template <class T>
class Searchable{
    //members
    State<T> start;
    State<T> goal;

public:
    /**
     *
     * @return the initial state
     */
    virtual State<T>* getInitialState() = 0;
    /**
     *
     * @return the goal state
     */
    virtual State<T>* getGoalState() = 0;
    /**
     *
     * @param state the current state
     * @return  all the possible states
     */
    virtual list<State<T>*> getAllPossibleStates(State<T>* state) = 0;
    //distructor
    virtual ~Searchable(){};

};

#endif //PROJ2_SEARCHABLE_H
