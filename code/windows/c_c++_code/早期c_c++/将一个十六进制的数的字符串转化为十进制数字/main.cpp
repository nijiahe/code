#include<iostream>
#include<string>
using namespace std;
/*ʵ����:����һ��ʮ�����������ַ���ת��Ϊһ��int��������*/
int dextohex(char* str)
{
	int res = 0;
	int size = strlen(str);
	cout << size << endl;
	if (size > 8)
	{
		cout << "�ַ���̫��" << endl;
		return -1;
	}
	else
	{
		for (int i = 0; i < size; i++)
		{
			if (str[size-1-i] >= '0'&&str[size - 1 - i] <= '9')
			{
				res += (str[size-1-i]-'0') <<(4*i);
			}
			else if (str[size - 1 - i] >= 'a'&&str[size - 1 - i] <= 'f')
			{
				res += (str[size - 1 - i] - 'a'+10) <<(4*i);
			}
			else if (str[size - 1 - i] >= 'A'&&str[size - 1 - i] <= 'F')
			{
				res += (str[size - 1 - i] - 'A'+10) <<(4*i);
			}
			else
			{
				cout << "�����쳣" << endl;
				return -1;
			}
		}
		return res;
	}
}

void main()
{
	cout << dextohex("ffffffff") << endl;


	cin.get();
	return;
}