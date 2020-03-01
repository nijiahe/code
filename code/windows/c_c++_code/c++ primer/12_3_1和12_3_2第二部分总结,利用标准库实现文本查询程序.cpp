//#include <iostream>
//#include <fstream>
//#include <sstream>
//#include <algorithm>
//#include <functional>
//#include <memory>
//#include <numeric>
//#include <iterator>
//#include <cstdlib>
//#include <string>
//#include <vector>
//#include <list>
//#include <map>
//#include <unordered_map>
//#include <set>
//#include <utility>
//#include <cstring>
//
//class queryresult;
//
//class textquery
//{
//public:
//	using line_no = std::vector<std::string>::size_type;
//	textquery(std::ifstream &infile):file(new std::vector<std::string>)
//	{
//		std::string text;
//		while (std::getline(infile, text))
//		{
//			file->push_back(text);
//			int n = file->size() - 1;
//			std::istringstream line(text);
//			std::string word;
//			while (line >> word)
//			{
//				//获取这个单词所在的行号,若这个单词还不存在,则这个单词会被加进map中
//				//但他所关联的对象是一个空shared_ptr指针,指向set
//				std::shared_ptr<std::set<line_no> > &lines = wm[word];
//				if (!lines)//若是空指针
//					lines.reset(new std::set<line_no>);//为其分配一个set
//				lines->insert(n);//将行号插入set中
//			}
//		}
//	}
//	queryresult query(const std::string& sought) const;
//private:
//	std::shared_ptr<std::vector<std::string> > file;
//	std::map<std::string, std::shared_ptr<std::set<line_no> > > wm;//创建一个由单词到行号的映射,行号由shared_ptr管理
//};
//
//class queryresult {
//	friend std::ostream& print(std::ostream &os, const queryresult &qr)
//	{
//		//如果找到了单词,打印出现次数和所有出现的位置
//		os << qr.sought << "occurs " << qr.lines->size() << " " << "time" << (qr.lines->size() > 1 ? "s" : "") << std::endl;//注这里time后面的"s"是代表time的复数形式
//		for (auto num : *qr.lines)//line是一个set,保存了所有出现过的行号,打印行号和对应的行
//			os << "\t(line " << num + 1 << ") " << *(qr.file->begin() + num) << std::endl;
//		return os;
//	}
//public:
//	queryresult(std::string s, std::shared_ptr<std::set<textquery::line_no> > p, std::shared_ptr<std::vector<std::string> > f)
//		:sought(s), lines(p), file(f){}
//	std::set<textquery::line_no>::iterator begin() { if (lines)return lines->begin(); }
//	std::set<textquery::line_no>::iterator end() { if (lines)return lines->end(); }
//	std::shared_ptr<std::vector<std::string>> get_file() const
//	{
//		return std::make_shared<std::vector<std::string>>(file);
//	}
//private:
//	std::string sought;//查询单词
//	std::shared_ptr<std::set<textquery::line_no> > lines;	//输入的行号
//	std::shared_ptr<std::vector<std::string> > file;	//输入文件
//};
//
//queryresult textquery::query(const std::string& sought) const
//{
//	//如果未找到sought,将返回一个指向此set的指针
//	static std::shared_ptr<std::set<line_no> > nodata(new std::set<line_no>);
//	//使用find而不是下标运算符来查找单词,避免将单词添加到wm中
//	auto loc = wm.find(sought);//寻找这个单词
//	if (loc == wm.end())
//		return queryresult(sought, nodata, file);//未找到,返回的是空set
//	else
//		return queryresult(sought, loc->second, file);//找到,返回一个拥有所有出现过单词的行号的set
//}
//
//void runqueries(std::ifstream& infile)
//{
//	textquery tq(infile);
//	while (true)
//	{
//		std::cout << "enter word to look for, or q to quit: ";
//		std::string s;
//		if (!(std::cin >> s) || s == "q") break;
//		print(std::cout, tq.query(s)) << std::endl;
//	}
//}
//
//int main()
//{
//	/*
//	过程:
//	1.主函数调用runqueries("f:"3.txt");
//	2.runqueries中创建textquery解析f:3.txt,生成一个按照行号排列的,保存了所有行的vector<string>,和一个map<string,set>类型,string为单词,set中保存了单词出现过的所有行号
//	3.runqueries中调用textquery成员函数textquery::query,此函数根据用户输入的单词,生成一个queryresult类型的查找结果,
//	queryresult中保存了要查询的单词,和一个与textquery中map中的set共享的shared_ptr指向此单词出现过的所有行号,
//	和一个与textquery共享的通过shared_ptr保存的文件信息,其中保存了整个文件的句子
//	4.通过textquery::query返回的queryresule类型变量,调用print函数分析queryresule中保存的结果进行打印输出
//	*/
//	std::ifstream ifs("f:\\3.txt");
//	runqueries(ifs);
//
//	system("pause");
//	return 0;
//}
