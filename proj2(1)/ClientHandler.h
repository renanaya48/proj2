#ifndef PROJ2_CLIENTHANDLER_H
#define PROJ2_CLIENTHANDLER_H

#include <iostream>
#include <fstream>

class ClientHandler{

public:
    /**
     * handle one client
     * @param newSockFd socket
     */
    virtual void handleClient(int newSockFd) = 0;
    //distructor
    virtual ~ClientHandler(){};
};

#endif //PROJ2_CLIENTHANDLER_H
