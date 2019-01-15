#include "MyTestClientHandler.h"
#include <string.h>
#include <unistd.h>

template <>
//constructor
MyTestClientHandler<string, string>::MyTestClientHandler(CacheManager<string, string>* cacheM,
        Solver<string, string>* solve){
    this->cacheManager = cacheM;
    this->solver = solve;

}

template <>
/**
 *
 * @param newSockFD socket
 */
void MyTestClientHandler<string, string>::handleClient(int newSockFD) {
    char buffer[1025];
    int n;
    string problem, solution;
    //read from the socket
    while (true) {
        bzero(buffer, 1025);
        n = read(newSockFD, buffer, 1024);
        //if there is a problem reading from the socket
        if (n < 0) {
            perror("ERROR reading from socket");
            exit(1);
        }

        problem = string(buffer);

        //if we got to the end
        if (strcmp(buffer, "end") == 0) {
            return;
        }

        //if the problem already have a solution in cache manager
        if (this->cacheManager->haveSolution(problem)) {
            //return the solution
            solution = this->cacheManager->getSolution(problem);
       //there is no solution we know to the problem
        } else {
            //solve the problem
            solution = this->solver->solve(problem);
            //add the problem and the solution to the cache manager
            this->cacheManager->saveSolution(solution, problem);
        }

        //write to the socket
        char bufferWrite[1024];
        bzero(bufferWrite, 1025);
        strcpy(bufferWrite, solution.c_str());
        ssize_t nBuffer = write(newSockFD, bufferWrite, strlen(bufferWrite));

        //if there is problem writing to the socket
        if (nBuffer < 0) {
            perror("ERROR writing to socket");
            exit(1);
        }
    }
}
