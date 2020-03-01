#include<iostream>

using namespace std;

/*
原理:以数组的一段的开头为分割点的排序
①以当前这一段开头的元素大小为基准,将比它小的元素全部移动到它的前面,那么比他大的就都在他的后面,以这个起始点最终的位置分割此数组
②用相同的方法对分割后的数组进行排序,直到这一段数组内排序OK
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
	void Partsort(int* begin, int* end)//begin代表这一段数组开头元素地址,end代表这一段末尾元素地址
	{
		if (sortOK(begin, end))//确保当前排序为完成且begin<end
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
	bool sortOK(int* begin, int* end)//begin代表这一段数组开头元素地址,end代表这一段末尾元素地址
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
	void insert(int* oldptr,int* newptr)//效果是将oldptr位置的元素插入到newptr处,并且newptr以及之后的元素全部往后退
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