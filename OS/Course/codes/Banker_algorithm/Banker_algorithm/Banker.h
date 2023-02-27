#pragma once
#include <vector>
#include <iostream>

using namespace std;


const int MAX_PROCESS = 100;
const int MAX_RESOURCE = 100;


// Class for representing a process
class Process {
public:
    int pid;
    vector<int> allocation;
    vector<int> max;
    vector<int> need;
};

void deallocateResources(Process& process, vector<int>& available);


// Function to find if a process can be allocated resources
bool isSafe(vector<Process>& processes, vector<int>& available, vector<bool>& finished) {
    int num_processes = processes.size();
    int num_resources = available.size();

    vector<int> work = available;
    vector<bool> can_finish(num_processes, false);

    int count = 0;
    while (count < num_processes) {
        bool found = false;
        for (int i = 0; i < num_processes; i++) {
            if (!finished[i] && processes[i].need <= work) {
                for (int j = 0; j < num_resources; j++) {
                    work[j] += processes[i].allocation[j];
                }
                can_finish[i] = true;
                found = true;
                count++;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}



// Function to allocate resources to a process
bool allocateResources(Process& process, vector<int>& available) {
    int num_resources = available.size();
    for (int i = 0; i < num_resources; i++) {
        if (process.need[i] > available[i]) {
            return false;
        }
    }

    for (int i = 0; i < num_resources; i++) {
        available[i] -= process.need[i];
        process.allocation[i] += process.need[i];
        process.need[i] = 0;
    }

    deallocateResources(process, available);

    return true;
}


// Function to deallocate resources from a process
void deallocateResources(Process& process, vector<int>& available) {
    int num_resources = available.size();
    for (int i = 0; i < num_resources; i++) {
        available[i] += process.allocation[i];
        process.allocation[i] = 0;
        process.need[i] = process.max[i];
    }
}