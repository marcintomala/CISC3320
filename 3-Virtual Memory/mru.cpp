#include <unordered_set>
#include <stack>
#include <iostream>
#include <vector>

using namespace std;

// frames stored in an unordered set for constant time access.


void mru(vector<int> pages) {
    int page_faults = 0;
    unordered_set<int> memory;
    int mru_page;

    for (int i : pages) {
        // for each page in the reference string, we check if it's in the memory:
        if (!memory.count(i)) {
            // if not, and there is still room in the memory, we add the new page
            cout << "*** PAGE FAULT *** Page " << i << " missing, adding it as a frame.\n";
            if (memory.size() == 10) {
                // if there is no room, we remove the MRU first
                cout << "memory frames full, removing the most recently used frame: " << mru_page << endl; 
                memory.erase(mru_page);
            }
            page_faults++;
            memory.insert(i);
            mru_page = i;
        } else {
            // if the page is present, we simply update the MRU to the page number
            cout << "reading page " << i << " (already present, no page fault) (Previous MRU: " << mru_page << ", ";
            mru_page = i;
            cout << "MRU now " << i << ")\n";
        }
    }
    cout << "\nTotal page faults: " << page_faults << endl;
}
