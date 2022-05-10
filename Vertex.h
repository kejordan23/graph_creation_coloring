//
// Created by Kylie Jordan on 4/25/22.
//

#ifndef PROJECT_FINAL_VERTEX_H
#define PROJECT_FINAL_VERTEX_H

#include <iostream>
#include <string>

using namespace std;

class Vertex{
private:
    int id = 0;
    int degree = 1;
    int color = 0;
public:
    Vertex(){};
    Vertex(int t){id = t;};
    int getID(){return id;};
    void setID(int s){id = s;};
    int getDegree(){return degree;};
    void setDegree(int d){degree = d;};
    int getColor(){return color;};
    void setColor(int c){color = c;};
    bool operator==(const Vertex& rhs){
        return this->id == rhs.id;
    };
    void print(){
        cout<<"ID: "<<id<<endl;
        cout<<"Degree: "<<degree<<endl;
        cout<<"Color: "<<color<<endl;
        cout<<endl;
    }
    void print(ofstream& out){
        out<<"ID: "<<id<<endl;
        out<<"Degree: "<<degree<<endl;
        out<<"Color: "<<endl;
        out<<endl;
    }
};

#endif //PROJECT_FINAL_VERTEX_H
