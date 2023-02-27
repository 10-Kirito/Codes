#ifndef _CPU_H
#define _CPU_H

#include "Process.h"


#include <list>

class Cpu
{
protected:
	list<Process> _wlist;
	list<Process> _rlist;

	// used to show the status of process timely
	list<Process> _output;


public:
	Cpu() = default;
	Cpu(list<Process> wlist, list<Process> rlist);
	~Cpu() = default;

	void show_process_status() const;
	void show_running_waiting() const;
	bool Cpu_status() const;

#ifdef PRIORITY
	void priority_schedule();
#else
	void round_schedule();
#endif

	
};

#endif // !_CPU_H



