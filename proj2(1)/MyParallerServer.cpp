#include "MyParallerServer.h"
#define WAIT_FOR_CLIENT 1
#define WAIT_FOREVER 0

#include <vector>
using namespace std;

//Client struct
struct client{
    ClientHandler *clientHandler;
    int newSockFd;

};

//Server struct
struct params {
    int sockFd;
    int newSockFd;
    int client;
    ClientHandler *clientHandler;
    struct sockaddr_in client_addr;
};

//Constructor
MyParallerServer::MyParallerServer()  {

}

/**
 * The function open a thread to communuczte to a client
 */
void* clientThread(void *arg) {
    struct client* clientStruct=(struct client*) arg;
    //Handle client
    clientStruct->clientHandler->handleClient(clientStruct->newSockFd);

   return 0;
}

/**
 * The function open a socket server and listen to multiple clients simultaneously
 */
void* multipleClients(void *args) {
    struct params* openSocket = (struct params *) args;
    timeval timeout;
    timeout.tv_sec = WAIT_FOR_CLIENT;
    timeout.tv_usec = 0;
    timeval timeForever;
    timeForever.tv_sec = WAIT_FOREVER;
    timeForever.tv_usec = 0;
    vector<pthread_t> closeThread;

    //Wait for connection from the first client
    struct client* clientStruct = new client();
    clientStruct->clientHandler=openSocket->clientHandler;
    openSocket->newSockFd = accept(openSocket->sockFd,
                                   (struct sockaddr *) &openSocket->client_addr,
                                   (socklen_t *) &openSocket->client);

    if (openSocket->newSockFd < 0) {
        perror("ERROR on accept");
        return 0;
    }

    //Open a thread to talk to the client
    clientStruct->newSockFd = openSocket->newSockFd;
    setsockopt(openSocket->newSockFd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeForever, sizeof(timeForever));
    pthread_t pthread;
    pthread_create(&pthread, nullptr, clientThread, clientStruct);
    closeThread.push_back(pthread);

    //While there are more clients
    while (true) {
        /*Accept actual connection from the client */
        //Wait for connection from the next client
        setsockopt(openSocket->sockFd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeout, sizeof(timeout));
        openSocket->newSockFd = accept(openSocket->sockFd,
                                       (struct sockaddr *) &openSocket->client_addr,
                                       (socklen_t *) &openSocket->client);

        //If the client failed to connect or the time ended clise the sever
        if (openSocket->newSockFd < 0) {
            if (errno == EWOULDBLOCK){
                printf("timeout\n");
                break;
            } else {
                perror("ERROR on accept");
                break;
            }
        }

        //Open a thread to talk to the client
        clientStruct->newSockFd = openSocket->newSockFd;
        setsockopt(openSocket->newSockFd, SOL_SOCKET, SO_RCVTIMEO, (char *)&timeForever, sizeof(timeForever));
        pthread_t pthread;
        pthread_create(&pthread, nullptr, clientThread, clientStruct);
        closeThread.push_back(pthread);
    }

    int size = closeThread.size();
    for (int i = 0; i < size; i++){
        pthread_join(closeThread[i], NULL);
    }

    delete clientStruct;
    return 0;
}

/**
 * The function open thread to open a server and listen to multiple clients simultaneously
 */
void MyParallerServer::open(int port, ClientHandler *clientHandler) {
    int newsockfd = 0;
    int sockfd, portno, clilen;
    struct sockaddr_in serv_addr, cli_addr;
    struct params* openSocket = new params();

    // open a socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    // Initialize socket structure
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = port;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    /* Now bind the host address using bind() call.*/
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }

    //Listen to the socket
    listen(sockfd, 5);
    clilen = sizeof(cli_addr);

    // Initialize server structure
    openSocket->clientHandler = clientHandler;
    openSocket->client = clilen;
    openSocket->client_addr = cli_addr;
    openSocket->newSockFd = newsockfd;
    openSocket->sockFd = sockfd;

    //Open a thread to the server
    pthread_t pthread;
    pthread_create(&pthread, nullptr, multipleClients, openSocket);
    pthread_join(pthread,NULL);
    stop(openSocket->sockFd);
    delete openSocket;
    //pthread_exit(NULL);
}
    /**
     * he function stop the server
     * @param socketFd the socket
     */
void MyParallerServer::stop(int socketFd) {
    //close the socket
    close(socketFd);
}