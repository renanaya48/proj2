#ifndef PROJ2_MATRIXSEARCHABLE_H
#define PROJ2_MATRIXSEARCHABLE_H

#include "Searchable.h"
#include <list>
#include <vector>
#include <string>
#include <string.h>

using namespace std;

template <class T>
class MatrixSearchable: public Searchable<T>{
    //members
    vector<vector<State<T>*>> matrix;
    State <T>* initialState;
    State <T>* goalState;
    int rowCount;

public:
    //constructor
    MatrixSearchable(){
        this->rowCount = 0;
    }

    /**
     *
     * @return the initial state
     */
    State<T>* getInitialState(){
        return this->initialState;
    }
    /**
     *
     * @return the goal state
     */
    State<T>* getGoalState(){
        return this->goalState;
    }
    /**
     * set the state
     * @param state the new state
     */
    void setGoalState(State<T>* state){
        this->goalState = state;
    }

    /**
     * set the initial state
     * @param state the new state
     */
    void setInitialState(State<T>* state){
        this->initialState = state;
    }
    /**
     *
     * @param state the current state
     * @return all the possible states
     */
    list<State<T>*> getAllPossibleStates(State<T>* state){
        list<State<T>*> succerssors;
        string name = state->getState();
        State<T>* temp;

        char* divide = const_cast<char *>(name.c_str());
        int i = stoi(strtok(divide, ","));
        int j = stoi(strtok(NULL, ","));
        int matrixSize = matrix[0].size() - 1;

        if ((j + 1) <= matrixSize){
            temp = matrix[i][j + 1];
            if(temp->getCost() != -1) {
                //right
                succerssors.push_back(matrix[i][j + 1]);
            }
        }
        if ((j - 1) >= 0){
            temp = matrix[i][j - 1];
            if(temp->getCost() != -1) {
                //left
                succerssors.push_back(matrix[i][j - 1]);
            }
        }
        if ((i + 1) <= (this->rowCount - 1)){
            temp = matrix[i + 1][j];
            if(temp->getCost() != -1) {
                //down
                succerssors.push_back(matrix[i + 1][j]);
            }
        }
        if ((i - 1) >= 0){
            temp = matrix[i - 1][j];
            if(temp->getCost() != -1) {
                //up
                succerssors.push_back(matrix[i - 1][j]);
            }
        }

        //the list of all the possible states
        return succerssors;

    }
/**
 * add a row to the matrix
 * @param row the row to add
 */
    void addRowToMatrix(string row){
        vector<State<T>*> rowVector;
        double cost;
        int col = 0;

        char* temp = const_cast<char *>(row.c_str());
        temp = strtok(temp, ",");

        while (temp != NULL) {
            cost = atof(temp);
            temp = strtok(NULL, ",");

            State<string>* newState = new State<string>();
            string name = to_string(this->rowCount) + "," + to_string(col);

            //set the state and the cost
            newState->setState(name);
            newState->setCost(cost);
            rowVector.push_back(newState);

            //add 1 to the colow
            col++;
        }

        this->matrix.push_back(rowVector);
        this->rowCount++;
    }
/**
 * create a matrix
 * @param newMatrixString the string to create the matrix from
 */
    void createMatrix(string newMatrixString){
        list<string>strings;
        char* temp = const_cast<char *>(newMatrixString.c_str());
        temp = strtok(temp, ";");

        while (temp != NULL){
            strings.push_back(temp);
            temp = strtok(NULL, ";");
        }

        int size = strings.size();
        int count = 0;

        list<string>::iterator it;
        it = strings.begin();

        //add the string to the row of the matrix
        while (count != size - 3) {
            string newRow = (*it);
            this->addRowToMatrix(newRow);
            it++;
            count++;
        }

        //the last values will be the initial state and the goal state
        string start = (*it);

        temp = const_cast<char*>(start.c_str());
        int i = stoi(strtok(temp, ","));
        int j = stoi(strtok(NULL, ","));

        setInitialState(this->getStateByIndex(i, j));
        it++;

        start = *it;
        temp = const_cast<char*>(start.c_str());


        i = stoi(strtok(temp, ","));
        j = stoi(strtok(NULL, ","));

        //set the goal state
        setGoalState(this->getStateByIndex(i, j));
    }
/**
 *
 * @param row the row
 * @param col the colum
 * @return the state by the index of row and col
 */
    State<T>* getStateByIndex(int row, int col){
        return this->matrix[row][col];
    }

    //distructor
    virtual ~MatrixSearchable(){
        //delete the all matrix
        int size = this->matrix.size();
        for(int i = 0; i < size; ++i){
            vector<State<string>*> temp = this->matrix[i];
            int tempSize = temp.size();
            for(int j = 0; j < tempSize; ++j){
                delete temp[j];
            }
        }
    };

};


#endif //PROJ2_MATRIXSEARCHABLE_H
