#include<stdio.h>
#include <direct.h>
#include <string.h>
#include <stdlib.h>
#include<io.h>

/*循环遍历传入文件夹下的所有文件并打印*/
void print_dir(char * file_path, size_t str_size)
{
	int path_str_len = strlen(file_path);
	if (file_path[path_str_len - 1] != '\\')
	{
		strcat_s(file_path, str_size, "\\");
	}
	char file_source[256];
	sprintf_s(file_source, 256, file_path);
	_finddata_t fileDir;
	long handle;

	strcat_s(file_source, 256, "*");
	if ((handle = _findfirst(file_source, &fileDir)) == -1L)
	{
		printf("The Path %s is wrong!<br />", file_source);
	}
	else
	{
		do
		{
			char next_file_path[256];
			sprintf_s(next_file_path, 256, "%s%s", file_path, fileDir.name);
			if (strcmp(fileDir.name, ".") != 0 && strcmp(fileDir.name, "..") != 0)
			{
				if (fileDir.attrib == _A_SUBDIR)
				{
					print_dir(next_file_path, 256);
				}
				else
				{
					if ((fileDir.attrib == _A_ARCH || _A_HIDDEN || _A_RDONLY || _A_SYSTEM))
					{
						char * ptr = strstr(fileDir.name, ".html");
						if (ptr != NULL && strcmp(ptr, ".html") == 0)
						{
							char temp[256];
							_getcwd(temp, 256);
							char * walk = next_file_path;
							walk += strlen(temp);
							while (*walk == '\\' || *walk == '/')
							{
								walk++;
							}
							printf("<a href=\"%s\">%s</a><br />", walk, fileDir.name);
						}
					}
				}
			}
		} while (_findnext(handle, &fileDir) == 0);
	}
	_findclose(handle);
}



int main()
{
	printf("Content-type: text/html;charset=utf-8\n\n");
	char ExePlace[1024];
	_getcwd(ExePlace, 1024);

	print_dir(ExePlace, 1024);


	return 0;
}