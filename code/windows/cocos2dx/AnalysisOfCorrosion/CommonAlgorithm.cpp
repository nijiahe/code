#include "CommonAlgorithm.h"

double strToDouble(const char *str) {
	__String* s = String::create( str);
	return s->doubleValue();
}

int strToInt(const char *str) {
	__String* s = String::create(str);
	return s->intValue();
}
