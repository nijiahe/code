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
//				//��ȡ����������ڵ��к�,��������ʻ�������,��������ʻᱻ�ӽ�map��
//				//�����������Ķ�����һ����shared_ptrָ��,ָ��set
//				std::shared_ptr<std::set<line_no> > &lines = wm[word];
//				if (!lines)//���ǿ�ָ��
//					lines.reset(new std::set<line_no>);//Ϊ�����һ��set
//				lines->insert(n);//���кŲ���set��
//			}
//		}
//	}
//	queryresult query(const std::string& sought) const;
//private:
//	std::shared_ptr<std::vector<std::string> > file;
//	std::map<std::string, std::shared_ptr<std::set<line_no> > > wm;//����һ���ɵ��ʵ��кŵ�ӳ��,�к���shared_ptr����
//};
//
//class queryresult {
//	friend std::ostream& print(std::ostream &os, const queryresult &qr)
//	{
//		//����ҵ��˵���,��ӡ���ִ��������г��ֵ�λ��
//		os << qr.sought << "occurs " << qr.lines->size() << " " << "time" << (qr.lines->size() > 1 ? "s" : "") << std::endl;//ע����time�����"s"�Ǵ���time�ĸ�����ʽ
//		for (auto num : *qr.lines)//line��һ��set,���������г��ֹ����к�,��ӡ�кźͶ�Ӧ����
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
//	std::string sought;//��ѯ����
//	std::shared_ptr<std::set<textquery::line_no> > lines;	//������к�
//	std::shared_ptr<std::vector<std::string> > file;	//�����ļ�
//};
//
//queryresult textquery::query(const std::string& sought) const
//{
//	//���δ�ҵ�sought,������һ��ָ���set��ָ��
//	static std::shared_ptr<std::set<line_no> > nodata(new std::set<line_no>);
//	//ʹ��find�������±�����������ҵ���,���⽫������ӵ�wm��
//	auto loc = wm.find(sought);//Ѱ���������
//	if (loc == wm.end())
//		return queryresult(sought, nodata, file);//δ�ҵ�,���ص��ǿ�set
//	else
//		return queryresult(sought, loc->second, file);//�ҵ�,����һ��ӵ�����г��ֹ����ʵ��кŵ�set
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
//	����:
//	1.����������runqueries("f:"3.txt");
//	2.runqueries�д���textquery����f:3.txt,����һ�������к����е�,�����������е�vector<string>,��һ��map<string,set>����,stringΪ����,set�б����˵��ʳ��ֹ��������к�
//	3.runqueries�е���textquery��Ա����textquery::query,�˺��������û�����ĵ���,����һ��queryresult���͵Ĳ��ҽ��,
//	queryresult�б�����Ҫ��ѯ�ĵ���,��һ����textquery��map�е�set�����shared_ptrָ��˵��ʳ��ֹ��������к�,
//	��һ����textquery�����ͨ��shared_ptr������ļ���Ϣ,���б����������ļ��ľ���
//	4.ͨ��textquery::query���ص�queryresule���ͱ���,����print��������queryresule�б���Ľ�����д�ӡ���
//	*/
//	std::ifstream ifs("f:\\3.txt");
//	runqueries(ifs);
//
//	system("pause");
//	return 0;
//}
