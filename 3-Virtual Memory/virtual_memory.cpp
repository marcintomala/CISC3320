#include <iostream>
#include <fstream>
#include <vector>
#include "fifo.cpp"
#include "lru.cpp"
#include "mru.cpp"

using namespace std;

int main () {
    ifstream in_stream;
    in_stream.open("data.csv");
    vector<int> pages;

    if (in_stream.good()) {
        int page; //where each page of the file will go to
        while (in_stream >> page) {
            pages.push_back(page);
        }
    }
    fifo(pages);
    lru(pages);
    mru(pages);
    mru({1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6, 1, 2, 3, 4, 5, 6});
    return 0;
}