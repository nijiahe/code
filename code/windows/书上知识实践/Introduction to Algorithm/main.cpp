#define call_main(x)	main##x()

#include <time.h>
#include <stdlib.h>

int main2_1_2();
int main2_3_2();
int main4_1();
int main15_1_3();
int main15_4();
int mains16_1();
int main19();
int main28();
int main32();

int main() {
	srand(time(NULL));
	call_main(32);

	return 0;
}