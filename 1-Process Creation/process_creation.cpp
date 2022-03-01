#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main () {
    pid_t id = fork(); // A child process is created and the id is assigned to the variable id
    if (id == 0) { // if the id is 0, the process is the forked C (child) process; otherwise, it is the P (parent) process
        id = fork(); // if we're in the child process, we fork again to create a grandchild
        if (id == 0) { // same logic applies; if fork() returns 0, we're in the GC (grandchild) process, otherwise - in the middle process
           cout << "I'm the grandchild process and my process id is: " << getpid() << endl;
        } else {
            cout << "I'm the parent process and my process id is: " << getpid() << endl;
        }
    } else {
        cout << "I'm the grandparent process and my process id is: " << getpid() << endl;
    }

    return 0;
}

/*
Sample Output:

I'm the grandparent process and my process id is: 499
I'm the parent process and my process id is: 500
I'm the grandchild process and my process id is: 501

*/