#include<iostream>
#include<boost/regex.hpp>
#include<locale>
#include<string>
//������ʽ
//ģ��ƥ��
//ba* ƥ�� b ba  baa baaa baaaa����
//ba+ ƥ�� ba baa baaa������ƥ��b
//ba? ƥ�� b ba
//ba{1,4} ƥ�� ba baa baaa baaaa
//d���� u��д��ĸ w����
using namespace std;

void main()
{
	std::locale::global(std::locale("English"));//����Ӣ�ı��ػ�
	string str = "china Englist";
	boost::regex expr("(\\w+)\\s(\\w+)");
	//cout << boost::regex_match(str, expr)<<endl;//���������ʽ�Ƿ�ƥ��,ƥ�����1,��ƥ�����0;
	boost::smatch what;
	if (boost::regex_search(str, what, expr))
	{
		for (auto ibegin = what.begin(); ibegin != what.end(); ibegin++)
		{
			cout << *ibegin << endl;
		}
	}
	else
	{
		cout << "fault" << endl;
	}
	boost::regex expr2("\\s");
	string kongge = "______";
	std::cout << boost::regex_replace(str, expr2, kongge);//�滻
	cin.get();
}