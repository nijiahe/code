;功能:修改0号中断函数，使其在触发零号中断时向屏幕中间第0列输出绿字Devide Error
;安全的内存在0:200-0:2FF

assume cs:code

code segment
start:
			;将do0函数保存到一段安全的空间
			mov ax,cs
			mov ds,ax
			mov si,offset do0;设置ds:si指向do0函数
			
			mov ax,0
			mov es,ax
			mov di,200h;设置es:di指向安全空间
			
			mov cx,offset do0_end-offset do0;计算出do0函数的长度并送入cx中
			
			cld;设置传送方向为正方向
			rep movsb;传送
			
			;修改0号中断的指向至do0函数(0号中断的地址位于0:0处)
			mov ax,0
			mov es,ax
			mov word ptr es:[0*4],200h
			mov word ptr es:[0*4+2],0
			
			mov ax,4c00h
			int 21h

	do0:jmp do0_start
			db 'Devide Error!'
do0_start:
			mov ax,0
			mov ds,ax
			mov si,202h;将ds:si指向字符串
			
			mov ax,0b800h
			mov es,ax
			mov di,780h;将es:di指向显存
			
			mov bl,02h
			mov cx,13
		s:mov al,[si]
			mov es:[di],al
			inc si
			inc di
			mov es:[di],bl
			inc di
			loop s
			
			mov ax,4c00h
			int 21h
do0_end:
			nop
			

code ends
end start