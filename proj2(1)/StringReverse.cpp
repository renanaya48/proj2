#include "StringReverse.h"

/**
 * solve the string reverse problem
 * @param problem the problem to solve
 * @return the solver
 */
string StringReverse::solve(string problem){
    string result = "";
    int i = problem.length() - 1;
    //go all the string by reverse
    for(; i >= 0; i--){
        result += problem[i];
    }
    //return the result
    return result;
}
