// Project 2: Asymptotic Graph Creation
// Author: Kylie Jordan
//
// Graph.h
//
// This header file declares Edge class constructors and functions.
//

#ifndef PA02_EDGE_H
#define PA02_EDGE_H

#include <iostream>
#include <string>
#include "DSDLinkedList.h"
#include "Vertex.h"
using namespace std;


class Edge{
private:
    DSDLinkedList<Vertex> edge = DSDLinkedList<Vertex>();
    Vertex vert1;
public:
    Edge(){};
    Edge(Vertex& s1, Vertex& s2){
        vert1 = s1;
        edge.insertAtEnd(s1);
        edge.insertAtEnd(s2);
    };
    int size(){
        return edge.getSize();
    };
    void addVert(Vertex& s){
        edge.insertAtEnd(s);
    };
    Vertex& getHead(){return vert1;};
    bool contains(Vertex& elem){
        return edge.contains(elem);
    };
    Vertex& getVert(int index){
        if(index <edge.getSize())
            return edge.getElement(index);
        else
            throw invalid_argument("index not in list");
    };
    void print(){
        for(int i = 1; i<edge.getSize(); i++){
            edge.getElement(i).print();
        }
    };
    void print(ofstream& out){
        for(int i = 1; i<edge.getSize(); i++){
            edge.getElement(i).print(out);
        }
    };
};

#endif //PA02_EDGE_H
