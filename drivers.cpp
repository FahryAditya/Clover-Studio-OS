#include "kernel.h"

unsigned char THEME_PRIMARY = COLOR_CYAN;
unsigned char THEME_SECONDARY = COLOR_LIGHT_BLUE;
unsigned char THEME_ACCENT = COLOR_YELLOW;
unsigned char THEME_TEXT = COLOR_WHITE;
unsigned char THEME_BACKGROUND = COLOR_BLACK;

void print_char(char c, unsigned char color, int position) {
    if (position < 0 || position >= SCREEN_WIDTH * SCREEN_HEIGHT * 2) {
        return;
    }
    
    volatile char* video = (volatile char*)VIDEO_MEMORY;
    video[position] = c;
    video[position + 1] = color;
}

void print_string(const char* str, unsigned char color, int position) {
    if (!str || position < 0 || position >= SCREEN_WIDTH * SCREEN_HEIGHT * 2) {
        return;
    }
    
    volatile char* video = (volatile char*)VIDEO_MEMORY;
    int offset = position;
    
    for (int i = 0; str[i] != '\0' && offset < SCREEN_WIDTH * SCREEN_HEIGHT * 2; i++) {
        if (str[i] == '\n') {
            offset = ((offset / (SCREEN_WIDTH * 2)) + 1) * (SCREEN_WIDTH * 2);
            continue;
        }
        video[offset++] = str[i];
        video[offset++] = color;
    }
}

char read_key() {
    char key = 0;
    
    __asm__ volatile (
        "xor %%ax, %%ax\n"
        "int $0x16\n"
        "mov %%al, %0\n"
        : "=r"(key)
        :
        : "ax"
    );
    
    return key;
}

void clear_screen() {
    volatile char* video = (volatile char*)VIDEO_MEMORY;
    
    for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT * 2; i += 2) {
        video[i] = ' ';
        video[i + 1] = (THEME_BACKGROUND << 4) | THEME_TEXT;
    }
}

void draw_box(int x, int y, int width, int height, unsigned char color) {
    if (x < 0 || y < 0 || x + width > SCREEN_WIDTH || y + height > SCREEN_HEIGHT) {
        return;
    }
    
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            int pos = ((y + row) * SCREEN_WIDTH + (x + col)) * 2;
            
            if (row == 0 || row == height - 1 || col == 0 || col == width - 1) {
                if ((row == 0 && col == 0) || (row == 0 && col == width - 1) ||
                    (row == height - 1 && col == 0) || (row == height - 1 && col == width - 1)) {
                    print_char('+', color, pos);
                } else if (row == 0 || row == height - 1) {
                    print_char('-', color, pos);
                } else {
                    print_char('|', color, pos);
                }
            }
        }
    }
}

void get_time(int* hour, int* minute, int* second) {
    unsigned char h = 0, m = 0, s = 0;
    
    __asm__ volatile (
        "mov $0x02, %%ah\n"
        "int $0x1A\n"
        "mov %%ch, %0\n"
        "mov %%cl, %1\n"
        "mov %%dh, %2\n"
        : "=r"(h), "=r"(m), "=r"(s)
        :
        : "ax", "cx", "dx"
    );
    
    *hour = ((h >> 4) * 10) + (h & 0x0F);
    *minute = ((m >> 4) * 10) + (m & 0x0F);
    *second = ((s >> 4) * 10) + (s & 0x0F);
}

static unsigned int random_seed = 12345;

int get_random(int min, int max) {
    random_seed = random_seed * 1103515245 + 12345;
    return min + (random_seed % (max - min + 1));
}

void delay(int milliseconds) {
    for (int i = 0; i < milliseconds * 1000; i++) {
        __asm__ volatile ("nop");
    }
}

void beep(int frequency, int duration) {
    if (frequency < 20 || frequency > 20000) {
        return;
    }
    
    unsigned int divisor = 1193180 / frequency;
    
    __asm__ volatile (
        "mov $0xB6, %%al\n"
        "out %%al, $0x43\n"
        "mov %0, %%ax\n"
        "out %%al, $0x42\n"
        "mov %%ah, %%al\n"
        "out %%al, $0x42\n"
        "in $0x61, %%al\n"
        "or $0x03, %%al\n"
        "out %%al, $0x61\n"
        :
        : "r"(divisor)
        : "ax"
    );
    
    delay(duration);
    
    __asm__ volatile (
        "in $0x61, %%al\n"
        "and $0xFC, %%al\n"
        "out %%al, $0x61\n"
        :
        :
        : "ax"
    );
}

int string_to_int(const char* str) {
    int result = 0;
    int sign = 1;
    int i = 0;
    
    if (str[0] == '-') {
        sign = -1;
        i = 1;
    }
    
    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return result * sign;
}

void int_to_string(int num, char* buffer) {
    int i = 0;
    int is_negative = 0;
    
    if (num == 0) {
        buffer[0] = '0';
        buffer[1] = '\0';
        return;
    }
    
    if (num < 0) {
        is_negative = 1;
        num = -num;
    }
    
    while (num > 0) {
        buffer[i++] = '0' + (num % 10);
        num /= 10;
    }
    
    if (is_negative) {
        buffer[i++] = '-';
    }
    
    buffer[i] = '\0';
    
    for (int j = 0; j < i / 2; j++) {
        char temp = buffer[j];
        buffer[j] = buffer[i - j - 1];
        buffer[i - j - 1] = temp;
    }
}

int string_length(const char* str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

void string_copy(char* dest, const char* src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
}
