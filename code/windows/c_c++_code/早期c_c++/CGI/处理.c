#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//cgiʵ��������ҳ��ִ�е�exe
void main()
{
	printf("Content-type:text/html\n\n");//��֪html��ҳ��ʽ
	printf("��������:%s<br><br>", getenv("QUERY_STRING"));
	char* envptr = getenv("QUERY_STRING");
	if (envptr == NULL)
	{
		printf("��������Ϊ��<br>");
		return;
	}
	char env[256] = { 0 };
	sprintf(env, envptr);
	char* ptr = strchr(env, '&');
	*ptr = '\0';
	char* start = strstr(env, "text1");
	start += 6;
	printf("%s<br><br>", start);
	char cmd[256];
	sprintf_s(cmd, 256, start);
	strcat(cmd, " >1.txt");
	printf("cmd:%s<br><br>", cmd);
	system(cmd);
	FILE* readp;
	fopen_s(&readp, "1.txt", "r");
	if (readp == NULL)
	{
		return;
	}
	while (!feof(readp))
	{
		char ch = fgetc(readp);
		if (ch == '\n')
		{
			printf("<br>");
		}
		else
		{
			putchar(ch);
		}
	}
	fclose(readp);
}

