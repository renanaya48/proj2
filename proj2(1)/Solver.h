#ifndef PROJ2_SOLVER_H
#define PROJ2_SOLVER_H

//solver class
template <class Problem, class Solution>
class Solver{

public:
    /**
     * solve the problem
     * @param problem the problem to solve
     * @return the solution
     */
    virtual Solution solve(Problem problem) = 0;
    /**
     * distructor
     */
    virtual ~Solver(){};
};

#endif //PROJ2_SOLVER_H
