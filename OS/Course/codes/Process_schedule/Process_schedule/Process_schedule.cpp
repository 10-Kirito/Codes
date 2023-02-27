#include "Process.h"
#include "Cpu.h"

#include <iostream>
#include <list>
#include <thread>
#include <Windows.h>

using namespace std;


void show_process_timely(const Cpu & cpu)
{
    

	while (!cpu.Cpu_status())
	{
        Sleep(1500);
        cpu.show_running_waiting();
        cpu.show_process_status();
        cout << "================================================================" << endl;
	}
    cout << "SYSTEM FINISHED!!" << endl;
}


void process_schedule(Cpu &cpu)
{
#ifdef PRIORITY
    cpu.priority_schedule();
#else
    cpu.round_schedule();
#endif

}

int main()
{
    Process process[6];
    // create the list of waiting process
    list<Process> _wlist;
    // create the list of running process 
    list<Process> _rlist;


    for (Process temp : process)
    {
        _wlist.push_back(temp);
    }

	// create the CPU
	Cpu _cpu(_wlist, _rlist);

	thread schedule(process_schedule, ref(_cpu));
    thread show_status(show_process_timely, ref(_cpu));

    schedule.join();
    show_status.join();

    return 0;
}

