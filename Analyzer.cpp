//
// Created by Kylie Jordan on 4/11/22.
//

#include "Analyzer.h"

using namespace std;

void Analyzer::read(ifstream& input){
    if(g.getSize()>0)
        g.clear();
    int numVert = 0;
    int threshold = 0;
    input>>threshold;
    int p[threshold];

    while(numVert < threshold){
        input>>p[numVert];
        numVert++;
    }

    numVert = 1;
    int currLine = p[0];
    int currVert = 0;
    int preVert = 0;

    while(numVert <= threshold){
        while(currLine != p[numVert]){
            input>>currVert;
            if(currVert == preVert)
                break;
            preVert = currVert;
            Vertex v1(numVert);
            Vertex v2(currVert);
            Edge e(v1, v2);
            g.addEdge(e);
            currLine++;
        }
        preVert = 0;
        numVert++;
    }
}

void Analyzer::compDegree(){
    for(int i = 1; i< g.getSize()+1; i++){
        int temp1 = g.getVertDegree(g.getEdge(i).getHead().getID());
        g.getEdge(i).getHead().setDegree(temp1);
        for(int j = 0; j<g.getEdge(i).size(); j++) {
            int temp = g.getEdge(i).getVert(j).getID();
            int temp2 = g.getVertDegree(temp);
            g.getEdge(i).getVert(j).setDegree(temp2);
        }
    }
}

void Analyzer::smallLastOrder(){
    Graph<Vertex> temp(g);
    bool done = false;
    int vertDel = 0;

    order.clear();
    while(!done) {
        int smallestD = 10000;
        int smallestV = 0;
        for (int i = 1; i < temp.getSize()+1; i++) {
            if(temp.degrees[i]<smallestD && temp.degrees[i]>=0) {
                smallestD = temp.degrees[i];
                smallestV = i;
            }
        }
        temp.degrees[smallestV] = 0;
        order.push_back(smallestV);
        vertDel++;
        int t = temp.getEdge(smallestV).size();
        for(int i = 0; i<temp.getEdge(smallestV).size(); i++){
            temp.degrees[temp.getEdge(smallestV).getVert(i).getID()]--;
        }

        if(vertDel == temp.getSize())
            done = true;
    }
    /*for(int i = 0; i<order.size(); i++){
        cout<<order[i]<<endl;
    }*/
}

void Analyzer::smallOrgOrder(){
    Graph<Vertex> temp(g);
    bool done = false;
    int vertDel = 0;

    order.clear();
    while(!done) {
        int smallestD = 10000;
        int smallestV = 0;
        for (int i = 1; i < temp.getSize()+1; i++) {
            if(temp.degrees[i]<smallestD && temp.degrees[i]>=0) {
                smallestD = temp.degrees[i];
                smallestV = i;
            }
        }
        temp.degrees[smallestV] = -1;
        order.push_back(smallestV);
        vertDel++;
        if(vertDel == temp.getSize())
            done = true;
    }
    /*for(int i = 0; i<order.size(); i++){
        cout<<order[i]<<endl;
    }*/
}

void Analyzer::randOrder(){
    Graph<Vertex> temp(g);
    bool done = false;
    int vertDel = 0;

    order.clear();

    for(int i = 1; i<temp.getSize()+1; i++){
        order.push_back(i);
    }

    while(!done) {
        int r1 = rand()%temp.getSize();
        int r2 = rand()%temp.getSize();
        if(r1 != r2) {
            int temp = order[r1];
            order[r1] = order[r2];
            order[r2] = temp;
            vertDel++;
        }
        if(vertDel == (temp.getSize()+(vertDel/2)))
            done = true;
    }
    /*for(int i = 0; i<order.size(); i++){
        cout<<order[i]<<endl;
    }*/
}
int Analyzer::color(){
    int color;
    for(int i = 0; i<order.size(); i++){
        color = 1;
        for(int j = 0; j<g.getEdge(order[i]).size(); j++) {
            if(g.getEdge(g.getEdge(order[i]).getVert(j).getID()).getHead().getColor() == color)
                color++;
        }
        g.getEdge(order[i]).getHead().setColor(color);
    }

    for(int i = 1; i< g.getSize()+1; i++){
        for(int j = 0; j<g.getEdge(i).size(); j++) {
            int temp = g.getEdge(g.getEdge(i).getVert(j).getID()).getHead().getColor();
            g.getEdge(i).getVert(j).setColor(temp);
        }
    }
    return color;
}

void Analyzer::goFiles(){
    for(int i = 0; i< 5; i++){

        //TO TEST: replace the file path with that to your directory of graph files
        ifstream in1("/Users/kyliejordan/Desktop/CS5350/Project_Final/Graphs/cycle"+to_string(((i+1)*100))+".txt");
        ifstream in2("/Users/kyliejordan/Desktop/CS5350/Project_Final/Graphs/uniform"+to_string(((i+1)*100))+".txt");
        ifstream in3("/Users/kyliejordan/Desktop/CS5350/Project_Final/Graphs/complete"+to_string(((i+1)*10))+".txt");
        if(!in1.is_open() || !in2.is_open() || !in3.is_open())
            cout<<"issue"<<endl;
        cout<<"###Cycle Graph"<<endl;
        cout<<"###Number of Vertices: "<<((i+1)*100)<<endl;
        printData(in1);

        cout<<"###Uniform Graph"<<endl;
        cout<<"###Number of Vertices: "<<((i+1)*100)<<endl;
        printData(in2);

        cout<<"###Complete Graph"<<endl;
        cout<<"###Number of Vertices: "<<((i+1)*10)<<endl;
        printData(in3);

        cout<<"Done"<<((i+1)*100)<<endl;
    }
}

void Analyzer::printData(ifstream& input){
    std::chrono::time_point<std::chrono::system_clock> start, end;
    read(input);
    compDegree();

    cout<<"Smallest last Ordering: ";
    start = std::chrono::system_clock::now();
    smallLastOrder();
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    cout<<elapsed_seconds.count()<<endl;

    cout<<"Coloring: ";
    start = std::chrono::system_clock::now();
    int c1 = color();
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout<<elapsed_seconds.count()<<endl;
    cout<<"$$$Total colors: "<<c1<<endl;

    cout<<"Smallest Original Ordering: ";
    start = std::chrono::system_clock::now();
    smallOrgOrder();
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout<<elapsed_seconds.count()<<endl;

    cout<<"Coloring: ";
    start = std::chrono::system_clock::now();
    int c2 = color();
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout<<elapsed_seconds.count()<<endl;
    cout<<"$$$Total colors: "<<c2<<endl;

    cout<<"Random Ordering: ";
    start = std::chrono::system_clock::now();
    randOrder();
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout<<elapsed_seconds.count()<<endl;

    cout<<"Coloring: ";
    start = std::chrono::system_clock::now();
    int c3 = color();
    end = std::chrono::system_clock::now();
    elapsed_seconds = end - start;
    cout<<elapsed_seconds.count()<<endl;
    cout<<"$$$Total colors: "<<c3<<endl;

    cout<<endl;
    cout<<endl;
}
