#include "MySerialServer.h"
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
#include <vector>
#include <pthread.h>
#include <time.h>

#define WAIT_FOR_CLIENT 60;

struct socketArgs {
//    template <class InputStream, class OutputStream>
    int newsockfd;
    int clilen;
    int sockfd;
    struct sockaddr_in cli_addr;
    ClientHandler* clientHandler;
};
/**
 * run one client
 * @param args the args
 * @return
 */
void* runClient(void* args){
    timeval timeout;
    timeout.tv_sec = WAIT_FOR_CLIENT;
    timeout.tv_usec = 0;

    struct socketArgs* param = (struct socketArgs*) args;


    while(true) {
        setsockopt(param->sockfd, SOL_SOCKET, SO_RCVTIMEO, (char*)&timeout, sizeof(timeout));
        /* Accept actual connection from the client */
        param->newsockfd = accept(param->sockfd, (struct sockaddr *) &(param->cli_addr),
                                  (socklen_t *) &(param->clilen));
        //the time past
        if (param->newsockfd < 0) {
            if (errno == EWOULDBLOCK){
                printf("timeout\n");
                return 0;
            } else {
                perror("ERROR on accept");
                return 0;
            }
        }
        param->clientHandler->handleClient(param->newsockfd);
        //close
        close(param->newsockfd);
    }
}
/**
 *
 * @param port the port
 * @param clientHandler ClientHandler
 */
void MySerialServer::open(int port, ClientHandler* client){

    int newsockfd = 0;
    int sockfd, portno, clilen;

    struct sockaddr_in serv_addr, cli_addr;

    // First call to socket function
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //if there is a problem open socket
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    // initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons((uint16_t)((size_t)portno));

    //bind the host address using bind call
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    // now start listening for the clients, here process will
    //go in sleep mode and will wait for the incoming connection
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    struct socketArgs* arg = new socketArgs();

    //set the args
    arg->cli_addr = cli_addr;
    arg->clilen = clilen;
    arg->newsockfd = newsockfd;
    arg->sockfd = sockfd;
    arg->clientHandler = client;

    pthread_t pthread;
    pthread_create(&pthread, nullptr, runClient, arg);
    pthread_join(pthread, NULL);

    //stop the connection
    this->stop(sockfd);
};
/**
 * stop the connection
 * @param sockfd the socket
 */
void MySerialServer::stop(int sockfd){
    //close the socket
    close(sockfd);
}


