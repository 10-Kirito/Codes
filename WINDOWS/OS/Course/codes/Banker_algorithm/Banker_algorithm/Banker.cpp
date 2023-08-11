#include "Banker.h"

int main() {
    int num_processes, num_resources;
    cout << "Enter the number of processes: ";
    cin >> num_processes;
    cout << "Enter the number of resources: ";
    cin >> num_resources;

    // Initialize available resources
    vector<int> available(num_resources);
    cout << "Enter the available resources: ";
    for (int i = 0; i < num_resources; i++) {
        cin >> available[i];
    }


    // Initialize processes
    vector<Process> processes(num_processes);
    for (int i = 0; i < num_processes; i++) {
        processes[i].pid = i;
        processes[i].allocation.resize(num_resources);
        processes[i].max.resize(num_resources);
        processes[i].need.resize(num_resources);
        cout << "Enter the allocation matrix for process " << i << ": ";
        for (int j = 0; j < num_resources; j++) {
            cin >> processes[i].allocation[j];
            available[j] -= processes[i].allocation[j];
        }
        cout << "Enter the max matrix for process " << i << ": ";
        for (int j = 0; j < num_resources; j++) {
            cin >> processes[i].max[j];
            processes[i].need[j] = processes[i].max[j] - processes[i].allocation[j];
        }
    }

    // Print initial state
    cout << "Initial state:" << endl;
    cout << "Available: ";
    for (int i = 0; i < num_resources; i++) {
        cout << available[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < num_processes; i++) {
        cout << "Process " << processes[i].pid << ": ";
        cout << "Allocation = [";
        for (int j = 0; j < num_resources; j++) {
            cout << processes[i].allocation[j] << " ";
        }
        cout << "], Max = [";
        for (int j = 0; j < num_resources; j++) {
            cout << processes[i].max[j] << " ";
        }
        cout << "], Need = [";
        for (int j = 0; j < num_resources; j++) {
            cout << processes[i].need[j] << " ";
        }
        cout << "]" << endl;
    }

    // Simulate resource allocation
    vector<bool> finished(num_processes, false);
    while (true) {
        // Check if there is a safe state
        if (isSafe(processes, available, finished)) {
            int i;
            for (i = 0; i < num_processes; i++) {
                if (!finished[i] && allocateResources(processes[i], available)) {
                    //break;
                }
            }
            if (i == num_processes) {
                cout << "Test" << endl;
                break;
            }
        }
        else {
            cout << "No safe state exists." << endl;
            return 0;
        }
    }

    // Print final state
    cout << "Final state:" << endl;
    cout << "Available: ";
    for (int i = 0; i < num_resources; i++) {
        cout << available[i] << " ";
    }
    cout << endl;
    for (int i = 0; i < num_processes; i++) {
        cout << "Process " << processes[i].pid << ": ";
        cout << "Allocation = [";
        for (int j = 0; j < num_resources; j++) {
            cout << processes[i].allocation[j] << " ";
        }
        cout << "], Max = [";
        for (int j = 0; j < num_resources; j++) {
            cout << processes[i].max[j] << " ";
        }
        cout << "], Need = [";
        for (int j = 0; j < num_resources; j++) {
            cout << processes[i].need[j] << " ";
        }
        cout << "]" << endl;
    }

    return 0;
}
