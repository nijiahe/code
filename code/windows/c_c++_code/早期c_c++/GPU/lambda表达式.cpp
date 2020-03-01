#include<iostream>
#include<vector>
#include<algorithm>/*�㷨ͷ�ļ�����for_each*/
#include<functional>
using namespace std;

void main00()
{
	vector<int> vec1;
	vec1.push_back(12);
	vec1.push_back(13);
	vec1.push_back(14);
	vec1.push_back(19);
	vector<int>::iterator ibegin, iend;
	ibegin = vec1.begin();
	iend = vec1.end();
	/*[]�з���Ҫ������ֵ��ֵ�����ݵĵ�ַ*/
	for_each(ibegin, iend, [](int &num) {num *= 2; });/*lambda���ʽ������������*/
	for_each(ibegin, iend, [](int num) {cout << num << endl; });
	std::cin.get();
}
/*[]��Ϊ�����б�
[=]��ú������ⲿ�ܻ�õ����оֲ�������constֻ����ʽ
[&]��ú������ⲿ�ܻ�õ����оֲ������Ŀɶ���дģʽ
[a]���a�Ŀɶ�
[&a]�ǻ�ÿɶ���дȨ��
���е�[this]�����Ķ�дȨ��*/
int main01()
{
	vector<int> vec1;
	vec1.push_back(12);
	vec1.push_back(13);
	vec1.push_back(14);
	vec1.push_back(19);
	int a = 10;
	int b = 2;
	for_each(vec1.begin(), vec1.end(), [&a](int &v) {a = 3; v += a;  cout << v << endl; });/*�޸�*/
	//for_each(vec1.begin(), vec1.end(), [=](int &v) {a = 3; v += a;  cout << v << endl; });/*�޸�*/
	/*��=��׽ֻ�ܻ�ȡֻ��Ȩ��*/
	/*��ȡ�ɶ���дȨ����[&]*/
	for_each(vec1.begin(), vec1.end(), [&a](int v) {cout << v << endl; });/*����*/
	std::cin.get();
	return 0;
}
/*��������()ֱ�ӵ���*/
int main02()
{
	[]() {cout << "haha" << endl; }();
	std::cin.get();
	return 0;
}

class test
{
public:
	vector<int>  myv;
	int num;
public:
	test()
	{
		num = 12;
		myv.push_back(10);
		myv.push_back(11);
	}
	void add()
	{

		//[]����this
		int  x = 3;
		
		auto fun1 = [this, x](int v) {this->num = 3; cout << v + x + this->num << endl; };
		//=���ո�������this�����е�ǰ�����ֲ������������Ը�ֵ�����ǿ��Զ�ȡ
		//&�������õķ�ʽ�����ֲ�������this,���Ը�ֵ�����Զ�ȡ
		//��������a,[=]   [a]
		//���� a [&]  [&a]
		//auto fun1 = [&](int v) { cout << v + x + this->num << endl; x = 3; };
		for_each(this->myv.begin(), this->myv.end(), fun1);
	}
};

int main03()
{
	test test1;
	test1.add();
	cin.get();
	return 0;
}
/*lambda���ʽ����ֵ��ʾ��ʽ*/
void main04()
{
	/*��*//*��֪��������*/
	auto minus = [](double num1, double num2)->double {return num1 / num2; };
	/*��*//*λ�÷�������*/
	auto multiminus = [](int num1, double num2)->decltype(num1 / num2) { return num1 / num2; };
	cout << minus(5,6) << endl;
	cout << multiminus(2, 3) << endl;
	cout << endl;
	cin.get();
}
/*multable�ؼ���ʵ�ֻ�ø����Ŀɶ�Ȩ��
�������޸�ԭ����*/
void main()
{
	int num = 10;
	auto show = [num]()mutable {num = 5; cout << "�����ڲ�num:" << num << endl; };
	show();
	cout << "�����ⲿnum:" << num << endl;
	cin.get();
}

//���Կ�����Lambda��Ҫ��Ϊ������֣�
//[�����������]��(���������غ�������)��mutable��exception������->����ֵ���͡�{ ������ }������ֱ���н��ܡ�
//һ��[�����������]����ʶһ��Lambda�Ŀ�ʼ���ⲿ�ֱ�����ڣ�����ʡ�ԡ�������������Ǵ��ݸ��������Զ����ɵĺ���������Ĺ��캯���ġ�
//�����������ֻ��ʹ����Щ������LambdaΪֹʱLambda�������÷�Χ�ڿɼ��ľֲ�����������Lambda�������this�����������������������ʽ��
//1���ա�û��ʹ���κκ������������
//2�� = ���������ڿ���ʹ��Lambda�������÷�Χ�����пɼ��ľֲ�����������Lambda�������this����������ֵ���ݷ�ʽ���൱�ڱ������Զ�Ϊ���ǰ�ֵ���������оֲ���������
//3��&���������ڿ���ʹ��Lambda�������÷�Χ�����пɼ��ľֲ�����������Lambda�������this�������������ô��ݷ�ʽ���൱�ڱ������Զ�Ϊ���ǰ����ô��������оֲ���������
//4��this���������ڿ���ʹ��Lambda�������еĳ�Ա������
//5��a����a��ֵ���д��ݡ���ֵ���д���ʱ���������ڲ����޸Ĵ��ݽ�����a�Ŀ�������ΪĬ������º�����const�ġ�Ҫ�޸Ĵ��ݽ�����a�Ŀ������������mutable���η���
//6��&a����a�����ý��д��ݡ�
//7��a, &b����a��ֵ���д��ݣ�b�����ý��д��ݡ�
//8�� = ��&a, &b����a��b�����ý��д����⣬������������ֵ���д��ݡ�
//9��&, a, b����a��b��ֵ���д����⣬���������������ý��д��ݡ�
//����(���������غ�������)����ʶ���ص�()�������Ĳ�����û�в���ʱ���ⲿ�ֿ���ʡ�ԡ���������ͨ����ֵ���磺(a, b)���Ͱ����ã��磺(&a, &b)�����ַ�ʽ���д��ݡ�
//����mutable��exception�������ⲿ�ֿ���ʡ�ԡ���ֵ���ݺ����������ʱ������mutable���η��󣬿����޸İ�ֵ���ݽ����Ŀ�����ע�������޸Ŀ�����������ֵ������
//exception��������ָ�������׳����쳣�����׳��������͵��쳣������ʹ��throw(int)��
//�ġ�->����ֵ���ͣ���ʶ��������ֵ�����ͣ�������ֵΪvoid�����ߺ�������ֻ��һ��return�ĵط�����ʱ�����������Զ��ƶϳ�����ֵ���ͣ�ʱ���ⲿ�ֿ���ʡ�ԡ�
//�塢{ ������ }����ʶ������ʵ�֣��ⲿ�ֲ���ʡ�ԣ������������Ϊ�ա�