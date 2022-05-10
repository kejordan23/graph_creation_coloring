//
// Created by Kylie Jordan on 4/11/22.
//

#ifndef PROJECT_FINAL_ANALYZER_H
#define PROJECT_FINAL_ANALYZER_H

#include "Graph.h"
#include "Edge.h"
#include "Vertex.h"
#include <iostream>
#include <vector>

using namespace std;

class Analyzer{
private:
    Graph<Vertex> g;
    vector<int> order;
public:
    Analyzer(){};
    void read(ifstream&);
    void compDegree();
    void smallLastOrder();
    void smallOrgOrder();
    void randOrder();
    int color();
    void print(){g.print();};
    void goFiles();
    void printData(ifstream&);
};

#endif //PROJECT_FINAL_ANALYZER_H
