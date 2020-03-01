// MFC异常.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "MFC异常.h"
#include<iostream>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 唯一的应用程序对象

CWinApp theApp;

using namespace std;

/*异常处理
①TRY:尝试
②THROW:抛出异常
③CATCH:处理异常*/
void openfile()
{
	//CFile file(_T("C:\\123.txt"), CFile::modeRead);
	TRY/*尝试动作,如果异常,抛出异常,让程序稳定执行*/
	{
		CFile file(_T("F:\\123.txt"), CFile::modeRead);/*C++文件*/
	}
	CATCH(CFileException, e)/*捕获异常*//*第一个参数代表问题数据类型,这里为文件类型,第二个存放错误具体数据*/
	{
		if (e->m_cause == CFileException::fileNotFound)/*如果错误,错误类型是文件未找到*/
		{
			cout << "文件不存在" << endl;
		}
	}
	END_CATCH
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])/*_tmain支持宽字符*/
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// 初始化 MFC 并在失败时显示错误
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO:  更改错误代码以符合您的需要
			_tprintf(_T("错误:  MFC 初始化失败\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO:  在此处为应用程序的行为编写代码。			
			//CFile file(_T("F:\\1.txt"), CFile::modeRead);/*C++文件*/
			openfile();
			/* _T代表宽字符 */
			system("pause");
		}
	}
	else
	{
		// TODO:  更改错误代码以符合您的需要
		_tprintf(_T("错误:  GetModuleHandle 失败\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
