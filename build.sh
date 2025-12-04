#!/bin/bash

echo "Building Custom OS..."

echo "Step 1: Assembling bootloader..."
nasm -f bin boot.asm -o boot.bin

echo "Step 2: Assembling kernel entry..."
nasm -f elf kernel_entry.asm -o kernel_entry.o

echo "Step 3: Compiling kernel..."
gcc -m32 -c kernel.cpp -o kernel.o -ffreestanding -fno-exceptions -fno-rtti -nostdlib -Wall -Wextra

echo "Step 4: Compiling drivers..."
gcc -m32 -c drivers.cpp -o drivers.o -ffreestanding -fno-exceptions -fno-rtti -nostdlib -Wall -Wextra

echo "Step 5: Compiling apps..."
gcc -m32 -c apps.cpp -o apps.o -ffreestanding -fno-exceptions -fno-rtti -nostdlib -Wall -Wextra

echo "Step 6: Linking kernel..."
ld -m elf_i386 -T link.ld kernel_entry.o kernel.o drivers.o apps.o -o kernel.bin --oformat binary

echo "Step 7: Creating OS image..."
cat boot.bin kernel.bin > os.bin

echo "Step 8: Padding OS image..."
truncate -s 1440K os.bin

echo "Build complete! Run with: qemu-system-i386 -drive format=raw,file=os.bin"
echo ""
echo "Testing in QEMU..."
qemu-system-i386 -drive format=raw,file=os.bin
