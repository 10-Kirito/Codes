#include <algorithm>
#include <chrono>
#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>
#include <map>

using namespace std;

int main()
{

	map<int, string> m;
	for (int i = 0; i < 1000000; i++)
	{
		m[i] = to_string(i);
	}

	vector<string> vec_copy;
	vector<string> vec_move;

	chrono::time_point<chrono::steady_clock> start = chrono::steady_clock::now();
	for_each(m.begin(), m.end(), [&](pair<const int, string>& p) -> void
		{
			vec_copy.push_back(p.second);
		});
	auto end = chrono::steady_clock::now();

	chrono::duration<double> duration = end - start;
	cout << "copy duration: " << duration.count() << endl;

	start = chrono::steady_clock::now();
	for_each(m.begin(), m.end(), [&](pair<const int, string>& p) -> void
		{
			//vec_move.push_back(move(p.second));
			vec_move.emplace_back(p.second);
		});
	end = chrono::steady_clock::now();

	duration = end - start;
	cout << "move duration: " << duration.count() << endl;

	start = chrono::steady_clock::now();
	for_each(m.begin(), m.end(), [](pair<const int, string>& p) -> void
		{
			move(p.second);
		});
	end = chrono::steady_clock::now();
	duration = end - start;
	cout << "move function duration: " << duration.count() << endl;

	int a = 4;
	int b;
	int c;
	start = chrono::steady_clock::now();
	//for_each(m.begin(), m.end(), [](pair<const int, string>& p) -> void
		//{
			//move(p.second);
		//});
	b = std::move(a);
	end = chrono::steady_clock::now();
	duration = end - start;
	cout << "b = std::movec(a)" << duration.count() << endl;

	start = chrono::steady_clock::now();
	//for_each(m.begin(), m.end(), [](pair<const int, string>& p) -> void
		//{
			//move(p.second);
		//});
	c = a;
	end = chrono::steady_clock::now();
	duration = end - start;
	cout << "c = a" << duration.count() << endl;


}