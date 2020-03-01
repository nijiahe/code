#include "Stack_evaluate.h"
#include <iostream>

int readNumber(const char *&s) {
	int n = 0;
	while (isdigit(*s)) {
		n = n * 10 + (*s-'0'); *s++;
	}
	return n;
}

int order(char optr) {
	switch (optr)
	{
	case '+':return ADD;
	case '-':return SUB;
	case '*':return MUL;
	case '/':return DIV;
	case '^':return POW;
	case '!':return FAC;
	case '(':return L_P;
	case ')':return R_P;
	case '\0':return EOE;
	default:
		exit(-1);
	}
}

char orderBetween(char topOptr, char curOptr) {
	int n1 = order(topOptr), n2 = order(curOptr);
	return pri[n1][n2];
}

int calcu(int n, char op) {
	int res = 1;
	if (op == '!') {
		while (1 <= n) 
			res *= n--;
	}
	return res;
}

float calcu(float n1, float n2, char op) {
	switch (op)
	{
	case '+':return n1 + n2;
	case '-':return n1 - n2;
	case '*':return n1 * n2;
	case '/':return n1 / n2;
	case '^':return pow(n1,n2);
	default:exit(-1);
	}
}


float evaluate(const char s[],Vector<char> &v) {
	Stack<float> opnm; Stack<char> optr;
	optr.push('\0');//�ڱ���־�����������������������ʾ���ʽ�������
	if (!s || !strlen(s))return 0;
	while (!optr.empty()) {
		if (isdigit(*s)){
			v.insert(*s);
			int n = readNumber(s);
			opnm.push(n); 
		}
		else {
			char op;
			switch (orderBetween(optr.get(),*s))
			{
			case '<'://��ǰ������ᱻ����ջ��
				optr.push(*s); s++; break;
			case '='://��������ʵ�ʷ��������������������,��'(',')'��'\0','\0'
				s++; optr.pop(); break;
			case '>'://'>'��ʾ������ʵ�ʵļ��㿪ʼ����
				op = optr.pop(); v.insert(op);
				if (op == '!') {
					float n = opnm.pop();
					opnm.push((float)(calcu(n, op)));
				}
				else {
					float n2 = opnm.pop(); float n1 = opnm.pop();
					opnm.push(calcu(n1, n2, op));
				}
				break;
			default:
				exit(-1); break;
			}
		}		
	}
	return opnm.pop();
}