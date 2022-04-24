#include <unordered_set>
#include <stack>
#include <iostream>
#include <vector>

using namespace std;

void mru(vector<int> pages) {
    int page_faults = 0;
    unordered_set<int> memory;
    int mru_page;

    for (int i : pages) {
        if (!memory.count(i)) {
            cout << "*** PAGE FAULT *** Page " << i << " missing, adding it as a frame.\n";
            if (memory.size() == 10) {
                cout << "memory frames full, removing the most recently used frame: " << mru_page << endl; 
                memory.erase(mru_page);
            }
            page_faults++;
            memory.insert(i);
            mru_page = i;
        } else {
            cout << "reading page " << i << " (already present, no page fault) (Previous MRU: " << mru_page << ", ";
            mru_page = i;
            cout << "MRU now " << i << ")\n";
        }
    }
    cout << "\nTotal page faults: " << page_faults << endl;
}
