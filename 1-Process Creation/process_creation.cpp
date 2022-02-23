#include <iostream>
#include <sys/wait.h>
#include <unistd.h>

using namespace std;

int main () {
    pid_t pid = fork();
    if (pid == 0) {
        pid = fork();
        if (pid == 0) {
           cout << "Hello World, I'm the grandchild process and my Process id is: " << getpid() << "\n";
        } else {
            cout << "Hello World, I'm the child process and my Process id is: " << getpid() << "\n";
        }
    } else {
        cout << "Hello World, I'm the parent process and my Process id is: " << getpid() << "\n";
    }

    return 0;
}

/*
Sample Output:

Hello World, I'm the parent process and my Process id is: 1847
Hello World, I'm the child process and my Process id is: 1848
Hello World, I'm the grandchild process and my Process id is: 1849

*/