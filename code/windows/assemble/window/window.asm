		.386
		.model	flat,stdcall
		option	casemap:none
		
include windows.inc    
include user32.inc     
includelib user32.lib  
include kernel32.inc   
includelib kernel32.lib



.data?
hInstance	dd	?
hWinMain	dd	?;用以保存创建窗体返回的窗体句柄

.const
szTitle		db		'Title',0
szText		db		'Text',0
szClass		db		'Class',0

szExitText	db		'确认退出?',0
szExitTitle	db		'窗口',0


.code
_ProcWinMain	proc	uses ebx edi esi hWnd,uMsg,wParam,lParam
		local	@stPs:PAINTSTRUCT
		local	@stRect:RECT
		local	@hDc
		
		mov		eax,uMsg
		.if		eax==WM_PAINT
			invoke	BeginPaint,hWnd,addr @stPs
			mov	@hDc,eax
			
			invoke	GetClientRect,hWnd,addr @stRect
			invoke	DrawText,@hDc,addr szText,-1,addr @stRect,DT_SINGLELINE or DT_CENTER or DT_VCENTER
			
			invoke	EndPaint,hWnd,addr @stPs
		.elseif	eax==WM_CLOSE
			invoke	MessageBoxW,NULL,offset szExitText,offset szExitTitle,MB_YESNO
			.if		eax==IDYES
				invoke	DestroyWindow,hWinMain
				invoke	PostQuitMessage,NULL
			.endif
		.else
			invoke	DefWindowProc,hWnd,uMsg,wParam,lParam
			ret
		.endif
		
		xor eax,eax
		ret	
_ProcWinMain	endp
_WinMain		proc
		local	@stWndClass:WNDCLASSEX                                         
		local	@stMsg:MSG                                                     
		                                                                       
		invoke	RtlZeroMemory,addr @stWndClass,sizeof @stWndClass              
		                                                                       
		invoke	LoadCursor,0,IDC_ARROW                                         
		mov		@stWndClass.hCursor,eax                                        
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
			NULL,NULL,hInstance,NULL                                           
		mov 	hWinMain,eax                                                   
		invoke	ShowWindow,hWinMain,SW_SHOWNORMAL                              
		invoke	UpdateWindow,hWinMain                                          
		                                                                       
		.while	TRUE                                                           
			invoke	GetMessage,addr @stMsg,NULL,0,0                            
			.break	.if	eax==0                                                 
			invoke	TranslateMessage,addr @stMsg                               
			invoke	DispatchMessage,addr @stMsg                                
		.endw                                                                  
		ret                                                                    
		
_WinMain		endp

start:
		call	_WinMain
		invoke	ExitProcess,NULL
		end start