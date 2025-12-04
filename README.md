# Custom OS v2.0 - Enhanced Edition 🚀

Sistem operasi modern dengan 7 aplikasi interaktif untuk arsitektur x86!

## 🎮 Fitur Baru v2.0

### **7 Aplikasi Lengkap:**
1. 📝 **Text Editor** - Write text dengan cursor visual
2. 🧮 **Calculator** - Basic math (+, -, *, /)
3. 🐍 **Snake Game** - Classic game dengan scoring
4. ⏰ **Digital Clock** - Real-time clock display
5. 💻 **System Info** - Detailed system information
6. 🎨 **Color Settings** - 4 tema warna (Blue/Green/Red/Yellow)
7. 🎲 **Guess Number** - Tebak angka 1-100 (7 attempts)

### **Peningkatan Sistem:**
- ✨ Color theming system (dinamis)
- 🔊 PC Speaker beep untuk feedback
- 🎯 Box drawing untuk UI yang lebih menarik
- ⏱️ Real-time clock (RTC BIOS)
- 🎰 Random number generator
- 🔤 String utility functions
- 📦 Modular code architecture

## 📁 File Structure

```
.
├── boot.asm           # Bootloader 512 bytes
├── kernel_entry.asm   # Kernel entry point
├── kernel.h           # Headers & declarations
├── kernel.cpp         # Main kernel
├── drivers.cpp        # System drivers (enhanced)
├── apps.cpp           # 7 applications
├── link.ld            # Linker script
├── build.sh           # Build automation
└── README.md          # This file
```

## 🛠️ Requirements

- **NASM** - Assembler untuk boot.asm
- **GCC** - C++ compiler (32-bit support)
- **LD** - GNU Linker
- **QEMU** - Emulator untuk testing

### Install Dependencies:

**Ubuntu/Debian:**
```bash
sudo apt update
sudo apt install nasm gcc-multilib qemu-system-x86
```

**Arch Linux:**
```bash
sudo pacman -S nasm gcc qemu-system-x86
```

**Fedora:**
```bash
sudo dnf install nasm gcc qemu-system-x86
```

## 🚀 Build & Run

### Quick Start:
```bash
chmod +x build.sh
./build.sh
```

### Manual Build:
```bash
# Step 1: Assemble bootloader
nasm -f bin boot.asm -o boot.bin

# Step 2: Assemble kernel entry
nasm -f elf kernel_entry.asm -o kernel_entry.o

# Step 3: Compile C++ files
gcc -m32 -c kernel.cpp -o kernel.o -ffreestanding -fno-exceptions -fno-rtti -nostdlib
gcc -m32 -c drivers.cpp -o drivers.o -ffreestanding -fno-exceptions -fno-rtti -nostdlib
gcc -m32 -c apps.cpp -o apps.o -ffreestanding -fno-exceptions -fno-rtti -nostdlib

# Step 4: Link kernel
ld -m elf_i386 -T link.ld kernel_entry.o kernel.o drivers.o apps.o -o kernel.bin --oformat binary

# Step 5: Create OS image
cat boot.bin kernel.bin > os.bin

# Step 6: Run in QEMU
qemu-system-i386 -drive format=raw,file=os.bin
```

## 🎮 How to Use

### Main Menu:
Setelah boot, pilih aplikasi dengan menekan angka **1-9**:

1. **Text Editor**
   - Ketik teks bebas
   - Enter untuk baris baru
   - Backspace untuk hapus
   - ESC untuk keluar

2. **Calculator**
   - Input angka pertama
   - Pilih operator (+, -, *, /)
   - Input angka kedua
   - Lihat hasil

3. **Snake Game**
   - Arrow keys untuk kontrol
   - Makan makanan (O) untuk skor
   - Hindari dinding
   - ESC untuk keluar

4. **Clock**
   - Menampilkan waktu real-time
   - Update setiap detik
   - ESC untuk keluar

5. **System Info**
   - Lihat informasi sistem
   - Waktu saat ini
   - Memory & platform info

6. **Color Settings**
   - Pilih tema warna:
     - 1: Blue (default)
     - 2: Green
     - 3: Red
     - 4: Yellow
   - Tema diterapkan ke seluruh UI

7. **Guess Number**
   - Tebak angka 1-100
   - 7 kesempatan
   - Hint: "Too high" / "Too low"

8. **About**
   - Info tentang OS
   - Build information
   - Credits

9. **Exit**
   - Shutdown sistem dengan aman

## 🎨 Color Themes

### Blue Theme (Default)
- Primary: Cyan
- Secondary: Light Blue
- Accent: Yellow

### Green Theme
- Primary: Green
- Secondary: Light Green
- Accent: White

### Red Theme
- Primary: Red
- Secondary: Light Red
- Accent: White

### Yellow Theme
- Primary: Yellow
- Secondary: Brown
- Accent: White

## 🔧 Technical Details

### Memory Map:
```
0x0000 - 0x03FF   : Interrupt Vector Table
0x0400 - 0x04FF   : BIOS Data Area
0x0500 - 0x7BFF   : Free memory
0x7C00 - 0x7DFF   : Bootloader (512 bytes)
0x7E00 - 0x8FFF   : Stack & free space
0x9000            : Stack pointer
0x10000+          : Kernel code
0xB8000           : Video memory (text mode)
```

### Features:
- **Text Mode**: 80x25 characters
- **Color Support**: 16 foreground + 8 background colors
- **Keyboard**: BIOS interrupt 0x16
- **Clock**: RTC via BIOS interrupt 0x1A
- **Sound**: PC Speaker via port 0x61
- **Stack**: Safe stack at 0x9000

## 🛡️ Safety Features

- ✅ Stack overflow protection
- ✅ Input validation (all keyboard input)
- ✅ Memory bounds checking
- ✅ Safe string operations
- ✅ Null pointer checks
- ✅ Division by zero handling (calculator)
- ✅ Game boundary collision detection
- ✅ Buffer overflow prevention

## 🐛 Troubleshooting

### Build Errors:

**Error: "cannot find -lgcc"**
```bash
sudo apt install gcc-multilib
```

**Error: "nasm: command not found"**
```bash
sudo apt install nasm
```

**Error: "ld: cannot find"**
```bash
sudo apt install binutils
```

### Runtime Issues:

**QEMU tidak boot:**
- Pastikan os.bin ada dan berukuran > 512 bytes
- Cek build log untuk errors

**Keyboard tidak respond:**
- Gunakan angka row keyboard, bukan numpad
- Pastikan QEMU window dalam focus

**Snake game lambat:**
- Normal, delay diatur untuk gameplay
- Adjust delay() value di apps.cpp

**Clock tidak update:**
- RTC mungkin tidak akurat di emulator
- Coba di hardware asli

## 🎯 Next Features (Roadmap)

### Coming Soon:
- [ ] Music player (MOD files)
- [ ] File system (FAT12)
- [ ] Multi-tasking
- [ ] Graphics mode (VGA 320x200)
- [ ] Mouse support
- [ ] Network stack
- [ ] Shell/Terminal

## 📝 Code Structure

### drivers.cpp - System Drivers:
- `print_string()` - Text output
- `print_char()` - Single character
- `read_key()` - Keyboard input
- `clear_screen()` - Screen clear
- `draw_box()` - UI borders
- `get_time()` - RTC clock
- `get_random()` - RNG
- `delay()` - Timing
- `beep()` - Sound
- String utilities

### apps.cpp - Applications:
- 7 complete applications
- Menu system
- Input handling
- Theme support

### kernel.cpp - Main Kernel:
- Initialization
- Main loop
- Infinite halt

## 🤝 Contributing

Contributions welcome! Areas to improve:
- More games
- Better graphics
- File system
- Network support
- USB drivers

## 📄 License

Open source - MIT License
Free to use, modify, and learn from!

## 💻 Testing

### In QEMU:
```bash
qemu-system-i386 -drive format=raw,file=os.bin
```

### With debugging:
```bash
qemu-system-i386 -drive format=raw,file=os.bin -serial stdio -monitor stdio
```

### On real hardware:
```bash
# Write to USB drive (CAREFUL! Replace /dev/sdX)
sudo dd if=os.bin of=/dev/sdX bs=512
```
## 🌟 Credits

Built with Clover Studio Team × CloverOtaku:
- x86 Assembly (NASM)
- C++ (Freestanding)
- Coffee ☕
- Patience 🙏

---

**Have fun exploring OS development! 🚀**

For questions or issues, check OSDev forums or Stack Overflow.
