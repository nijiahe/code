		.386
		.model flat,stdcall
		option casemap:none

include windows.inc
include user32.inc
includelib user32.lib
include kernel32.inc
includelib kernel32.lib
include	gdi32.inc
includelib	gdi32.lib

IDD_DIALOG1               equ              100
IDB_BITMAP1               equ              101
IDB_BITMAP2               equ              102
IDOptoin                  equ              40000
IDSliderBar               equ              40001
IDTitle_Text              equ              40002
IDOnTop                   equ              40003
IDExit                    equ              40004
IDLine                    equ              40005
IDShowPicture             equ              40006
IDAllowChangePicture      equ              40007
IDStaticBox               equ              40008
IDMulableBox              equ              40009
IDTitle        			  equ              40010
IDUserDefine              equ              40011
IDChangePicture           equ              40012
IDUserDefineBox           equ              40013
IDPicture                 equ              40014
IDNum                     equ              40015

.data?
hInstance	dd		?
hBmp1		dd		?
hBmp2		dd		?
dwPos		dd		?

.const
szText1		db		'Hello World!',0
szText2		db		'Text2',0
szText3		db		'UserDefine',0

.code

_ProcWinMain	proc	uses esi edi ebx hWnd,wMsg,wParam,lParam
		local @szBuffer[128]:byte
		
		mov		eax,wMsg
		.if		eax==WM_CLOSE
			invoke	EndDialog,hWnd,NULL
			invoke	DeleteObject,hBmp1
			invoke	DeleteObject,hBmp2
		.elseif	eax==WM_COMMAND
			mov	eax,wParam
			;退出
			.if		ax==IDExit
				invoke SendMessage,hWnd,WM_CLOSE,NULL,NULL
			;切换图片
			.elseif	ax==IDChangePicture
				mov		eax,hBmp1
				xchg	eax,hBmp2
				mov		hBmp1,eax
				invoke	SendDlgItemMessage,hWnd,IDPicture,STM_SETIMAGE,IMAGE_BITMAP,eax
			;置在最前面
			.elseif	ax==IDOnTop
				invoke	IsDlgButtonChecked,hWnd,IDOnTop
				.if		eax==BST_CHECKED
					invoke	SetWindowPos,hWnd,HWND_TOPMOST,0,0,0,0,SWP_NOMOVE or SWP_NOSIZE
				.else	
					invoke	SetWindowPos,hWnd,HWND_NOTOPMOST,0,0,0,0,SWP_NOMOVE or SWP_NOSIZE
				.endif
			;显示隐藏图片
			.elseif	ax==IDShowPicture
				invoke	GetDlgItem,hWnd,IDPicture
				mov		ebx,eax
				invoke	IsWindowVisible,ebx
				.if	eax
					invoke	ShowWindow,ebx,SW_HIDE
				.else
					invoke	ShowWindow,ebx,SW_SHOW
				.endif
			;是否允许切换图片(是否灰化更换图片按钮)
			.elseif	ax==IDAllowChangePicture
				invoke	IsDlgButtonChecked,hWnd,IDAllowChangePicture
				.if	eax==BST_CHECKED
					mov ebx,TRUE
				.else
					xor	ebx,ebx
				.endif
				invoke	GetDlgItem,hWnd,IDChangePicture
				invoke	EnableWindow,eax,ebx
			;模态边框和可变边框(得到窗体属性后为其设置有无边框在设置回去)
			.elseif	ax==IDStaticBox
				invoke	GetWindowLong,hWnd,GWL_STYLE
				and	eax,not WS_THICKFRAME
				invoke	SetWindowLong,hWnd,GWL_STYLE,eax
			.elseif	ax==IDMulableBox
				invoke	GetWindowLong,hWnd,GWL_STYLE
				or	eax,WS_THICKFRAME
				invoke	SetWindowLong,hWnd,GWL_STYLE,eax
			;下拉框
			.elseif	ax==IDTitle
				shr eax,16;逻辑右移
				.if	ax==CBN_SELENDOK
					invoke	SendDlgItemMessage,hWnd,IDTitle,CB_GETCURSEL,0,0
					.if	eax==2
						invoke	GetDlgItem,hWnd,IDUserDefineBox
						invoke	EnableWindow,eax,TRUE
					.else
						mov ebx,eax
						invoke	SendDlgItemMessage,hWnd,IDTitle,CB_GETLBTEXT,ebx,addr @szBuffer
						invoke	SetWindowText,hWnd,addr @szBuffer
						invoke	GetDlgItem,hWnd,IDUserDefineBox
						invoke	EnableWindow,eax,FALSE
					.endif
				.endif
			.elseif	ax==IDUserDefineBox
				invoke	GetDlgItemText,hWnd,IDUserDefineBox,addr @szBuffer,sizeof @szBuffer
				invoke	SetWindowText,hWnd,addr @szBuffer
			.endif
		.elseif	eax==WM_INITDIALOG
			;初始化组合框
			invoke	SendDlgItemMessage,hWnd,IDTitle,CB_ADDSTRING,0,addr szText1
			invoke	SendDlgItemMessage,hWnd,IDTitle,CB_ADDSTRING,0,addr szText2
			invoke	SendDlgItemMessage,hWnd,IDTitle,CB_ADDSTRING,0,addr szText3
			invoke	SendDlgItemMessage,hWnd,IDTitle,CB_SETCURSEL,0,0
			invoke	GetDlgItem,hWnd,IDUserDefineBox
			invoke	EnableWindow,eax,FALSE
			
			invoke	LoadBitmap,hInstance,IDB_BITMAP1
			mov hBmp1,eax
			invoke	LoadBitmap,hInstance,IDB_BITMAP2
			mov hBmp2,eax
			
			;初始化单选钮和复选框
			invoke	CheckDlgButton,hWnd,IDShowPicture,BST_CHECKED
			invoke	CheckDlgButton,hWnd,IDAllowChangePicture,BST_CHECKED
			invoke	CheckDlgButton,hWnd,IDStaticBox,BST_CHECKED
			
			;初始化滚动条
			invoke	SendDlgItemMessage,hWnd,IDSliderBar,SBM_SETRANGE,0,100;初始化滚动条时需要发送这个消息设置滚动范围
		.elseif	eax==WM_HSCROLL	
			mov	eax,wParam
			.if	ax==SB_LINELEFT
				dec	dwPos
			.elseif	ax==SB_LINERIGHT
				inc	dwPos
			.elseif	ax==SB_PAGELEFT
				sub dwPos,10
			.elseif ax==SB_PAGERIGHT
				add dwPos,10
			.elseif	ax==SB_THUMBPOSITION||ax==SB_THUMBTRACK
				mov eax,wParam
				shr	eax,16
				mov dwPos,eax
			.else
				mov eax,TRUE
				ret
			.endif
			cmp	dwPos,0
			jge	@F
			mov	dwPos,0
			@@:
			cmp dwPos,100
			jle @F
			mov dwPos,100
			@@:
			invoke	SetDlgItemInt,hWnd,IDNum,dwPos,FALSE
			invoke	SendDlgItemMessage,hWnd,IDSliderBar,SBM_SETPOS,dwPos,TRUE
		.else
			mov	eax,FALSE
			ret
		.endif
		mov		eax,TRUE
		ret
		;返回false代表自己没有处理,需要系统处理
		;返回true代表自己处理过了
		
_ProcWinMain	endp

start:
		invoke	GetModuleHandle,NULL
		mov		hInstance,eax
		invoke	DialogBoxParam,hInstance,IDD_DIALOG1,NULL,offset _ProcWinMain,NULL
		
		invoke	ExitProcess,NULL
		end	start