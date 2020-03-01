#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//cgi实质是在网页上执行的exe
void main()
{
	printf("Content-type:text/html\n\n");//告知html网页格式
	printf("环境变量:%s<br><br>", getenv("QUERY_STRING"));
	char* envptr = getenv("QUERY_STRING");
	if (envptr == NULL)
	{
		printf("环境变量为空<br>");
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

