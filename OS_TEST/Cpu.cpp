#include "Cpu.h"
#include "tools.h"

#include <iostream>
#include <Windows.h>
#include <list>
#include <algorithm>
// #include <cstdlib>

Cpu::Cpu(list<Process> wlist, list<Process> rlist)
	:_wlist((wlist)),_rlist(rlist),_output(wlist)
{
	
#ifdef PRIORITY
	// sort waiting process by priority
	_wlist.sort(Compare_Priority);
	// sort all process for show the status of process
	_output.sort(Compare_Pid);
#endif
}


void Cpu::show_process_status() const
{
	cout << "PID: \t\t";
	for (auto &pro : _output)
		cout << pro.getPid() << "\t";
	cout << endl;

#ifdef PRIORITY
	cout << "PRIORITY: \t";
	for (auto& pro : _output)
		cout << pro.getPriority() << "\t";
#else
	cout << "ROUNDTIME: \t";
	for (auto& pro : _output)
		cout << pro.get_round_time() << "\t";
#endif

	cout << endl;
	cout << "CPUTIME: \t";
	for (auto& pro : _output)
		cout << pro.get_used_time() << "\t";
	cout << endl;

	cout << "ALLTIME: \t";
	for (auto& pro : _output)
		cout << pro.get_need_time() << "\t";
	cout << endl;
	cout << "STATUS: \t";

	for(auto &pro:_output)
	{
		switch (pro.get_status()) 
		{
		case MyEnum::RUNNING:
			cout << "RUNNING" << "\t";
			break;
		case MyEnum::WAITING:
			cout << "WAITING" << "\t";
			break;
		default:
			cout << "FINISH" << "\t";
			break;
		}
	}

	cout << endl;


}

void Cpu::show_running_waiting() const
{
	cout << "================================================================" << endl;
	cout << "RUNING PROC\t\t\t\tWAITING PROC" << endl;
	if (_rlist.empty())
		cout << "\t";
	else
		cout << _rlist.front().getPid() << "\t";
	if (_wlist.empty())
		cout << "\t";
	else {
		cout << "\t\t\t\t";
		for (auto& pro : _wlist)
			cout << pro.getPid() << " ";
	}
	cout << endl;

	cout << "================================================================" << endl;
}

bool Cpu::Cpu_status() const
{
	if (_wlist.empty() && _rlist.empty())
		return true;
	else
		return false;
}

#ifdef PRIORITY
void Cpu::priority_schedule()
{
	if (_wlist.empty() && _rlist.empty())
		return;

	list<Process>::iterator ptr;
	list<Process>::iterator ptr_temp;
	Process temp;

	/// 如果当前运行队列为空的话，我们将处于等待队列中最前面的进程移出
	if (_rlist.empty())
	{
		ptr = _wlist.begin();
		_rlist.push_back(*(ptr));
		_wlist.pop_front();

		ptr = _rlist.begin();
		ptr_temp = ::find(_output.begin(), _output.end(), *ptr);
		ptr_temp->set_Status(MyEnum::RUNNING);
		Sleep(1000);
		ptr->change_times();
		ptr->change_Priority(-3);

		// 实时更新进程的状态
		ptr_temp->change_times();
		ptr_temp->change_Priority(-3);

		

		/// 比较当前运行队列中的进程和处于等待状态的进程的优先级
		/// 如果当前运行队列中的进程仍然优先级最高，那么继续调度
		///	否则的话，将其移出队列

		/// 如果当前进程仍然没有结束
		if (!ptr->check_End())
		{
			if (ptr->getPriority() >= _wlist.front().getPriority())
			{
				priority_schedule();
			}
			else
			{

				ptr_temp = ::find(_output.begin(), _output.end(), *ptr);
				ptr_temp->set_Status(MyEnum::WAITING);
				_wlist.push_back(*ptr);
				_rlist.pop_front();
				priority_schedule();
			}
		}
		else
		{
			// 当前进程已经运行完毕
			// ptr->set_Status(MyEnum::FINISH);
			ptr_temp = ::find(_output.begin(), _output.end(), *ptr);
			ptr_temp->set_Status(MyEnum::FINISH);
			_rlist.pop_front();
			priority_schedule();
		}
	}else
	{
		/// 如果当前运行队列不是空的话,对相应的进程进行调度
		ptr = _rlist.begin();
		ptr_temp = ::find(_output.begin(), _output.end(), *ptr);
		ptr_temp->set_Status(MyEnum::RUNNING);
		Sleep(1000);
		ptr->change_times();
		ptr->change_Priority(-3);
		ptr_temp->change_times();
		ptr_temp->change_Priority(-3);


		if (!ptr->check_End())
		{
			if (ptr->getPriority() >= _wlist.front().getPriority())
			{
				// ptr->set_Status(MyEnum::RUNNING);
				priority_schedule();
			}
			else
			{
				// ptr->set_Status(MyEnum::WAITING);
				ptr_temp = ::find(_output.begin(), _output.end(), *ptr);
				ptr_temp->set_Status(MyEnum::WAITING);
				_wlist.push_back(*ptr);
				_rlist.pop_front();
				priority_schedule();
			}
		}
		else
		{
			// ptr->set_Status(MyEnum::FINISH);
			ptr_temp = ::find(_output.begin(), _output.end(), *ptr);
			ptr_temp->set_Status(MyEnum::FINISH);
			_rlist.pop_front();
			priority_schedule();
		}
	}
}

#else
void Cpu::round_schedule()
{
	if (_wlist.empty() && _rlist.empty())
		return;

	list<Process>::iterator ptr;
	list<Process>::iterator ptr_temp;
	Process temp;

	/// 如果当前运行队列为空的话，我们将处于等待队列中最前面的进程移出
	if (_rlist.empty())
	{
		ptr = _wlist.begin();
		_rlist.push_back(*(ptr));
		_wlist.pop_front();

		ptr = _rlist.begin();
		ptr_temp = std::find(_output.begin(), _output.end(), *ptr);
		ptr_temp->set_Status(MyEnum::RUNNING);
		Sleep(1000);
		ptr->change_times();
		// 实时更新进程的状态
		ptr_temp->change_times();

		/// 比较当前正在运行队列中的进程轮转片数是否已经达到
		///	如果已经满足条件，就将其放到等待队列尾部

		if (!ptr->check_End())
		{
			if (!ptr->check_round_end())
			{
				round_schedule();
			}
			else
			{
				ptr->set_Status(MyEnum::WAITING);
				_wlist.push_back(*ptr);
				_rlist.pop_front();
				round_schedule();
			}
		}
		else
		{
			// 当前进程已经运行完毕
			// ptr->set_Status(MyEnum::FINISH);
			ptr_temp = std::find(_output.begin(), _output.end(), *ptr);
			ptr_temp->set_Status(MyEnum::FINISH);
			_rlist.pop_front();
			round_schedule();
		}
	}
	else
	{
		/// 如果当前运行队列不是空的话,对相应的进程进行调度
		ptr = _rlist.begin();
		ptr_temp = std::find(_output.begin(), _output.end(), *ptr);
		ptr_temp->set_Status(MyEnum::RUNNING);
		Sleep(1000);
		ptr->change_times();
		ptr_temp->change_times();


		if (!ptr->check_End())
		{
			if (!ptr->check_round_end())
			{
				//ptr->set_Status(MyEnum::RUNNING);
				round_schedule();
			}
			else
			{
				// ptr->set_Status(MyEnum::WAITING);
				ptr_temp = std::find(_output.begin(), _output.end(), *ptr);
				ptr_temp->set_Status(MyEnum::WAITING);
				_wlist.push_back(*ptr);
				_rlist.pop_front();
				round_schedule();
			}
		}
		else
		{
			// ptr->set_Status(MyEnum::FINISH);
			ptr_temp = std::find(_output.begin(), _output.end(), *ptr);
			ptr_temp->set_Status(MyEnum::FINISH);
			_rlist.pop_front();
			round_schedule();
		}
	}







}
#endif // PRIORITY



