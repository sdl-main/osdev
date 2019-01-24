OBJECTS = boot.o kmain.o fb.o common.o dt.o gdt.o idt.o interrupts.o isr.o pic.o timer.o kbd.o
CC = /home/sdl/opt/cross/bin/i686-elf-gcc
CFLAGS = -std=gnu99 -ffreestanding -O2 -Wall -Wextra -nostdlib -c
LD = /home/sdl/opt/cross/bin/i686-elf-gcc
LDFLAGS = -T link.ld -ffreestanding -nostdlib -lgcc
    AS = nasm
    ASFLAGS = -felf32

    copy:
	cp -a ../src/. .

    check:
	if grub-file --is-x86-multiboot kernel.elf; then echo "MULTIBOOT CONFIRMED"; else echo "ERROR: THE FILE IS NOT MULTIBOOT"; fi

    all: clean copy kernel.elf check

    kernel.elf: $(OBJECTS)
	$(LD) $(LDFLAGS) $(OBJECTS) -o kernel.elf

    aba.iso: kernel.elf check
	cp kernel.elf iso/boot/kernel.elf
	genisoimage -R                              \
		    -b boot/grub/stage2_eltorito    \
                    -no-emul-boot                   \
                    -boot-load-size 4               \
                    -input-charset utf8             \
                    -boot-info-table                \
                    -o aba.iso                      \
                    iso

    run: copy aba.iso
	bochs -f bochsrc.txt -q

    %.o: %.c
	$(CC) $(CFLAGS)  $< -o $@

    %.o: %.s
	$(AS) $(ASFLAGS) $< -o $@

    clean:
	rm -rf *.o kernel.elf aba.iso *.c *.s *.h

