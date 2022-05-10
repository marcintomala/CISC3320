#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

// The LRU algorithm using an unordered (hash) map with constant time access.
// Along with the map, a linked list is created to quickly keep track of the least recently used.
// (as pages are read in/accessed, they are moved to the head, which causes the tail to be the least recently used)


// Linked list definition and basic functions:
class Node {
    public:
        int page;
    Node* next;
    Node* prev;
};

void add_node(Node* head, Node* n) {
    // adds a new node at the beginning of the LL
    n->prev = head;
    n->next = head->next;
    
    head->next->prev = n;
    head->next = n;
}

void remove_node(Node* n) {
    // removes the node
    n->prev->next = n->next;
    n->next->prev = n->prev;
}

void move_to_head(Node* head, Node* n) {
    // when pages already present are accessed, they need to be moved to the top
    remove_node(n);
    add_node(head, n);
}

Node* pop_tail(Node* tail) {
    // removal of the last node - the least recently used
    Node* res = tail->prev;
    remove_node(res);
    return res;
}


void lru(vector<int> pages) {
    // definitions
    unordered_map<int, Node*> memory;
    int page_faults = 0;
    Node* head = new Node();
    Node* tail = new Node();

    head->next = tail;
    tail->prev = head;

    for (int i : pages) {
        // for each page, we attempt to retrieve a node associated with it
        Node* n = memory.count(i) ? memory[i] : NULL;
        // if the node is null - the page does not exist - we have a page fault and we add a new node to the map
        if (!n) {
            cout << "*** PAGE FAULT *** Page " << i << " not currently in memory, adding...\n";
            page_faults++;
            Node* n = new Node();
            n->page = i;
            if (memory.size() >= 10) {
                // if the map is full, we remove the least recently used - tail of the linked list
                cout << "--- MEMORY FULL, REMOVING LRU ---\n";
                Node* t = pop_tail(tail);
                memory.erase(t->page);
                cout << "--- REMOVED PAGE " << t->page << " ---\n";
            }
            memory[i] = n;
            add_node(head, n);
        } else {
            // if the node is not null - already present - we just update the node's position in the LL
            cout << "reading page " << i << " (already present, no page fault)\n";
            move_to_head(head, n);
        }
    }
    cout << "Total page faults: " << page_faults << endl;
}
