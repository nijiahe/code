assume cs:code,ds:data,ss:stack

stack segment
	db 1024 dup (0)
stack ends

data segment
	db 'welcome to masm!',0
data ends

code segment
start:mov ax,data
			mov ds,ax
			mov bx,0;将ds:bx指向字符串
			mov ax,0B800H
			mov es,ax
			mov si,0;将es:si指向显存
			mov ax,stack
			mov ss,ax
			mov sp,1024;将栈顶指针指向stack:1024
			
			push ds
			push bx
			call show_str
			add sp,4
			
			
			;函数的功能:传入一个字符串的首地址，在第12行0列的位置一直输出直到遇到0为止
			

	
			mov ax,4c00H
			int 21h
	show_str:
			push bx
			push es
			push si
			push cx
			push bp
			push ds
			
			mov ax,0B800H
			mov es,ax
			mov si,0;将es:si指向显存
			
			mov bp,sp
			mov bx,[bp+14]
			mov ds,[bp+16];将ds:bx指向目标字符串
		s:mov cl,ds:[bx]
			mov ch,0;将字符串的第一个数传递给cl
			jcxz show_str_ret;如果cx是0，跳转到show_str_ret
			;否则输出并且递增，循环执行
			mov al,cl
			mov ah,02h
			mov es:[si+780h],ax
			inc bx
			add si,2
			loop s
			
		show_str_ret:
			pop ds
			pop bp
			pop cx
			pop si
			pop es
			pop bx
			ret

code ends
end start