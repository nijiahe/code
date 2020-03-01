#pragma once
#include<iostream>
#include "listnode.h"

using namespace std;

template<class T>
class linklist
{
public:
	listnode<T>* ports;//ѭ���ӿ�
	int listlong;//����Ԫ������
public:
	linklist();//����
	~linklist();//����
	listnode<T>* pushback(T value);//��β������   OK
	listnode<T>* indexinsert(int index,T value);//����Ŀ¼������  OK
	listnode<T>* revise(int index, T value);//����Ŀ¼���޸�  OK
	
	listnode<T>* findindex(int index);//����Ŀ¼����   OK
	listnode<T>* findvalue(T value);//������������ݲ���		OK
	void merge(linklist<T> anotherlist);//��������������ϲ�	
	bool remove(int index);//����Ŀ¼��ɾ��
	bool remove(listnode<T>* remnode);//���ݴ���Ľڵ�ɾ��
	void listshow();//��ʾ��������Ԫ��   OK
	//void deletesame();//ɾ����ͬ��Ԫ��
	void rev();//��ת����
	int getlistlong();//��������Ԫ����
	void clean();//��������Ԫ��
};

