#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <errno.h>
#include <iostream>
#include <cctype>
#include <fcntl.h>
#include <random>

// defining names for named semaphore initialization
#define PRTR "/prtrsem" // printers
#define PLTR "/pltrsem" // plotters
#define SCNR "/scnrsem" // scanners

using namespace std;

// unlinking preexisting semaphores with the names
int a = sem_unlink(PRTR);
int b = sem_unlink(PLTR);
int c = sem_unlink(SCNR);

// pointer array which will store the pointers to the three named semaphores
// each semaphore is given a O_CREAT flag to prevent reinitialization by other processes
// 0777 code allows for universal permissions
// each semaphore is initialized with appropriate count of available devices
sem_t* resources [3] = {
    sem_open(PRTR, O_CREAT, 0777, 5), 
    sem_open(PLTR, O_CREAT, 0777, 6), 
    sem_open(SCNR, O_CREAT, 0777, 4)
};

string resource_names [3] = {
    "printer",
    "plotter",
    "scanner"
};

// global declarations - out stream for output file generation and necessary functions
ofstream file_out;
int rng(int x, int y); // to generate random integers between x and y using Mersenne twister
void req(); // to request resources

int main() {
    file_out.open("output.txt");
    for (int i = 0; i < 4; i++) {
        // repeated 4 times; runs resource requests for each child, otherwise sleeps for 1-3 seconds
        pid_t id = fork();
        if (id == 0) { 
            // if this is a child process - request a random resource
            req(); 
        } else {
            sleep(rng(1, 3));
        }
    }

    return 0;
}

void req() {
    // resources array is indexed 0 for printer, 1 for plotter, 2 for scanner (request id)
    // as such, we generate a number between 0 and 2:
    int req_id = rng(0, 2);
    // the generated number decides which resource's semaphor and name are to be used throughout the rest of this function:
    sem_t* resource = resources[req_id];
    string resource_name = resource_names[req_id];
    // Request output
    pid_t id = getpid();
    file_out << "*** Process " << id << " is requesting a " << resource_name << " ..." << endl;
    // sem_trywait() attempts to decrement the appropriate semaphore but does not wait if blocked, unlike sem_wait() 
    sem_trywait(resource);
    // if the request failed with error EAGAIN (semaphore blocked), we wait 2-4 seconds to try again:
    while (errno == EAGAIN) {
        errno = 0;
        file_out << "### All " << resource_name << "s busy; process " << id << " waiting..." << endl;
        sleep(rng(2, 4));
        // after the wait, we try again:
        file_out << "*** Process " << id << " is requesting a " << resource_name << " ..." << endl;
        sem_trywait(resource);
    }
    // if resource is available, we either never entered the loop or we left it - we can proceed:
    resource_name[0] = toupper(resource_name[0]); // capitalized for output
    int val;
    sem_getvalue(resource, &val);
    file_out << "--- " << resource_name << " received by process " << id << "; " << val << " " << resource_name << "(s) left" << endl;
    sleep(rng(1, 3));
    // after 1-3 seconds, the resource is released and the process terminates
    sem_post(resource);
    sem_getvalue(resource, &val);
    file_out << "+++ " << resource_name << " released by process " << id << "; " << val << " " << resource_name << "(s) available" << endl;
}

int rng(int x, int y) {
    // helper function to generate random numbers between x and y using Mersenne twister
    random_device os_seed;
    mt19937 generator(os_seed());
    uniform_int_distribution<uint_least32_t> distribute(x, y);
    return distribute(generator);
}