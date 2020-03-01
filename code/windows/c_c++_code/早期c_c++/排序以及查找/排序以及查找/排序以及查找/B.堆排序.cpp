#include<iostream>

using namespace std;

//���ö�,ÿ�ν����ֵ��ȡ���Ѷ�,Ȼ�󽫶Ѷ���ȡ���������,������Ԫ�ؼ�һ,Ȼ���ڶԶѶ���Ԫ�ؽ�����ȡ���ֵ
/*
				0
		1				2
	3		4		5		6
  7  8    9  10   11 12   13 14
������һ�������Ԫ�ع�����ͼ��ʾģ��,ͼ�����ִ���a[0],a[1],����
��ߵı���ΪLeftChild,�ұߵ���RightChild,�Ϸ��ı���ΪParent
�ٴ����һ��Ԫ�صĸ��ڵ㿪ʼ��0�ڵ�,����������,ʹ�������ֵ���ڸ��ڵ�,����12��Ԫ��,����a[5]��ʼѭ����a[0]
�ڴ�ʱa[0]Ϊ�������ֵ,ÿ����֦�����ֵ���ڸ��ڵ�,��a[0]��ֵ���������һ��Ԫ�ؽ���,����Ԫ�ظ���--,Ȼ������a[0]�ڵ����֦,��Ϊ������ڵ㷢���仯,��Ӧ�仯���ӽڵ�Ҳ�ᱻ���ú���ȥ����,����û����
�۴�ʱ��Ϊ������������
*/
class HeapSort
{
private:
	int* array;
	int elemnum;
public:
	HeapSort()
	{

	}
	HeapSort(int*array, int elemnum) :array(array), elemnum(elemnum)
	{

	}
	~HeapSort()
	{
		delete []array;
	}
	void Heapinit(int* array,int elemnum)
	{
		this->array = array;
		this->elemnum = elemnum;
	}
	void showarray()
	{
		for (int i = 0; i < elemnum; i++)
		{
			cout << array[i] << " ";
		}
		cout << endl;
	}
	int LeftChild(int Parent)
	{
		return 2 * Parent+1;
	}
	int RightChild(int Parent)
	{
		return 2 * Parent + 2;
	}
	int Parent(int Child)
	{
		return (Child-1) / 2;
	}
	void Swap(int index1,int index2)
	{
		array[index1] = array[index1] + array[index2];
		array[index2] = array[index1] - array[index2];
		array[index1] = array[index1] - array[index2];
	}
	//��Ϊ�����parent�ڵ����parent��left��right��˳��,�������parent�ڵ�ı�,�Զ�Ϊ��Ӧ�ڵ���ӽڵ����¼��
	void parent_sort(int parent)
	{
		int maxNode;
		if (LeftChild(parent) < elemnum&&array[LeftChild(parent)]>array[parent])//�����ڵ��������ڵ���ڸ��ڵ�
		{
			maxNode = LeftChild(parent);
		}
		else
		{
			maxNode = parent;
		}
		if (RightChild(parent) < elemnum&&array[RightChild(parent)]>array[maxNode])//����ҽڵ�������ҽڵ���ڴ���Ǹ��ڵ�
		{
			maxNode = RightChild(parent);
		}
		if (maxNode != parent)
		{
			Swap(parent, maxNode);
			parent_sort(maxNode);
		}
	}
	void BuildMaxHeap()
	{
		for (int i = Parent(elemnum - 1); i >= 0; i--)
		{
			parent_sort(i);
		}
	}
	void Sort()
	{
		int temp = elemnum;
		BuildMaxHeap();
		for (int i = elemnum - 1; i > 0; i--)
		{
			Swap(0, i);
			elemnum--;
			parent_sort(0);
		}
		elemnum = temp;
	}
};


void mainB()
{
	int nArr[10] = { 4, 1, 3, 2, 16, 9, 10, 14, 8, 7 };
	HeapSort sort1(nArr,10);
	sort1.showarray();
	sort1.Sort();
	sort1.showarray();
	cin.get();
}