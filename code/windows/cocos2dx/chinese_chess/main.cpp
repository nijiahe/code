#include "main.h"
#include "AppDelegate.h"
#include "cocos2d.h"

USING_NS_CC;

int WINAPI _tWinMain(HINSTANCE hInstance,
                       HINSTANCE hPrevInstance,
                       LPTSTR    lpCmdLine,
                       int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	//��ʼ��socket����
	WSADATA data;
	WSAStartup(MAKEWORD(2, 2), &data);

    // create the application instance
    AppDelegate app;
    return Application::getInstance()->run();
}