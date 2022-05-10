#include <iostream>
#include <fstream>
#include <vector>
#include "fifo.cpp"
#include "lru.cpp"
#include "mru.cpp"
#include "opt.cpp"

using namespace std;

int main () {
    // driver function. reads the reference string file and places the pages in a vector of integers
    // to be used by the algorithm functions:
    ifstream in_stream;
    in_stream.open("data.csv");
    vector<int> pages;

    if (in_stream.good()) {
        int page; //where each page of the file will go to
        while (in_stream >> page) {
            pages.push_back(page);
        }
    }
    
    // page replacement algorithm function calls
    //fifo(pages);
    //mru(pages);
    lru(pages);
    opt(pages);
    return 0;
}