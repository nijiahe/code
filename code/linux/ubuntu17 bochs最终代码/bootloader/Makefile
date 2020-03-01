all: boot.bin loader.bin

loader.bin: loader.asm
	nasm loader.asm -o loader.bin

boot.bin: boot.asm
	nasm boot.asm -o boot.bin

clean:
	rm -rf *.bin *.asm~ Makefile~ loader.bin boot.bin
