		.386
		.model flat,stdcall
		option casemap:none

include windows.inc
include user32.inc
includelib user32.lib
include kernel32.inc
includelib kernel32.lib

IDR_MENU1             equ             100
IDR_ACCELERATOR1      equ             101
IDI_ICON1             equ             102
IDI_CURSOR1           equ             103
IDI_CURSOR2           equ             104
ID10100               equ             40000
ID10200               equ             40001
ID10300               equ             40002
ID20100               equ             40003
ID20200               equ             40004
ID20300               equ             40005
ID20400               equ             40006
ID20500               equ             40007
ID20600               equ             40008
ID20700               equ             40009
ID20800               equ             40010
ID21000               equ             40011
ID20910               equ             40012
ID20920               equ             40013
ID20930               equ             40014
ID30100               equ             40015
ID30200               equ             40016
ID90100               equ             40017
ID90200               equ             40018


.data?
hInstance	dd		?
hWinMain	dd		?
hMenu		dd		?
hSubMenu	dd		?
hCur1		dd		?
hCur2		dd		?

.const
szTitle		db		'Title',0
szText		db		'Text',0
szClass		db		'Class',0
szFormat	db		'select menu is : %08x',0
szCaption	db		'menu select',0
szMenuHelp	db		'help',0
szMenuAbout	db		'about',0

.code
_DisplayMenuItem	proc	_dwCommandID
		local	@szBuffer[256]:byte
		
		pushad
		invoke	wsprintf,addr @szBuffer,addr szFormat,_dwCommandID
		invoke	MessageBox,hWinMain,addr @szBuffer,offset szCaption,MB_OK
		popad
		ret
_DisplayMenuItem	endp

_Quit	proc
		invoke	DestroyWindow,hWinMain
		invoke	PostQuitMessage,NULL
		ret
_Quit	endp

_ProcWinMain	proc	uses esi edi ebx hWnd,uMsg,wParam,lParam
		local	@stPos:POINT
		local	@hSysMenu
		
		mov		eax,uMsg
		;处理菜单及加速键消息
		.if	eax==WM_CREATE
			;得到菜单栏第2个POPUP菜单的句柄
			invoke	GetSubMenu,hMenu,1
			mov		hSubMenu,eax
			
			invoke	GetSystemMenu,hWnd,FALSE
			mov		@hSysMenu,eax
			;将帮助和关于设置为系统菜单
			invoke	AppendMenu,@hSysMenu,MF_SEPARATOR,0,NULL
			invoke	AppendMenu,@hSysMenu,0,ID30100,offset szMenuHelp
			invoke	AppendMenu,@hSysMenu,0,ID30200,offset szMenuAbout
			
			invoke SendMessage,hWnd,WM_COMMAND,ID20500,NULL
			invoke SendMessage,hWnd,WM_COMMAND,ID30100,NULL
		;选择菜单的消息
		.elseif		eax==WM_COMMAND
			invoke	_DisplayMenuItem,wParam
			mov		eax,wParam
			movzx	eax,ax
			.if		eax==ID10300
				call	_Quit
			;工具栏中的三个可以同时选中的菜单
			.elseif	eax>=ID20910 && eax<=ID20930
				;用ebx保存菜单ID
				mov		ebx,eax
				invoke	GetMenuState,hMenu,ebx,MF_BYCOMMAND
				.if		eax==MF_CHECKED
					mov	eax,MF_UNCHECKED
				.elseif	eax==MF_UNCHECKED
					mov eax,MF_CHECKED
				.endif
				invoke	CheckMenuItem,hMenu,ebx,eax
			;大图标,小图标,列表,详细资料互斥菜单选中
			.elseif	eax>=ID20500 && eax<=ID20800
				invoke	CheckMenuRadioItem,hMenu,ID20500,ID20800,eax,MF_BYCOMMAND
			.elseif eax==ID30100
				invoke	CheckMenuRadioItem,hMenu,ID30100,ID30200,eax,MF_BYCOMMAND
				invoke	SetClassLong,hWnd,GCL_HCURSOR,hCur1
			.elseif eax==ID30200
				invoke	CheckMenuRadioItem,hMenu,ID30100,ID30200,eax,MF_BYCOMMAND
				invoke	SetClassLong,hWnd,GCL_HCURSOR,hCur2
			.endif
				
		;处理系统菜单消息
		
		;按下右键时弹出一个POPUP菜单
		.elseif	eax==WM_RBUTTONDOWN
			invoke	GetCursorPos,addr @stPos
			invoke	TrackPopupMenu,hSubMenu,TPM_LEFTALIGN,@stPos.x,@stPos.y,NULL,hWnd,NULL
		.elseif	eax==WM_CLOSE
			call	_Quit
		.else
			invoke	DefWindowProc,hWnd,uMsg,wParam,lParam
			ret
		.endif
		
		xor		eax,eax
		ret
			
_ProcWinMain	endp

_WinMain		proc
		local	@stWndClass:WNDCLASSEX
		local	@stMsg:MSG
		local	@hAccelerator
		
		invoke	GetModuleHandle,NULL
		mov		hInstance,eax
		invoke	LoadMenu,hInstance,IDR_MENU1
		mov		hMenu,eax
		invoke	LoadAccelerators,hInstance,IDR_ACCELERATOR1
		mov		@hAccelerator,eax
		
		invoke	RtlZeroMemory,addr @stWndClass,sizeof WNDCLASSEX
		
		invoke	LoadCursor,hInstance,IDI_CURSOR1
		mov		hCur1,eax
		invoke	LoadCursor,hInstance,IDI_CURSOR2
		mov		hCur2,eax
		mov		@stWndClass.hCursor,eax
		invoke	LoadIcon,hInstance,IDI_ICON1
		mov		@stWndClass.hIcon,eax
		mov		@stWndClass.hIconSm,eax
		push	hInstance                                                      
		pop		@stWndClass.hInstance;实例句柄                                     
		mov		@stWndClass.cbSize,sizeof WNDCLASSEX;窗口大小                      
		mov		@stWndClass.style,CS_HREDRAW or CS_VREDRAW;窗口风格                
		mov		@stWndClass.lpfnWndProc,offset	_ProcWinMain;消息处理函数            
		mov		@stWndClass.hbrBackground,COLOR_WINDOW+1;背景画刷                  
		mov		@stWndClass.lpszClassName,offset szClass;窗体类名                  
		invoke	RegisterClassEx,addr @stWndClass
		
		invoke	CreateWindowEx,WS_EX_CLIENTEDGE,offset szClass,offset szTitle,\
			WS_OVERLAPPEDWINDOW,\
			100,100,600,400,\
			NULL,hMenu,hInstance,NULL
		mov		hWinMain,eax
		invoke	ShowWindow,hWinMain,SW_SHOWNORMAL
		invoke	UpdateWindow,hWinMain
		
		.while	TRUE
			invoke	GetMessage,addr @stMsg,NULL,0,0
			.break	.if eax==0
			invoke	TranslateAccelerator,hWinMain,@hAccelerator,addr @stMsg
			.if eax==0;如果不是加速键
				invoke	TranslateMessage,addr @stMsg
				invoke	DispatchMessage,addr @stMsg
			.endif
		.endw
		ret
		
_WinMain		endp
start:
		call	_WinMain
		invoke	ExitProcess,NULL
		end	start