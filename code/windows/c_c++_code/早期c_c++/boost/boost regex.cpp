#include<iostream>
#include<boost/regex.hpp>
#include<locale>
#include<string>
//正则表达式
//模糊匹配
//ba* 匹配 b ba  baa baaa baaaa……
//ba+ 匹配 ba baa baaa……不匹配b
//ba? 匹配 b ba
//ba{1,4} 匹配 ba baa baaa baaaa
//d数字 u大写字母 w文字
using namespace std;

void main()
{
	std::locale::global(std::locale("English"));//设置英文本地化
	string str = "china Englist";
	boost::regex expr("(\\w+)\\s(\\w+)");
	//cout << boost::regex_match(str, expr)<<endl;//检测正则表达式是否匹配,匹配输出1,不匹配输出0;
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
	std::cout << boost::regex_replace(str, expr2, kongge);//替换
	cin.get();
}