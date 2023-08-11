#include "Process.h"

#include <iostream>
#include <Windows.h>
using namespace std;

#ifdef PRIORITY
Process::Process() :
	_pid(rand() % 1000), 
	_next(nullptr), 
	_priority(rand() % 60), 
	_used_time(0),
	_need_time(rand() % 10),
	_status(MyEnum::WAITING)
{}

int Process::getPriority() const{
	return _priority;
}

void Process::change_Priority(int num) {
	if((_priority += num) <= 0)
		_priority = 0;
}

void Process::change_times() {
	_used_time++;
	_need_time--;
}


#else
Process::Process() :
	_pid(rand() % 1000),
	_next(nullptr),
	_round_time(rand() % 10),
	_used_time(0),
	_need_time(rand() % 20),
	_status(MyEnum::WAITING)
{}
#endif // PRIORITY


#ifdef PRIORITY
Process::Process(int pid,Process * next, int priority, int used_time, int need_time, MyEnum status) 
	:_pid(rand() % 1000),
	_next(next),
	_priority(priority),
	_used_time(used_time),
	_need_time(need_time),
	_status(status)
{}
#else
Process::Process(int pid, Process* next, int round_time, int used_time, int need_time, MyEnum status)
	:_pid(rand() % 1000),
	_next(next),
	_round_time(round_time),
	_used_time(used_time),
	_need_time(need_time),
	_status(status)
{}

void Process::change_times()
{
	_need_time--;
	_used_time++;
}

bool Process::check_round_end()
{
	if(_used_time == _round_time)
	{
		_used_time = 0;
		return true;
	}
	else
	{
		return false;
	}
}

int Process::get_round_time() const
{
	return _round_time;
}
#endif // ROUND

void Process::set_Status(MyEnum status){
	_status = status;
}

int Process::getPid() const{
	return _pid;
}

int Process::get_need_time() const
{
	return _need_time;
}

int Process::get_used_time() const
{
	return _used_time;
}

MyEnum Process::get_status() const
{
	return _status;
}

bool Process::check_End()
{
	return _need_time <= 0;
}

bool Process::operator==(const Process& a)
{
	return _pid == a.getPid();
}



ostream& operator << (ostream & out, Process & pro) {
	out << "PID: " << pro._pid << endl;

#ifdef PRIORITY
	out << "priority: " << pro._priority << endl;
#else // PRIORITY
	out << "Round_time: " << pro._round_time << endl;
#endif

	out << "Used_time: " << pro._used_time << endl;
	out << "Need_time: " << pro._need_time << endl;
	out << "Status: " ;
	switch (pro._status)
	{
	case MyEnum::RUNNING:
		out << "RUNNING" << endl;
		break;
	case MyEnum::WAITING:
		out << "WAITING" << endl;
		break;
	default:
		out << "FINISH" << endl;
		break;
	}
	return out;
}







