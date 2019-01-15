#ifndef PROJ2_FILECACHEMANAGER_H
#define PROJ2_FILECACHEMANAGER_H

#include <map>
#include "CacheManager.h"
#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;
template <class Problem, class Solution>
class FileCacheManager: public CacheManager<Problem, Solution>{
    //member
    map <string, string> problemsAndSolutions;

public:
    //constructor
    FileCacheManager(){
        this->readFile();
    }
/**
 * read file
 */
    void readFile(){
        ifstream myFile("ProbAndSolv.txt");
        string line;
        string problem = "";
        string solution = "";
        //open the file
        if(myFile.is_open()){
            //get the text by lines
            while (getline(myFile, line)){
                char* c = const_cast<char*>(line.c_str());
                c = strtok(c, "$");
                problem += c;

                c = strtok(NULL, ";");
                solution += c;

                this->problemsAndSolutions.insert(pair<string, string>(problem, solution));
            }
            //close file
            myFile.close();
        }
    }
/**
 * write to the file
 * @param problem the problem
 * @param solution the solution of the problem
 */
    void writeFile(string problem, string solution){
        ofstream myFile("ProbAndSolv.txt", ios::app);
        string line;

        //open the file
        if(myFile.is_open()){
            //write the problem and the solution to the file
            myFile << problem ;
            myFile << "$";
            myFile << solution;
            myFile <<"\n";
        }
    }
    /**
     *
     * @param problem the problem to check
     * @return if the problem have a solution or not
     */
    virtual bool haveSolution(string problem){
        //if there is a solution
        if (this->problemsAndSolutions.count(problem)){
            return true;
        }
        //no solution
        else {
            return false;
        }
    }
/**
 *
 * @param problem the problem we want to get it solution
 * @return the solution
 */
    virtual string getSolution(string problem){
        //update
        return this->problemsAndSolutions.find(problem)->second;
    }
    /**
     *
     * @param solution the solution to save
     * @param problem the problem to save
     */
    virtual void saveSolution(string solution, string problem){
        //insert the problem and the solution to the list
        this->problemsAndSolutions.insert(pair<string, string>(problem, solution));
        //write the problem and the solution to the file
        writeFile(problem, solution);
    }

    //distructor
    virtual ~FileCacheManager(){};

};


#endif //PROJ2_FILECACHEMANAGER_H
