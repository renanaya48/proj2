cmake_minimum_required(VERSION 3.13)
project(proj2)

#set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "-std=c++14 -pthread")

add_executable(proj2 main.cpp Server.h MySerialServer.cpp MySerialServer.h ClientHandler.h Solver.h MyTestClientHandler.cpp MyTestClientHandler.h CacheManager.h FileCacheManager.h StringReverse.cpp StringReverse.h State.h Searchable.h Searcher.h BFS.h MatrixSolver.h MatrixSearchable.h BestFS.h Astar.h MyClientHandler.cpp MyClientHandler.h MyParallerServer.cpp MyParallerServer.h BackTrace.h StartMain.h)