#pragma once

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <queue>
#include "ExtremumGetter.h"
#include "PosAdder.h"
#include "PosSetter.h"
#include "TreePrinter.h"

struct IntExtremumPair {
    int min;
    int max;
    IntExtremumPair(int rh1 = 0, int rh2 = 0) : min(rh1), max(rh2) {}
};

template<class BinNode, class ValueType>
class VisualTree 
{
public:
    typedef BinNode *BinNode::*           PtrToMember;
    typedef ValueType BinNode::*           PtrToData;

    VisualTree(PtrToMember p, PtrToMember lc, PtrToMember rc, PtrToData val);

    void draw(BinNode *node, const char *promot = NULL);

private:
    void                     adjust_pos(BinNode *root);
    BinNode*                ancestor(BinNode *node);
    int                      digits(int n);
    int                      digits(char c);
    int                      digits(const char*s);
    IntExtremumPair          extreme_pos(BinNode *p);
    ExtremumGetter<BinNode> extreme_node(BinNode *root);
    int                      scan_tree(BinNode *root); 
    template<class VST> void traverse_level(BinNode *p, VST &vst); 
    ExtremumGetter<BinNode> getter;
    TreePrinter<BinNode, ValueType> printer;
    PosSetter<BinNode>      setter;
    PtrToMember              parent, left, right;
    ValueType BinNode::    *value;
};

/*
 * ���캯��
 */
template<class BinNode, class ValueType>
VisualTree<BinNode, ValueType>::VisualTree(PtrToMember p, PtrToMember lc, PtrToMember rc, PtrToData val) :
    getter(), printer(p,lc,rc,val), setter(p,lc,rc), parent(p), left(lc), right(rc), value(val){}

/*
 * Խ�����    
 */
template<class BinNode, class ValueType>
void VisualTree<BinNode, ValueType>::adjust_pos(BinNode *root)
{
    if (root == NULL) {
		return;
    }
    int diff = 0;
    IntExtremumPair extr;
    if (root->*left) {
        extr = extreme_pos(root->*left);
        if (root->pos <= extr.max) { // ������Խ��:�����ڵ����Ƽ�������������
            diff = extr.max - root->pos + 1; 
            PosAdder adder(diff);
            root->add_pos(diff);
            traverse_level(root->*right, adder);
            adjust_pos(ancestor(root));
        }
    } 

    if (root->*right) { // ������Խ�磺������������
        extr = extreme_pos(root->*right);
        if (extr.min <= root->pos) {
            diff = root->pos - extr.min + 1;
            PosAdder adder(diff);
            traverse_level(root->*right, adder);
            adjust_pos(ancestor(root));
        }
    }
}

/*
 * Ѱ�ҽڵ�node�ĵ�һ���������ӵ�����
 * @return ���ȵ�ַ����NULL
 */
template<class BinNode, class ValueType>
BinNode *VisualTree<BinNode, ValueType>::ancestor(BinNode *node)
{
    BinNode *pchild = node;
    BinNode *pparent = node->*parent;
    while (pparent && pchild == pparent->*right) {
        pchild = pparent;
        pparent = pchild->*parent;
    }
    return pparent;

}

/*
 * ����һ������n���ʱռ�õ��ַ���
 * @return ����n���ʱ��ռ�ַ���
 */
template<class BinNode, class ValueType>
int VisualTree<BinNode, ValueType>::digits(int n) 
{
    int len = 0;
    if (n < 0) { 
        len++; 
        n = -n; 
    }
    do {
        len++;
        n /= 10;
    } while (n);
    return len;
}

/*
 * ���һ���ַ���ռ�õ��ַ���
 * @return 1
 */
template<class BinNode, class ValueType>
int VisualTree<BinNode, ValueType>::digits(char c) {
    return 1;
}

/*
 * ���һ���ַ�����ռ�õ��ַ���
 * @return �ַ�������
 */
template<class BinNode, class ValueType>
int VisualTree<BinNode, ValueType>::digits(const char *s){
    return strlen(s);   
}

/*
 * ͼ�λ���ʾ������
 * @input root:���ĸ��ڵ㣬promot:��ѡ��ʾ��Ϣ,Ӧ��'\0'��β
 */

template<class BinNode, class ValueType>
void VisualTree<BinNode, ValueType>::draw(BinNode *root, const char *promot)
{   
    if (promot) { 
        printf("%s\n", promot);
    } 

    if (root == NULL) {
        printf("Empty tree!\n");
        return;
    }
    int len = scan_tree(root);
    printer.set_edge_length(len);
    traverse_level(root, printer);  
}

/*
 * ���������ҵ������ڵ�ָ��
 * @return std::pair, ����firstָ������ڵ㣬secondָ�����ҽڵ�
 */
template<class BinNode, class ValueType>
ExtremumGetter<BinNode> 
VisualTree<BinNode, ValueType>::extreme_node(BinNode *node)
{
    getter.init(node, node);
    traverse_level(node, getter);
    return getter;
}

/* 
 * ������Ľڵ����ҵĽڵ�pos
 * @return ������С/���λ�������IntExtremumPair
 */
template<class BinNode, class ValueType>
IntExtremumPair VisualTree<BinNode, ValueType>::extreme_pos(BinNode *node)
{
    ExtremumGetter<BinNode> nodes = extreme_node(node);
    IntExtremumPair ret;
    if (nodes.min()) { ret.min = nodes.min()->pos; }
    if (nodes.max()) { ret.max = nodes.max()->pos; }
    return ret;
}

/*
 * ɨ�������������������Ϣ�����б��/����λ����
 * @return �������λ��
 */
template<class BinNode, class ValueType>
int VisualTree<BinNode, ValueType>::scan_tree(BinNode *root)
{
    int                    cnt;     // ��ǰ�����ɨ��ڵ����
    int                    depth;   // ��ǰɨ�����
    int                    max_len; 

    std::queue<BinNode*>  qnode;
    std::vector<int>       num_node;  // num_node[i]:  ���Ϊi�Ľڵ�����

    num_node.push_back(1); // һ�����ڵ�
    num_node.push_back(0); // ��ʼ����1��

    qnode.push(root);

    // �����ڵ�λ����Ϊ0���ݴ���������ڵ����λ�� 
    root->pos = 0; 
    traverse_level(root, setter);

    // ��ȡ������������
    IntExtremumPair extr = extreme_pos(root);

    // ������ڵ��������Ϊ0,�����ڵ���������
    PosAdder adder(root->pos - extr.min);
    traverse_level(root, adder);
    cnt = 0; depth = 0; max_len = 0;

    for ( ; !qnode.empty(); qnode.pop()) {
        BinNode *temp = qnode.front();
        adjust_pos(temp);
        if (temp->*left)  { 
            qnode.push(temp->*left);
            num_node[depth+1]++;
        }
        if (temp->*right) { 
            qnode.push(temp->*right); 
            num_node[depth+1]++;
        }

        if (++cnt == num_node[depth]) {
            temp->newline = true;
            depth++;
            num_node.push_back(cnt = 0); // ��ʼ�����²�ڵ����
        } else {
            temp->newline = false;
        }
        max_len = std::max(max_len, digits(temp->*value));

    }
    // ʹ������Ļ���֮�䲻����϶
    extr = extreme_pos(root);
    if (extr.min > 0) { 
        PosAdder adder(-extr.min);
        traverse_level(root,adder);
    }
    return max_len;
}

/* 
 * ��α�����������������ÿ���ڵ�ִ�в���vst
 */
template<class BinNode, class ValueType>
template<class VST>
void VisualTree<BinNode, ValueType>::traverse_level(BinNode *root, VST &vst)
{
    if (root == NULL) {
        return;
    }

    BinNode             *temp;
    std::queue<BinNode*> qnode;
    for (qnode.push(root); !qnode.empty(); qnode.pop()) {
		temp = qnode.front();
        vst(temp);
        if (temp->*left)  { qnode.push(temp->*left); }
		if (temp->*right) { qnode.push(temp->*right); }
    }
}
