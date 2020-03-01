#include<iostream>
#include"tree.h"
#include"tree.cpp"
#include"leaf.h"


using namespace std;

void main()
{
	tree<double> tree1;
	tree1.addleaf(1.1);
	tree1.addleaf(2.2);
	tree1.addleaf(3.3);
	tree1.addleaf(4.4);
	tree1.addleaf(5.5);
	tree1.addleaf(6.6);
	tree1.addleaf(7.7);
	tree1.addleaf(8.8);
	leaf<double>* leaf4 = tree1.idtoleaf(tree1.topleaf,7);
	cout << leaf4->value << endl;
	tree1.showtreezhongxu(tree1.topleaf);
	cin.get();
}