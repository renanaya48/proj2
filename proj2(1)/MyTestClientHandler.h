#ifndef PROJ2_MYTESTCLIENTHANDLER_H
#define PROJ2_MYTESTCLIENTHANDLER_H

#include "ClientHandler.h"
#include "Solver.h"
#include "CacheManager.h"

template <class Problem, class Solution>
//       MyTestClientHandler class
class MyTestClientHandler : public ClientHandler {
    //members
    CacheManager<string, string>* cacheManager;
    Solver<string, string>* solver;

public:
    /**
     *
     * @param cacheManager CacheManager
     * @param solver the solve of the solution
     */
    MyTestClientHandler(CacheManager<string, string>* cacheManager, Solver<string, string>* solver);
    /**
     *
     * @param newSockFD the socket
     */
    virtual void handleClient(int newSockFD);
    //distructor
    virtual ~MyTestClientHandler(){};

};


#endif //PROJ2_MYTESTCLIENTHANDLER_H
