#pragma once

#include <string>
#include <algorithm>

int* buildBC(const char* P) {
	int* BC = new int[256];
	size_t m = std::strlen(P);
	for (size_t i = 0; i < 256; i++)
		BC[i] = -1;//初始化,相当于memset成-1,-1表示通配符
	for (size_t i = 0; i < m; i++)
		BC[P[i]] = i;//记录每个字符的最后出现位置
	return BC;
}

//ss表 最大匹配后缀字符表
int* buildSS(const char* P) {
	int m = strlen(P);
	int* ss = new int[m];
	ss[m - 1] = m;//对最后一个字符而言,最大匹配后缀就是字符串本身
	int lo = m - 1, hi = m - 1;//P(lo,hi]和p[m-hi+lo,m)表示当前匹配串
	for (int j = m - 2; j >= 0; j--) {//最后一个元素的ss值已经确定,所以从倒数第二个元素开始
		if ((lo < j) && (ss[m - 1 - (hi - j)] <= j - lo))//若lo<j,则表明此前已有一步使得一个长串与后缀相互匹配,则此后检验的串和尾部的一摸一样
			//只需尾部的匹配的串不大于当前匹配的串的长度,即(ss[m - 1 - (hi - j)] <= j - lo),则可以直接沿用尾部已取得的数值
			ss[j] = ss[m - 1 -(hi-j)];
		else {
			hi = j; lo = __min(lo, hi);//难道说只有相匹配的字符为同一个时才有可能发生(ss[m - 1 - (hi - j)] > j - lo)?
			//暂且这么认为,不然我想不通这里为什么lo=__min(lo,hi),因为hi降低了,lo却还是原来的的话,如果不是全部为统一字符,怎么保证还和后缀匹配?
			while ((0 <= lo) && (P[m - 1 - (hi - lo)] == P[lo])) //如果下一个元素与后缀下一个元素相等,则继续检测
				lo--;//匹配的下界--
			ss[j] = hi - lo;//存入
		}
	}
	return ss;
}

int* buildGS(const char* P) {
	int m = std::strlen(P);
	int* gs = new int[m];
	int* ss = buildSS(P);
	for (int j = 0; j < m; j++)gs[j] = m;//默认都移m个步长
	for (int j = m - 1,i = 0; j >= 0;j--) {//逆序扫描,这样子可以让移动更大的覆盖移动更小的
		if (j + 1 == ss[j]) //情况a,如果当前j的ss是直接到头的,j + 1表示[0,j]的长度,ss[j]表示j处元素前方和尾部后缀的最大匹配长度
			while (i < m - (j + 1))//对于所有的秩大于j,<m的元素,向后移动m-(j+1)都是其一种选择因为这些元素都包含了完整的所需尾部
				gs[i++] = m - j - 1;
	}
	for (size_t j = 0; j < m - 1; j++)//情况b,画家算法
		gs[m - ss[j] - 1] = m - j - 1;//将ss里记录的信息再一次覆盖,若在m-ss[j]-1处失败,则相应的将j移到m-1的位置上,即移动m-1-j
	delete[]ss;
	return gs;
}

//BM算法,兼顾Bad Character坏字符和Good Suffix好后缀
int BM_match(const char* P, const char* T) {
	int* bc = buildBC(P);//坏字符表
	int* gs = buildGS(P);//好后缀表
	size_t i = 0;//模式串与文本串相较的偏移
	while (std::strlen(T) >= i + strlen(P)) {//当模式串没有移出头
		int j = strlen(P)-1;//在模式串中移动的指针,从模式串最后开始
		while (P[j] == T[i + j])//匹配
			if (--i < 0)break;//全部匹配,则break当前循环,因为已经匹配完成了
		if (j < 0)//匹配完成
			break;
		else
			i += std::max(gs[j], j - bc[T[i + j]]);//后移两者中的更大者
	}
	delete[]gs; delete[]bc;
	return i;
}