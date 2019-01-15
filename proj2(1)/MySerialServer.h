#ifndef PROJ2_MYSERIALSERVER_H
#define PROJ2_MYSERIALSERVER_H

#include "Server.h"

using namespace server_side;
class MySerialServer: public Server{
    //member
    bool runner=true;

public:
    /**
     *
     * @param port the port
     * @param clientHandler ClientHandler
     */
    virtual void open(int port,ClientHandler* clientHandler);
    /**
     * stop the connection
     * @param sockfd the socket
     */
    virtual void stop(int sockfd);
    //distructor
    virtual ~MySerialServer(){};
};


#endif //PROJ2_MYSERIALSERVER_H
