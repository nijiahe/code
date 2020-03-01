#pragma once

#define BUFFER_SIZE 100

template<class BinNode, class ValueType>
class TreePrinter
{
public:
	typedef BinNode *BinNode::*PtrToMember;
	typedef ValueType BinNode::*PtrToData;

	TreePrinter(PtrToMember p, PtrToMember l, PtrToMember r, PtrToData d) :
		edge_len(2), num_out(0), vec(), parent(p), left(l), right(r), value(d){}

	void set_edge_length(int len)
	{
		edge_len = std::max(len, 2); // 边沿最小宽度为2
	}

	void operator() (BinNode *node)
	{
		assert(node);
		BinNode *lc = node->*left;
		BinNode *rc = node->*right;
		int      lbl = 0, rbl = 0;  // 左边沿字符长度，右边沿字符长度 
		int      spaces = node->pos * edge_len - num_out; // 占位空白字符数

		if (lc) { lbl = edge_len * (node->pos - (node->*left)->pos) - 1; }
		if (rc) { rbl = edge_len * ((node->*right)->pos - node->pos) - 1; }

		spaces -= lbl;
		assert(spaces >= 0);

		while (spaces--) {
			num_out += printf(" ");
		}

		if (node->*left) {
			vec.push_back(num_out - 1);
			while (lbl--) {
				num_out += printf("_");
			}
		}
	
		num_out += out_value(node->*value,node->color);

		if (node->*right) {
			while (rbl--) {
				num_out += printf("_");
			}
			vec.push_back(num_out);
		}
		if (node->newline) {
			new_line();
		}
	}

private:
	int out_value(char c,RBColor color) {
		int n = sprintf_s<BUFFER_SIZE>(buffer, "%c", c);
		if(RB_RED== color)
			printf("\033[1;31;40m%s\033[0m",buffer);
		else
			printf("%c", c);
		return n;
	}
	int out_value(int i, RBColor color) {
		int n = sprintf_s<BUFFER_SIZE>(buffer, "%d", i);
		if (RB_RED == color)
			printf("\033[1;31;40m%s\033[0m",buffer);
		else
			printf("%d", i);
		return n;
	}
	int out_value(const char *p, RBColor color) {
		int n = sprintf_s<BUFFER_SIZE>(buffer, "%s", p);
		if (RB_RED == color)
			printf("\033[1;31;40m%s\033[0m",buffer);
		else
			printf("%s", p);
		return n;
	}

	void new_line()
	{
		printf("\n");
		if (!vec.empty()) {
			int n = 0, end = vec[vec.size() - 1];
			for (int i = 0; i <= end && n < (int)vec.size(); ++i) {
				if (i == vec[n]) {
					printf("|");
					n++;
				}
				else {
					printf(" ");
				}
			}
		}
		printf("\n");
		num_out = 0;
		vec.clear();
	}

	int                   edge_len;
	int                   num_out;   // 已输出字符数
	std::vector<int>      vec;
	PtrToMember           parent;
	PtrToMember           left;
	PtrToMember           right;
	ValueType BinNode:: *value;

	char buffer[BUFFER_SIZE];//用来存放printf输出字符的缓冲区
};
