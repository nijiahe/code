#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

class Data
{
public:
	Data(string str);
	void print_Data();

private:
	unsigned year;
	unsigned month;
	unsigned day;
};

Data::Data(string str)
{
	string numstr = "0123456789/";
	string coma = ",";
	string tempstr;

	int flag = 0;//用以判断是哪种形式的数据格式
	int pos1 = 0, pos2 = 0;
	int num = 0;

	if (str.find_first_not_of(numstr) == string::npos)//判断1/1/1990格式
	{
		flag = 1;
	}
	else if (str.find_first_of(coma) != string::npos)//判断January 1,1990格式
	{
		flag = 2;
	}

	switch (flag)
	{
	case 1://处理1/1/1990格式
		pos1 = str.find_first_of("/");
		this->month = stol(str.substr(0, pos1));
		++pos1;
		pos2 = str.find_first_of("/", pos1);
		this->day = stol(str.substr(pos1, pos2));
		++pos2;
		this->year = stol(str.substr(pos2));
		break;
	case 2://处理January 1,1900格式
		pos1 = str.find_first_of(" ");
		tempstr = str.substr(0, pos1);
		if (tempstr == "January")this->month = 1;
		else if (tempstr == "Febuary")this->month = 2;
		else if (tempstr == "March")this->month = 3;
		else if (tempstr == "April")this->month = 4;
		else if (tempstr == "May")this->month = 5;
		else if (tempstr == "June")this->month = 6;
		else if (tempstr == "July")this->month = 7;
		else if (tempstr == "August")this->month = 8;
		else if (tempstr == "September")this->month = 9;
		else if (tempstr == "October")this->month = 10;
		else if (tempstr == "November")this->month = 11;
		else if (tempstr == "December")this->month = 12;
		else cerr << "The input month is an error value" << endl;

		pos2 = str.find_first_of(",");
		++pos1;
		this->day = stol(str.substr(pos1, pos2 - pos1));
		++pos2;
		this->year = stol(str.substr(pos2));

		break;
	case 0://处理Jan 1 1990格式
		pos1 = str.find_first_of(" ");
		tempstr = str.substr(0, pos1);
		if (tempstr == "Jan")this->month = 1;
		else if (tempstr == "Feb")this->month = 2;
		else if (tempstr == "Mar")this->month = 3;
		else if (tempstr == "Apr")this->month = 4;
		else if (tempstr == "May")this->month = 5;
		else if (tempstr == "Jun")this->month = 6;
		else if (tempstr == "Jul")this->month = 7;
		else if (tempstr == "Aug")this->month = 8;
		else if (tempstr == "Sep")this->month = 9;
		else if (tempstr == "Oct")this->month = 10;
		else if (tempstr == "Nov")this->month = 11;
		else if (tempstr == "Dec")this->month = 12;
		else cerr << "The input month is an error value" << endl;

		pos2 = str.find_first_of(" ", ++pos1);
		this->day = stol(str.substr(pos1, pos2 - pos1));
		this->year = stol(str.substr(++pos2));

		break;
	default:
		break;
	}
}

void Data::print_Data()
{
	cout << "The Data is: Year " << this->year << ",Month " << this->month << ",Day " << this->day << endl;
}

void main9_51()
{
	Data data1("December 12,1900");
	Data data2("12/12/1900");
	Data data3("Dec 12 1900");

	data1.print_Data();
	data2.print_Data();
	data3.print_Data();

	system("pause");
}