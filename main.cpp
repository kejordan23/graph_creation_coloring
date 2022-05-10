/*
 * Project: Graph Coloring Analysis
 * Author: Kylie Jordan
 *
 * #### Please see project report for more information on the code base ####
 *
 * To run:
 *      ./Project_Final -i <input_file_path>    -for ordering and coloring
 *      ./Project_Final -o <output_file_path>   -for graph creation
 */
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <ctime>
#include "Graph.h"
#include "Edge.h"
#include "Creator.h"
#include "Analyzer.h"

using namespace std;

int main(int argc, char** argv) {
    if(argv[1] == "-i") {
        ifstream input(argv[2]);
        if (!input.is_open())
            cout << "cannot open input" << endl;

        Analyzer a;
        a.printData(input);

        input.close();
    }
    else if (argv[1] == "-o") {
        ofstream out(argv[2]);
        if (!out.is_open())
            cout << "cannot open out" << endl;

        Creator c;
        c.analyzeTimes(out, 200, 300);
        out.close();
    }
    return 0;
}
