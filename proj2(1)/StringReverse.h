#ifndef PROJ2_STRINGREVERSE_H
#define PROJ2_STRINGREVERSE_H

#include "Solver.h"
#include <string>
using namespace std;
/**
 * StringReverse class
 */
class StringReverse: public Solver<string, string> {
public:
    StringReverse(){}
    string solve(string problem);
    ~StringReverse(){};
};

#endif //PROJ2_STRINGREVERSE_H
