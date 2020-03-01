#pragma once

#include "Stack.h"

#define N_OPTR 9
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE }Operator;

const char pri[N_OPTR][N_OPTR]{
	/*									当前运算符							*/
	/*				 +	 -	 *	 /	 ^	 !	 (	 )	\0	*/
	/*	  +	*/		'>','>','<','<','<','<','<','>','>',
	/* 	  -	*/		'>','>','<','<','<','<','<','>','>',
	/* 栈 *	*/		'>','>','>','>','<','<','<','>','>',
	/* 顶 /	*/		'>','>','>','>','<','<','<','>','>',
	/* 运 ^	*/		'>','>','>','>','>','<','<','>','>',
	/* 算 !	*/		'>','>','>','>','>','>',' ','>','>',
	/* 符 (	*/		'<','<','<','<','<','<','<','=',' ',
	/*	  )	*/		' ',' ',' ',' ',' ',' ',' ',' ',' ',	//栈顶是不可能出现')'的,如果出现就代表没有与之匹配的'(',表达式错误
	/*	 \0 */		'<','<','<','<','<','<','<',' ','='
};

int readNumber(const char *&s);
int order(char optr);
char orderBetween(char topOptr, char curOptr);
int calcu(int n, char op);
float calcu(float n1, float n2, char op);
float evaluate(const char s[], Vector<char> &v);