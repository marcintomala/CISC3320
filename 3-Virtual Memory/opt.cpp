#include <iostream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

// Optimal algorithm. Given a vector of integers which represents the reference string,
// we build a map of each page's future positions. Then, as space in the memory is needed,
// we iterate over the pages in memory to find the page furthest away (if at all) in the 
// reference string.


void opt(vector<int> pages) {
    // variable declarations
    int page_faults = 0;
    unordered_map<int, queue<int>> positions;
    unordered_set<int> memory;


    for (int i = 0; i < pages.size(); i++) {
        // positions map build loop
        if (!positions.count(pages[i])) {
            queue<int> a;
            a.push(i);
            positions[pages[i]] = a;
        } else {
            positions[pages[i]].push(i);
        }
    }

    for (auto& p : positions) {
        // trailer max integer value for every positions queue
        p.second.push(INT32_MAX);
    }

    for (int i : pages) {
        cout << "Reading page " << i << "...\n";
        if (!memory.count(i)) {
            // if page is not in memory, we need to add it
            cout << "*** PAGE FAULT *** Page " << i << " missing, adding it as a frame.\n";
            if (memory.size() == 10) {
                // if memory is full, we find the furthest away element:
                cout << "\nMemory frames full, removing the least needed frame\n"; 
                int max = -1;
                int j = -1;
                for (int k : memory) {
                    if (positions[k].front() > max) {
                        max = positions[k].front();
                        j = k;
                    }
                }

                // cosmetic branching to indicate whether the page that's being removed appears again or not:
                if (max == INT32_MAX) {
                    cout << "Page " << j << " does not appear again, removing " << j << endl;
                } else {
                    cout << "The furthest page is " << j << ", as it next appears at position " << max << ". Removing " << j << "...\n";
                }
                cout << endl;
                memory.erase(j);
            }
            page_faults++;
            // currently read page's next position (the current index) is removed from its positions queue
            positions[i].pop();
            memory.insert(i);
        } else {
            // if an element was found in memory, we just need to remove the current position from its positions queue
            positions[i].pop();
            cout << "(Already present, no page fault.)\n";
        }
    }
    cout << "\nTotal page faults: " << page_faults << endl;
}

