#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

void fifo(vector<int> pages) {
    int page_faults = 0;
    unordered_set<int> memory;
    queue<int> order;

    for (int i : pages) {
        if (!memory.count(i)) {
            cout << "*** PAGE FAULT *** Page " << i << " missing, adding it as a frame.\n";
            if (memory.size() == 10) {
                int out = order.front();
                cout << "memory frames full, removing the oldest frame: " << out << endl; 
                memory.erase(out);
                order.pop();
            }
            page_faults++;
            memory.insert(i);
            order.push(i);
        } else {
            cout << "reading page " << i << " (already present, no page fault)\n";
        }
    }
    cout << "\nTotal page faults: " << page_faults << endl;
}

