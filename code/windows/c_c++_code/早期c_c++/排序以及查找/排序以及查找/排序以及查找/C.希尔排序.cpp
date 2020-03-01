#include<iostream>

using namespace std;

//先隔几个位置将数组大体小的元素排到前面,在进行微调
/*原理
0 1 2 3 4 5 6 7 8 9 
①先取较大的间隔量为其进行大致的排序,如一开始取间隔量为4,则对a[0],a[4],a[8]进行排序,排序原理为插入排序
②缩小间隔量,同上用插入排序
③当间隔量缩小至1时,即用插入排序对整个数组排序,但因为之前已经进行了许多微调,所以性能上提升
特:间隔量最后必须是1
*/
void Shell_Sort(int* array, int elemnum)
{
	if (elemnum <= 0 || array == nullptr)
	{
		return;
	}
	int grade = 0;
	int rearindex;
	int adelem;
	while (elemnum > grade)
	{
		grade = 3 * grade + 1;
	}
	while (grade > 0)
	{
		for (int i = grade; i < elemnum; i++)
		{
			rearindex = i - grade;
			adelem = array[i];
			while (rearindex >= 0 && array[rearindex] > adelem)
			{
				array[rearindex + grade] = array[rearindex];
				rearindex -= grade;
			}
			array[rearindex + grade] = adelem;
		}
		grade = (grade - 1) / 3;
	}
}


void mainC()
{
	int array[10];
	for (int i = 0; i < 10; i++)
	{
		array[i] = rand() % 100;
	}
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cout << endl;
	Shell_Sort(array, 10);
	for (int i = 0; i < 10; i++)
	{
		cout << array[i] << " ";
	}
	cin.get();
}