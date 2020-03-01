#pragma once

#include "Stack.h"

#define N_OPTR 9
typedef enum { ADD, SUB, MUL, DIV, POW, FAC, L_P, R_P, EOE }Operator;

const char pri[N_OPTR][N_OPTR]{
	/*									��ǰ�����							*/
	/*				 +	 -	 *	 /	 ^	 !	 (	 )	\0	*/
	/*	  +	*/		'>','>','<','<','<','<','<','>','>',
	/* 	  -	*/		'>','>','<','<','<','<','<','>','>',
	/* ջ *	*/		'>','>','>','>','<','<','<','>','>',
	/* �� /	*/		'>','>','>','>','<','<','<','>','>',
	/* �� ^	*/		'>','>','>','>','>','<','<','>','>',
	/* �� !	*/		'>','>','>','>','>','>',' ','>','>',
	/* �� (	*/		'<','<','<','<','<','<','<','=',' ',
	/*	  )	*/		' ',' ',' ',' ',' ',' ',' ',' ',' ',	//ջ���ǲ����ܳ���')'��,������־ʹ���û����֮ƥ���'(',���ʽ����
	/*	 \0 */		'<','<','<','<','<','<','<',' ','='
};

int readNumber(const char *&s);
int order(char optr);
char orderBetween(char topOptr, char curOptr);
int calcu(int n, char op);
float calcu(float n1, float n2, char op);
float evaluate(const char s[], Vector<char> &v);