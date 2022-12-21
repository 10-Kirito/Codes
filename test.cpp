#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

using namespace std;

int main()
{
	std::string str = "Hello";
	std::vector<std::string> v;

	v.push_back(std::move(str));
	cout << "str: " << str << endl;
	cout << "v: " << endl;
	copy(v.begin(), v.end(), ostream_iterator<string>(cout, "\t"));
}
