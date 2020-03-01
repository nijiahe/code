#include<iostream>

using namespace std;

//利用堆,每次将最大值提取至堆顶,然后将堆顶提取至数组最后方,将数组元素减一,然后将在对堆顶的元素进行提取最大值
/*
				0
		1				2
	3		4		5		6
  7  8    9  10   11 12   13 14
堆排序将一个数组的元素构成如图所示模样,图中数字代表a[0],a[1],……
左边的被称为LeftChild,右边的是RightChild,上方的被称为Parent
①从最后一个元素的父节点开始到0节点,依次整理树,使树的最大值都在父节点,如有12个元素,及从a[5]开始循环到a[0]
②此时a[0]为数组最大值,每个树枝的最大值均在父节点,将a[0]的值和数组最后一个元素交换,数组元素个数--,然后整理a[0]节点的树枝,因为如果父节点发生变化,对应变化的子节点也会被调用函数去整理,所以没问题
③此时即为升序排序数组
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
	//以为传入的parent节点调整parent和left和right的顺序,并且如果parent节点改变,自动为对应节点的子节点重新检测
	void parent_sort(int parent)
	{
		int maxNode;
		if (LeftChild(parent) < elemnum&&array[LeftChild(parent)]>array[parent])//如果左节点存在且左节点大于父节点
		{
			maxNode = LeftChild(parent);
		}
		else
		{
			maxNode = parent;
		}
		if (RightChild(parent) < elemnum&&array[RightChild(parent)]>array[maxNode])//如果右节点存在且右节点大于大的那个节点
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