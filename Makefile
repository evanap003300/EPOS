all: floppy.img

bin/boot.bin: bootloader/boot.asm
	nasm -f bin bootloader/boot.asm -o bin/boot.bin

build/kernel.o: kernel/kernel.c
	gcc -ffreestanding -m32 -nostdlib -fno-pic -fno-pie -c kernel/kernel.c -o build/kernel.o

bin/kernel.bin: build/kernel.o kernel/linker.ld
	ld -m elf_i386 -T kernel/linker.ld -o bin/kernel.bin build/kernel.o

floppy.img: bin/boot.bin bin/kernel.bin
	dd if=/dev/zero of=floppy.img bs=512 count=2880
	dd if=bin/boot.bin of=floppy.img conv=notrunc bs=512 count=1
	dd if=bin/kernel.bin of=floppy.img conv=notrunc bs=512 seek=1

qemu: floppy.img
	qemu-system-i386 -fda floppy.img -boot a

clean:
	rm -rf bin/*
	rm -rf build/*
	rm -f floppy.img
