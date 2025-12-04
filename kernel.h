#ifndef KERNEL_H
#define KERNEL_H

extern "C" void kernel_main();

void print_string(const char* str, unsigned char color, int position);
void print_char(char c, unsigned char color, int position);
char read_key();
void clear_screen();
void draw_box(int x, int y, int width, int height, unsigned char color);
void show_menu();
void handle_input();

void text_editor();
void calculator();
void snake_game();
void clock_display();
void system_info();
void color_settings();
void guess_number_game();

void get_time(int* hour, int* minute, int* second);
int get_random(int min, int max);
void delay(int milliseconds);
void beep(int frequency, int duration);

int string_to_int(const char* str);
void int_to_string(int num, char* buffer);
int string_length(const char* str);
void string_copy(char* dest, const char* src);

#define VIDEO_MEMORY 0xB8000
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25

#define COLOR_BLACK 0x00
#define COLOR_BLUE 0x01
#define COLOR_GREEN 0x02
#define COLOR_CYAN 0x03
#define COLOR_RED 0x04
#define COLOR_MAGENTA 0x05
#define COLOR_BROWN 0x06
#define COLOR_LIGHT_GRAY 0x07
#define COLOR_DARK_GRAY 0x08
#define COLOR_LIGHT_BLUE 0x09
#define COLOR_LIGHT_GREEN 0x0A
#define COLOR_LIGHT_CYAN 0x0B
#define COLOR_LIGHT_RED 0x0C
#define COLOR_LIGHT_MAGENTA 0x0D
#define COLOR_YELLOW 0x0E
#define COLOR_WHITE 0x0F

extern unsigned char THEME_PRIMARY;
extern unsigned char THEME_SECONDARY;
extern unsigned char THEME_ACCENT;
extern unsigned char THEME_TEXT;
extern unsigned char THEME_BACKGROUND;

#endif
