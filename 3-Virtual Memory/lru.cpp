#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Node {
    public:
        int page;
    Node* next;
    Node* prev;
};

void add_node(Node* head, Node* n) {
    n->prev = head;
    n->next = head->next;
    
    head->next->prev = n;
    head->next = n;
}

void remove_node(Node* n) {
    n->prev->next = n->next;
    n->next->prev = n->prev;
}

void move_to_head(Node* head, Node* n) {
    remove_node(n);
    add_node(head, n);
}

Node* pop_tail(Node* tail) {
    Node* res = tail->prev;
    remove_node(res);
    return res;
}


void lru(vector<int> pages) {
    unordered_map<int, Node*> memory;
    int page_faults = 0;
    Node* head = new Node();
    Node* tail = new Node();

    head->next = tail;
    tail->prev = head;

    for (int i : pages) {
        Node* n = memory.count(i) ? memory[i] : NULL;
        if (!n) {
            cout << "*** PAGE FAULT *** Page " << i << " not currently in memory, adding...\n";
            page_faults++;
            Node* n = new Node();
            n->page = i;
            if (memory.size() >= 10) {
                cout << "--- MEMORY FULL, REMOVING LRU ---\n";
                Node* t = pop_tail(tail);
                memory.erase(t->page);
                cout << "--- REMOVED PAGE " << t->page << " ---\n";
            }
            memory[i] = n;
            add_node(head, n);
        } else {
            cout << "reading page " << i << " (already present, no page fault)\n";
            Node* n = memory[i];
            n->page = i;
            move_to_head(head, n);
        }
    }
    cout << "Total page faults: " << page_faults << endl;
}
