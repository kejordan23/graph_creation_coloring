//
// Created by Kylie Jordan on 4/11/22.
//

#ifndef PROJECT_FINAL_CREATOR_H
#define PROJECT_FINAL_CREATOR_H

#include <iostream>
#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"

using namespace std;

class Creator{
private:
    Graph<Vertex> g;
public:
    Creator(){};
    void completeGraph(ofstream&, int);
    void cycleGraph(ofstream&, int);
    void randGraph(ofstream&, int, int, int);
    void runCreations();
    void analyzeTimes(ofstream&, int, int);
};

#endif //PROJECT_FINAL_CREATOR_H
