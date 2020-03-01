#include<iostream>
#include<string>

using namespace std;
/*erase函数的原型如下：
（1）string& erase(size_t pos = 0, size_t n = npos);
（2）iterator erase(iterator position);
（3）iterator erase(iterator first, iterator last);
也就是说有三种用法：
（1）erase(pos, n); 删除从pos开始的n个字符，比如erase(0, 1)就是删除第一个字符
（2）erase(position); 删除position处的一个字符(position是个string类型的迭代器)
（3）erase(first, last); 删除从first到last之间的字符（first和last都是迭代器）*/
void main130()
{
	//char str[] = "asdfg";
	string str("abcdefghijki");
	str.insert(str.begin(), 3, 'z');/*在一个位置插入3个z*/
	str.erase(str.begin());/*删除*/
	str.replace(5, 0, "xxx");/*插入的位置,插入时删除的长度,要插入的字符串*/
	cout << str << endl;
	cout << "********************" << endl;
	int pos1 = str.find("ijk");
	cout << pos1 << endl;/*find找到返回这个字符串在数组的开头位置str[i],失败返回-1*/
	int pos2 = str.find_last_of("i");/*最后一个匹配的位置*/
	cout << pos2 << endl;
	int pos3 = str.find('i', pos1+1);/*指定find从字符串的第几个元素进行查找*/
	cout << pos3 << endl;
	cin.get();
}