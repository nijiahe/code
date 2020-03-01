#include<iostream>
#include<new>
const int buf(512);
char buffer[512];

void main()
{
	int *ch1, *ch2;
	ch1 = new(buffer) int[10];
	ch2 = new(buffer) int[10];
	for (int i = 0; i < 10; i++)
	{
		ch1[i] = i;
		std::cout << " " << &ch1[i];
	}
	std::cout << std::endl;
	for (int i = 0; i < 10; i++)
	{
		ch2[i] = i;
		std::cout << " "<<&ch2[i];
	}


	std::cin.get();
}