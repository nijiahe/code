#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <functional>
#include <memory>
#include <numeric>
#include <iterator>
#include <cstdlib>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <set>
#include <utility>
#include <cstring>
#include <type_traits>

/*
��һ������Ϊ,ģ������ΪT,����ֵΪ*T,������Ӧ���������ֶ���:
template<typename It>	decltype(*T) fcn(It beg, It end){return *beg;}
template<typename It>	decltype(*beg) fcn(It beg, It end){return *beg;}
���ⶼ�ǲ����е�,��һ��һ�����ǲ����е�,��һ�����ͽ�����һ�����Ǵ��,�ڶ���Ҳ�ǲ��е�,��Ϊ��ʱ��δ����beg
����,β�󷵻����Ϳ��Խ����һ����,��Ϊ��ʱ�������ͱ�д�ں���,����ʱ�������Ѿ�֪����beg�Ǻ�����
����:(ע��:β�󷵻����͵ķ���ֵ��Ҫauto������˵����)
���ڽ����ò���*������ֵ,���Է��ص�����Ϊ T &
����ֻ����T����,��ʱ�����ñ�׼�ⶨ����ͷ�ļ�type_traits�е�����ת��ģ��
����remove_reference<decltype(*beg)>::type����int����T,������T &1
*/

template<typename It>	
auto fcn(It beg, It end) ->decltype(*beg){ 
	/*...*/
	return *beg; 
}

//��ϰ��:����ֵ�㹻���add�汾,������ݷ��ؼӷ��Ľ���Զ�ѡ�ú��ʵ�����
template<typename T>
auto add(T lhs,T rhs)->decltype(lhs + rhs)
{
	return lhs + rhs;
}

int main16_2_3()
{
	

	system("pause");
	return 0;
}