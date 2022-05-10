//
// Created by Kylie Jordan on 4/11/22.
//

#include "Creator.h"
#include <random>
#include <set>

using namespace std;

void Creator::completeGraph(ofstream& out, int vert){
    if(g.getSize() > 0)
        g.clear();
    for(int i = 1; i< vert+1; i++){
        for(int j = 1; j<vert+1; j++) {
            if(i != j) {
                Vertex v1(i);
                Vertex v2(j);
                Edge e(v1, v2);
                g.addEdge(e);
            }
        }
    }
    g.print(out);
}
void Creator::cycleGraph(ofstream& out, int vert){
    if(g.getSize() > 0)
        g.clear();
    for(int i = 1; i< vert; i++){
        int temp = i+1;
        Vertex v1(i);
        Vertex v2(temp);
        Edge e(v1, v2);
        g.addEdge(e);
    }
    int t = 1;
    Vertex v1(t);
    Vertex v2(vert);
    Edge e(v1, v2);
    g.addEdge(e);
    g.print(out);
}


//dist is the integer value associated with the wanted distribution
// 1 for uniform
// 2 for skewed (left)
// 3 for normal
void Creator::randGraph(ofstream& out, int vert, int totEdge, int dist){
    if(g.getSize() > 0)
        g.clear();
    //uniform distribution
    if(dist == 1){
        std::random_device                  rand_dev;
        std::mt19937                        generator(rand_dev());
        std::uniform_int_distribution<int>  distr(1, vert);

        int vertChose = 0;
        int confChose = 0;

        for(int i = 0; i<totEdge; i++) {
            vertChose = distr(generator);
            confChose = distr(generator);
            if (vertChose != confChose) {
                Vertex v1(vertChose);
                Vertex v2(confChose);
                Edge e(v1, v2);
                g.addEdge(e);
            }
            else
                i--;
        }
    }
    // skewed distribution
    else if(dist == 2){
        std::default_random_engine generator;
        std::normal_distribution<double>  distr(1.0, vert/2);

        int vertChose = 0;
        int confChose = 0;

        for(int i = 0; i<totEdge; i++) {
            vertChose = (int)abs(distr(generator));
            confChose = (int)abs(distr(generator));
            if (vertChose != confChose && vertChose>= 1 && confChose >=1 && vertChose <=vert && confChose <= vert) {
                Vertex v1(vertChose);
                Vertex v2(confChose);
                Edge e(v1, v2);
                g.addEdge(e);
            }
            else
                i--;
        }
    }
    // normal distribution
    else if(dist == 3){
        std::random_device                  rand_dev;
        std::mt19937                        generator(rand_dev());
        std::normal_distribution<double>  distr(double(vert/2), double(vert/4)+1);

        int vertChose = 0;
        int confChose = 0;

        for(int i = 0; i<totEdge; i++) {
            vertChose = (int)distr(generator);
            confChose = (int)distr(generator);
            if (vertChose != confChose && vertChose>= 1 && confChose >=1 && vertChose <=vert && confChose <= vert) {
                Vertex v1(vertChose);
                Vertex v2(confChose);
                Edge e(v1, v2);
                g.addEdge(e);
            }
            else
                i--;
        }
    }
    else
        cout<<"Incorrect distribution numbers"<<endl;

    g.print(out);
}

void Creator::runCreations(){
    for(int i = 0; i< 5; i++){
        ofstream out1("/Users/kyliejordan/Desktop/CS5350/Project_Final/Graphs/cycle"+to_string(((i+1)*100))+".txt");
        ofstream out2("/Users/kyliejordan/Desktop/CS5350/Project_Final/Graphs/uniform"+to_string(((i+1)*100))+".txt");
        ofstream out3("/Users/kyliejordan/Desktop/CS5350/Project_Final/Graphs/complete"+to_string(((i+1)*10))+".txt");
        if(!out1.is_open() || !out2.is_open() || !out3.is_open())
            cout<<"issue"<<endl;
        cycleGraph(out1, ((i+1)*100));
        randGraph(out2, ((i+1)*100), ((i+1)*100)+100, 1);
        completeGraph(out3, ((i+1)*10));
        cout<<"Done"<<((i+1)*100)<<endl;
    }
}


void Creator::analyzeTimes(ofstream& out, int vert, int edges){
    std::chrono::time_point<std::chrono::system_clock> start, end;

    cout<<"Number of Vertices: "<<vert<<endl;
    cout<<"Number of Conflicts: "<<edges<<endl;

    cout<<"Rand Graph Creation Runtimes:"<<endl;
    start = std::chrono::system_clock::now();
    randGraph(out, vert, edges, 1);
    end = std::chrono::system_clock::now();

    std::chrono::duration<double> elapsed_seconds = end - start;
    cout<<"Uniform: "<<elapsed_seconds.count()<<endl;

    start = std::chrono::system_clock::now();
    randGraph(out, vert, edges, 2);
    end = std::chrono::system_clock::now();

    elapsed_seconds = end - start;
    cout<<"Skewed: "<<elapsed_seconds.count()<<endl;

    start = std::chrono::system_clock::now();
    randGraph(out, vert, edges, 3);
    end = std::chrono::system_clock::now();

    elapsed_seconds = end - start;
    cout<<"Normal: "<<elapsed_seconds.count()<<endl;

    cout<<"Complete Graph Runtime: ";
    start = std::chrono::system_clock::now();
    completeGraph(out, vert);
    end = std::chrono::system_clock::now();

    elapsed_seconds = end - start;
    cout<<elapsed_seconds.count()<<endl;

    cout<<"Cycle Graph Runtime: ";
    start = std::chrono::system_clock::now();
    cycleGraph(out, vert);
    end = std::chrono::system_clock::now();

    elapsed_seconds = end - start;
    cout<<elapsed_seconds.count()<<endl;
}
