#include<iostream>

using namespace std;

/*
ԭ��:�������һ�εĿ�ͷΪ�ָ�������
���Ե�ǰ��һ�ο�ͷ��Ԫ�ش�СΪ��׼,������С��Ԫ��ȫ���ƶ�������ǰ��,��ô������ľͶ������ĺ���,�������ʼ�����յ�λ�÷ָ������
������ͬ�ķ����Էָ��������������,ֱ����һ������������OK
*/

class FastSort
{
private:
	int* parray = nullptr;
	int elemnum = 0;
public:
	FastSort()
	{

	}
	void init(int* parray,int elemnum)
	{
		this->parray = parray;
		this->elemnum = elemnum;
	}
	~FastSort()
	{
		delete[]parray;
	}
	int getelemnum()
	{
		return elemnum;
	}
	void Partsort(int* begin, int* end)//begin������һ�����鿪ͷԪ�ص�ַ,end������һ��ĩβԪ�ص�ַ
	{
		if (sortOK(begin, end))//ȷ����ǰ����Ϊ�����begin<end
		{
			return;
		}
		int* firstptr = begin;
		int* pwalk = begin;
		while (pwalk != end + 1)
		{
			if (*pwalk < *firstptr)
			{
				insert(pwalk, firstptr);
				firstptr = firstptr+1;
			}
			pwalk++;
		}
		Partsort(begin, firstptr-1);
		Partsort(firstptr+1,end);
	}
	bool sortOK(int* begin, int* end)//begin������һ�����鿪ͷԪ�ص�ַ,end������һ��ĩβԪ�ص�ַ
	{
		if (begin >= end)
		{
			return 1;
		}
		else
		{
			int* pwalk = begin;
			while (pwalk != end)
			{
				if (*pwalk > *(pwalk + 1))
				{
					return 0;
				}
				pwalk++;
			}
			return 1;
		}
	}
	void insert(int* oldptr,int* newptr)//Ч���ǽ�oldptrλ�õ�Ԫ�ز��뵽newptr��,����newptr�Լ�֮���Ԫ��ȫ��������
	{
		int num = *oldptr;
		int* oldwalk = oldptr;
		while (oldwalk >= newptr)
		{
			*oldwalk = *(oldwalk - 1);
			oldwalk--;
		}
		*newptr = num;
	}
	void showparray()
	{
		for (int i = 0; i < elemnum; i++)
		{
			cout << parray[i] << " ";
		}
		cout << endl;
	}
	void beginSort()
	{
		Partsort(parray, parray + elemnum - 1);
	}
};


void mainF()
{
	int str[] = { 3,111,97,100,0,100,31,23 };
	FastSort sort1;
	sort1.init(str,8);
	sort1.showparray();
	sort1.beginSort();
	sort1.showparray();

	cin.get();
}