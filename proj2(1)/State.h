#ifndef PROJ2_STATE_H
#define PROJ2_STATE_H


//TODO nodeState
template <class T>
/**
 * State calss
 * @tparam T the generic state
 */
class State {
    //members
    T state;
    double cost;
    State<T>* parent;

public:
    //constructor
    State(){
        this->cost = 0;
    }
/**
 * get the price of the element
 * @return hoe much it cost
 */
    double getCost(){
        return this->cost;
    }
    //distructor
    virtual ~State(){};
/**
 *
 * @param s the state
 * @return true if equal, false -else
 */
    bool equals(State<T>* s){
        //if the states are equal - return true
        if (this->state == s->getState()){
            return true;
            //not equal
        } else {
            //return false
            return false;
        }
    }
    /**
     *
     * @return the parent of the vertex
     */
    State<T>* getParent(){
        return this->parent;
    }
    /**
     *
     * @return the state of the element
     */
    T getState(){
        return this->state;
    }
    /**
     * set the parent of the vertex
     * @param parent1 the parent to change
     */
    void setParent(State<T>* parent1){
        this->parent = parent1;
    }
    /**
     * set the state
     * @param state1 the state to change to
     */
    void setState(T state1){
        this->state = state1;
    }

    /**
     * change the price
     * @param cost1 the new price
     */
    void setCost(int cost1){
        this->cost = cost1;
    }
};


#endif //PROJ2_STATE_H
