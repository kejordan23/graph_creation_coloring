// Project 2: Asymptotic Graph Creation
// Author: Kylie Jordan
//
// Graph.h
//
// This header file declares Graph class constructors and functions. Referenced from Kylie Jordan's code created
// during CS2341 Fall2020
//

#ifndef INC_20F_FLT_PLN_ADJLIST_H
#define INC_20F_FLT_PLN_ADJLIST_H

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "DSDLinkedList.h"
#include "Edge.h"

using namespace std;

template <typename T>
class Graph{
    private:
        DSDLinkedList<Edge> graph = DSDLinkedList<Edge>();
    public:
        int degrees [20000];
        Graph(){};
        Graph& operator=(Graph& rhs){
            this->graph = rhs.graph;
            this->graph.degrees = rhs.degrees;
            return *this;
        }
        void clear(){
            graph.clear();
        };
        int getVertDegree(int index){return degrees[index];};
        int getSize(){return graph.getSize();};
        Edge& getEdge(int id){
            int index = 0;
            for(int i = 0; i<graph.getSize(); i++){
                if(graph.getElement(i).getHead().getID() == id)
                    index = i;
            }
            return graph.getElement(index);
        };
        void addEdge(Edge& e){
            bool vert1InGraph = false;
            bool vert2InGraph = false;
            int vert1degree = 0;
            int vert2degree = 0;
            for(int i = 0; i< graph.getSize(); i++){
                if(graph.getElement(i).getHead()==e.getVert(0)) {
                    vert1degree = graph.getElement(i).size()-1;
                    degrees[graph.getElement(i).getHead().getID()] = vert1degree;
                    if(!graph.getElement(i).contains(e.getVert(1))) {
                        graph.getElement(i).addVert(e.getVert(1));
                    }
                    vert1InGraph = true;
                }
                if(graph.getElement(i).getHead()==e.getVert(1)) {
                    vert2degree = graph.getElement(i).size()-1;
                    degrees[graph.getElement(i).getHead().getID()] = vert2degree;
                    if(!graph.getElement(i).contains(e.getVert(0))) {
                        graph.getElement(i).addVert(e.getVert(0));
                    }
                    vert2InGraph = true;
                }
            }
            if(!vert1InGraph){
                graph.insertAtEnd(e);
                degrees[e.getVert(0).getID()] = 1;
            }
            if(!vert2InGraph){
                Edge temp (e.getVert(1), e.getVert(0));
                graph.insertAtEnd(temp);
                degrees[e.getVert(1).getID()] = 1;
            }
            vert1degree = 0;
            vert2degree = 0;
        };
        // this prints vertex information
        void print(){
            int arr[graph.getSize()];
            cout<<graph.getSize()<<endl;
            cout<<graph.getSize()+1<<endl;
            arr[0] = graph.getSize()+1;
            for(int i = 1; i<graph.getSize(); i++){
                cout<<arr[i-1]+getEdge(i).size()-1<<endl;
                arr[i] = arr[i-1]+getEdge(i).size()-1;
            }
            for(int i = 1; i<=graph.getSize(); i++){
                cout<<"#####Vertex: "<<getEdge(i).getHead().getID()<<endl;
                getEdge(i).print();
            }
        };
        //this prints out formatted edges
        void newPrint(){
            for(int i = 0; i<graph.getSize(); i++){
                for(int j = 0; j< graph.getElement(i).size(); j++) {
                    cout<<graph.getElement(i).getVert(j).getID()<<"->";
                }
                cout<<endl;
            }
        }
        //This print function is for graph creation ONLY
        void print(ofstream& out){
            int arr[graph.getSize()];
            out<<graph.getSize()<<endl;
            out<<graph.getSize()+1<<endl;
            arr[0] = graph.getSize()+1;
            for(int i = 1; i<graph.getSize(); i++){
                out<<arr[i-1]+getEdge(i).size()-1<<endl;
                arr[i] = arr[i-1]+getEdge(i).size()-1;
            }
            for(int i = 1; i<=graph.getSize(); i++){
                for(int j = 1; j<getEdge(i).size(); j++)
                    out<<getEdge(i).getVert(j).getID()<<endl;
            }
        };
};

#endif //INC_20F_FLT_PLN_ADJLIST_H
