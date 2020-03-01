#define call_main(x) main##x()

int main1();
int main2();//Vector
int main3();//List
int main4();//Stack,Queue
int main5();//Binarty Tree
int main6();//Map
int main7();//BBST
int main8_1();//Splay
int main8_2();//B-
int main8_3();//RedBlack
int main9_1();//Skiplist
int main9_2();//Hashtable
int main10_1();//Priority Queue
int main10_2();//LeftHeap
int main11_1();//KMP
int main11_2();
int main12_1();//¿ìËÙÅÅĞò
int main12_2();
int main12_3();

#include <cstdlib>
#include <ctime>

int main() {
	srand(time(0));
	call_main(6);
}