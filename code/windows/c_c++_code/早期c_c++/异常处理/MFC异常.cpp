// MFC�쳣.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "MFC�쳣.h"
#include<iostream>
#include <stdlib.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

/*�쳣����
��TRY:����
��THROW:�׳��쳣
��CATCH:�����쳣*/
void openfile()
{
	//CFile file(_T("C:\\123.txt"), CFile::modeRead);
	TRY/*���Զ���,����쳣,�׳��쳣,�ó����ȶ�ִ��*/
	{
		CFile file(_T("F:\\123.txt"), CFile::modeRead);/*C++�ļ�*/
	}
	CATCH(CFileException, e)/*�����쳣*//*��һ����������������������,����Ϊ�ļ�����,�ڶ�����Ŵ����������*/
	{
		if (e->m_cause == CFileException::fileNotFound)/*�������,�����������ļ�δ�ҵ�*/
		{
			cout << "�ļ�������" << endl;
		}
	}
	END_CATCH
}

int _tmain(int argc, TCHAR* argv[], TCHAR* envp[])/*_tmain֧�ֿ��ַ�*/
{
	int nRetCode = 0;

	HMODULE hModule = ::GetModuleHandle(NULL);

	if (hModule != NULL)
	{
		// ��ʼ�� MFC ����ʧ��ʱ��ʾ����
		if (!AfxWinInit(hModule, NULL, ::GetCommandLine(), 0))
		{
			// TODO:  ���Ĵ�������Է���������Ҫ
			_tprintf(_T("����:  MFC ��ʼ��ʧ��\n"));
			nRetCode = 1;
		}
		else
		{
			// TODO:  �ڴ˴�ΪӦ�ó������Ϊ��д���롣			
			//CFile file(_T("F:\\1.txt"), CFile::modeRead);/*C++�ļ�*/
			openfile();
			/* _T������ַ� */
			system("pause");
		}
	}
	else
	{
		// TODO:  ���Ĵ�������Է���������Ҫ
		_tprintf(_T("����:  GetModuleHandle ʧ��\n"));
		nRetCode = 1;
	}

	return nRetCode;
}
