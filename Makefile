
run: os.img
	qemu-system-x86_64   -smp  cores=3 -fda os.img	


os.img: boot.bin  kernel.bin
	cat boot.bin kernel.bin > os.img


kernel.bin: ./kernel/kernel.c
	gcc -m32 -c kernel/kernel.c -o kernel.o
	nasm kernel/entry.asm -f elf -o entry.o
	nasm kernel/apEntry.asm -f elf -o apEntry.o
	ld -T linker.ld -m elf_i386 -o kernel.bin entry.o apEntry.o  kernel.o


boot.bin: ./boot/bootloader.asm
	cd ./boot
	nasm -o boot.bin ./boot/bootloader.asm
	cd ..


clean: 
	rm -f  ./kernel.o kernel.bin boot.bin os.img entry.o apEntry.o


