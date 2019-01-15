#ifndef PROJ2_MATRIXSOLVER_H
#define PROJ2_MATRIXSOLVER_H

#include "Solver.h"
#include "Searcher.h"
#include <string>
#include <list>
#include "MatrixSearchable.h"

template <class Problem, class Solution, class T>
class MatrixSolver: public Solver<Problem, Solution> {
    //members
    Searcher<Solution, T>* searcher;
    MatrixSearchable<T>* matrix;

public:
    //constructor
    MatrixSolver(Searcher<Solution, T>* search){
        this->searcher = search;
    }
    /**
     *
     * @param problem the problem to solve
     * @return the solution
     */
    string solve(string problem){
        //create matrix
        matrix = new MatrixSearchable<T>();
        matrix->createMatrix(problem);

        string result = this->searcher->search(matrix);

        return result;
    }

    //distructor
    virtual ~MatrixSolver(){
        delete this->matrix;
    };
};


#endif //PROJ2_MATRIXSOLVER_H
