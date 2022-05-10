#include <iostream>
#include <queue>
#include <unordered_set>
#include <vector>

using namespace std;

// first in, first out - we keep track of elements in the memory using an unordered_set for constant time access
// the elements to be removed are tracked by a queue data structure - which also follows the first in first out queueing model

void fifo(vector<int> pages) {
    int page_faults = 0;
    unordered_set<int> memory;
    queue<int> order;

    for (int i : pages) {
        // if page is not in memory, we add it to the memory if it's not full, and push it to the queue
        if (!memory.count(i)) {
            cout << "*** PAGE FAULT *** Page " << i << " missing, adding it as a frame.\n";
            if (memory.size() == 10) {
                // if memory is full, we remove the front element of the queue to make room for the new page
                int out = order.front();
                cout << "memory frames full, removing the oldest frame: " << out << endl; 
                memory.erase(out);
                order.pop();
            }
            page_faults++;
            memory.insert(i);
            order.push(i);
        } else {
            // unlike LRU/MRU, access does not affect when the frame will be removed
            cout << "reading page " << i << " (already present, no page fault)\n";
        }
    }
    cout << "\nTotal page faults: " << page_faults << endl;
}

