#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <memory>
#include <numeric>
#include <iterator>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <utility>

class Employee
{
private:
	std::string _name;
	int _id;
	static int count_flag;
public:
	Employee():_id(count_flag++){}
	Employee(std::string name):_name(name),_id(count_flag++){}
	Employee(const Employee& emp):_name(emp._name),_id(count_flag++){}
	Employee operator=(const Employee&) = delete;
	const int id() const { return _id; };
};

int Employee::count_flag = 0;

int main13_1_6()
{


	system("pause");
	return 0;
}
