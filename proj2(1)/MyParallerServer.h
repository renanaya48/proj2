#ifndef PROJ2_MYPARALLERSERVER_H
#define PROJ2_MYPARALLERSERVER_H

#include <iostream>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <functional>
#include "Server.h"
#include "ClientHandler.h"
#include <time.h>

using namespace server_side;

class MyParallerServer : public Server {
public:
    //Constructor
    MyParallerServer();

    /**
     * The function open a server that listem to multiple clients simultaneously
     */
    void open(int port, ClientHandler *clientHandler);

    /**
     * he function stop the server
     * @param socketFd the socket
     */
    void stop(int socketFd);
    //distructor
    virtual ~MyParallerServer(){};

};

#endif //PROJ2_MYPARALLERSERVER_H
