#ifndef PROJ2_STARTMAIN_H
#define PROJ2_STARTMAIN_H

#include "MyParallerServer.h"
#include <string.h>
#include <stdio.h>
#include "Searchable.h"
#include "Searcher.h"
#include "Solver.h"
#include "MyClientHandler.h"
#include "CacheManager.h"
#include "MatrixSolver.h"
#include "Astar.h"
#include "FileCacheManager.h"

//name space
namespace boot{
    class StartMain{
    public:
        //distructor
        ~StartMain(){};
        //main
        int main(int argc, char* argv[]) {
            //if there are not 2 args that past to the main
            if(argc != 2){
                printf("Invalid input");
                exit(4);
            }
            //first arg will be the port
            int port = stoi(argv[1]);
            //new server
            Server* myServer = new MyParallerServer();
            Searcher<string, string>* searcher = new Astar<string, string>();
            Solver<string, string>* solver = new
                    MatrixSolver<string, string, string>(searcher);
            CacheManager<string, string>* cache = new FileCacheManager<string, string>();
            ClientHandler* client = new MyClientHandler<string, string>(cache, solver);

            //open new server by the port and client
            myServer->open(port, client);

            //free the memory allocated
            delete searcher;
            delete cache;
            delete solver;
            delete myServer;
            delete client;

            return 0;
        }
    };
}


#endif //PROJ2_STARTMAIN_H
