#include "Stack_algorithm.h"

void convert(Stack<char>& s, _int64 n, int base) {//base表示进制数
	static char digit[] = "0123456789ABCDEF";
	while (n) {
		s.push(digit[n%base]);
		n /= base;
	}
}

bool parenMatch(const char* str,int lo,int hi) {
	Stack<char> s;
	for (int i = lo; i < hi; i++) {
		char c = str[i];
		switch (c)
		{
		case '(':
		case '[':
		case '{':
			s.push(c);
		case ')':
			if (s.empty() || s.pop() != '(')
				return false;
		case ']':
			if (s.empty() || s.pop() != '[')
				return false;
		case '}':
			if (s.empty() || s.pop() != '{')
				return false;
		default:
			break;
		}
	}
	return s.empty();
}

