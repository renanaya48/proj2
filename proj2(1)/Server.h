#ifndef PROJ2_SERVER_H
#define PROJ2_SERVER_H

#include "ClientHandler.h"

//namespace server_side
namespace server_side{
    //Server class
    class Server{

    public:

        /**
         * open new server
         * @param port the port to open on
         * @param clientHandler the current client
         */
        virtual void open(int port,ClientHandler* clientHandler) = 0;
        /**
         * stop the connection
         * @param sockfd the soccet
         */
        virtual void stop(int sockfd) = 0;
        //distroctor
        virtual ~Server(){};
    };
}




#endif //PROJ2_SERVER_H
