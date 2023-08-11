#ifndef PROCESS_H
#define PROCESS_H

// #define PRIORITY
// #define ROUND
#include<string>
// #include<cstdlib>
using namespace std;

enum class MyEnum{ RUNNING, WAITING, FINISH};


class Process
{
protected:
	int _pid;
	Process* _next;

#ifdef PRIORITY
	int _priority;
#else
	int _round_time;
#endif // ROUND

	int _used_time;
	int _need_time;
	MyEnum _status;

public:

#ifdef PRIORITY
	Process();
#else
	Process();
#endif

#ifdef PRIORITY
	Process(int pid, Process * next, int priority, int used_time, int need_time, MyEnum status);
	int getPriority() const;
	void change_Priority(int num);
	void change_times();
#else
	Process(int pid, Process * next, int round_time, int used_time, int need_time, MyEnum status);
	void change_times();
	bool check_round_end();
	int get_round_time()const;
#endif // PRIORITY

	Process(const Process& pro) = default;
	~Process() = default;
	
	void set_Status(MyEnum status);
	int getPid() const;
	int get_need_time() const;
	int get_used_time() const;
	MyEnum get_status() const;
	bool check_End();
	bool operator == (const Process& a);
	friend ostream& operator << (ostream& out, Process& pro) ;
};

#endif // !PROCESS_H



