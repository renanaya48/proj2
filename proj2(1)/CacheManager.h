#ifndef PROJ2_CACHEMANAGER_H
#define PROJ2_CACHEMANAGER_H

#include <map>

using namespace std;
template <class Problem, class Solution>
class CacheManager {
    //member
    map <Problem, Solution> problemsAndSolutions;

public:
    /**
     *
     * @param problem the problem
     * @return true if the problem already have a solution. else-false
     */
    virtual bool haveSolution(Problem problem) = 0;
    /**
     *
     * @param problem the problem to get it solution
     * @return the solution to the problem
     */
    virtual Solution getSolution(Problem problem) = 0;
    /**
     * the function save the problem and the solution
     * @param solution the solution to save
     * @param problem the problem to save
     */
    virtual void saveSolution(Solution solution, Problem problem) = 0;
    //distructor
    virtual ~CacheManager(){};
};


#endif //PROJ2_CACHEMANAGER_H
