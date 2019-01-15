#ifndef PROJ2_MYCLIENTHANDLER_H
#define PROJ2_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include <string>
#include "CacheManager.h"
#include "Solver.h"

template <class Problem, class Solution>
class MyClientHandler: public ClientHandler{
    //members
    CacheManager<string, string>* cacheManager;
    Solver<string, string>* solver;

public:
    //constructor
    MyClientHandler(CacheManager<string, string>* cacheManager, Solver<string, string>* solver);
    /**
     * handle one client
     * @param newSockFD the client's socket
     */
    virtual void handleClient(int newSockFD);
    //distructor
    virtual ~MyClientHandler(){};

};


#endif //PROJ2_MYCLIENTHANDLER_H
