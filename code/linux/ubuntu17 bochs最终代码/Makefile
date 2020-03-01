all:
	sudo mount Ninux.img /media/ -t vfat -o loop
	make -C bootloader/
	make -C kernel/
	make -C user/
	dd if=bootloader/boot.bin of=Ninux.img bs=512 count=1 conv=notrunc
	sudo cp bootloader/loader.bin /media/
	sudo cp kernel/kernel.bin /media/
	sync
	sudo umount /media/
	sudo mount ~/下载/bochs-2.6.9/disk.img /mnt/
	sudo cp user/init.bin /mnt/
	sync
	sudo umount /mnt/

clean:
	make -C bootloader/ clean
	make -C kernel/ clean
	make -C user/ clean

umount:
	sudo umount /media/
