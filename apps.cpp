#include "kernel.h"

void show_menu() {
    draw_box(15, 3, 50, 18, THEME_PRIMARY);
    
    print_string("  CUSTOM OS - MAIN MENU  ", THEME_ACCENT, (4 * SCREEN_WIDTH + 27) * 2);
    
    print_string("1. Text Editor", THEME_TEXT, (6 * SCREEN_WIDTH + 20) * 2);
    print_string("2. Calculator", THEME_TEXT, (7 * SCREEN_WIDTH + 20) * 2);
    print_string("3. Snake Game", THEME_TEXT, (8 * SCREEN_WIDTH + 20) * 2);
    print_string("4. Clock", THEME_TEXT, (9 * SCREEN_WIDTH + 20) * 2);
    print_string("5. System Info", THEME_TEXT, (10 * SCREEN_WIDTH + 20) * 2);
    print_string("6. Color Settings", THEME_TEXT, (11 * SCREEN_WIDTH + 20) * 2);
    print_string("7. Guess Number Game", THEME_TEXT, (12 * SCREEN_WIDTH + 20) * 2);
    print_string("8. About", THEME_TEXT, (13 * SCREEN_WIDTH + 20) * 2);
    print_string("9. Exit", THEME_TEXT, (14 * SCREEN_WIDTH + 20) * 2);
    
    print_string("Select (1-9): ", THEME_SECONDARY, (17 * SCREEN_WIDTH + 25) * 2);
}

void text_editor() {
    clear_screen();
    draw_box(2, 1, 76, 22, THEME_PRIMARY);
    print_string("TEXT EDITOR - ESC to exit", THEME_ACCENT, (2 * SCREEN_WIDTH + 27) * 2);
    
    char buffer[1000];
    int buffer_pos = 0;
    int cursor_x = 4;
    int cursor_y = 4;
    
    for (int i = 0; i < 1000; i++) {
        buffer[i] = '\0';
    }
    
    print_string("Type your text (ESC to exit):", THEME_TEXT, (3 * SCREEN_WIDTH + 4) * 2);
    
    while (1) {
        int pos = (cursor_y * SCREEN_WIDTH + cursor_x) * 2;
        print_char('_', THEME_ACCENT, pos);
        
        char key = read_key();
        
        print_char(' ', THEME_TEXT, pos);
        
        if (key == 27) {
            break;
        }
        
        if (key == '\r' || key == '\n') {
            cursor_y++;
            cursor_x = 4;
            if (cursor_y >= 21) cursor_y = 4;
        } else if (key == 8) {
            if (cursor_x > 4) {
                cursor_x--;
                print_char(' ', THEME_TEXT, (cursor_y * SCREEN_WIDTH + cursor_x) * 2);
                if (buffer_pos > 0) buffer_pos--;
            }
        } else if (key >= 32 && key <= 126) {
            if (buffer_pos < 999 && cursor_x < 76) {
                buffer[buffer_pos++] = key;
                print_char(key, THEME_TEXT, (cursor_y * SCREEN_WIDTH + cursor_x) * 2);
                cursor_x++;
                if (cursor_x >= 76) {
                    cursor_x = 4;
                    cursor_y++;
                    if (cursor_y >= 21) cursor_y = 4;
                }
            }
        }
    }
    
    beep(800, 100);
}

void calculator() {
    clear_screen();
    draw_box(20, 5, 40, 15, THEME_PRIMARY);
    print_string("CALCULATOR", THEME_ACCENT, (6 * SCREEN_WIDTH + 35) * 2);
    
    print_string("Enter first number: ", THEME_TEXT, (9 * SCREEN_WIDTH + 24) * 2);
    char num1_str[10] = {0};
    int idx = 0;
    
    while (1) {
        char key = read_key();
        if (key == '\r') break;
        if (key >= '0' && key <= '9' && idx < 9) {
            num1_str[idx++] = key;
            print_char(key, THEME_TEXT, (9 * SCREEN_WIDTH + 44 + idx - 1) * 2);
        } else if (key == 8 && idx > 0) {
            idx--;
            print_char(' ', THEME_TEXT, (9 * SCREEN_WIDTH + 44 + idx) * 2);
        }
    }
    
    print_string("Operation (+,-,*,/): ", THEME_TEXT, (11 * SCREEN_WIDTH + 24) * 2);
    char op = read_key();
    print_char(op, THEME_ACCENT, (11 * SCREEN_WIDTH + 45) * 2);
    
    print_string("Enter second number: ", THEME_TEXT, (13 * SCREEN_WIDTH + 24) * 2);
    char num2_str[10] = {0};
    idx = 0;
    
    while (1) {
        char key = read_key();
        if (key == '\r') break;
        if (key >= '0' && key <= '9' && idx < 9) {
            num2_str[idx++] = key;
            print_char(key, THEME_TEXT, (13 * SCREEN_WIDTH + 45 + idx - 1) * 2);
        } else if (key == 8 && idx > 0) {
            idx--;
            print_char(' ', THEME_TEXT, (13 * SCREEN_WIDTH + 45 + idx) * 2);
        }
    }
    
    int num1 = string_to_int(num1_str);
    int num2 = string_to_int(num2_str);
    int result = 0;
    
    if (op == '+') result = num1 + num2;
    else if (op == '-') result = num1 - num2;
    else if (op == '*') result = num1 * num2;
    else if (op == '/' && num2 != 0) result = num1 / num2;
    
    char result_str[20];
    int_to_string(result, result_str);
    
    print_string("Result: ", THEME_ACCENT, (15 * SCREEN_WIDTH + 24) * 2);
    print_string(result_str, THEME_LIGHT_GREEN, (15 * SCREEN_WIDTH + 32) * 2);
    
    print_string("Press any key...", THEME_TEXT, (18 * SCREEN_WIDTH + 32) * 2);
    read_key();
    beep(1000, 100);
}

void snake_game() {
    clear_screen();
    draw_box(10, 2, 60, 20, THEME_PRIMARY);
    print_string("SNAKE GAME - Arrow Keys, ESC to exit", THEME_ACCENT, (3 * SCREEN_WIDTH + 21) * 2);
    
    int snake_x[100] = {30};
    int snake_y[100] = {12};
    int snake_length = 5;
    int food_x = 40;
    int food_y = 12;
    int dir_x = 1;
    int dir_y = 0;
    int score = 0;
    
    for (int i = 1; i < snake_length; i++) {
        snake_x[i] = snake_x[0] - i;
        snake_y[i] = snake_y[0];
    }
    
    while (1) {
        print_char('O', THEME_LIGHT_RED, (food_y * SCREEN_WIDTH + food_x) * 2);
        
        for (int i = 0; i < snake_length; i++) {
            char c = (i == 0) ? '@' : '#';
            print_char(c, THEME_LIGHT_GREEN, (snake_y[i] * SCREEN_WIDTH + snake_x[i]) * 2);
        }
        
        delay(150);
        
        __asm__ volatile (
            "mov $0x01, %%ah\n"
            "int $0x16\n"
            : : : "ax"
        );
        
        char scancode = 0;
        __asm__ volatile (
            "mov $0x01, %%ah\n"
            "int $0x16\n"
            "jz no_key\n"
            "xor %%ah, %%ah\n"
            "int $0x16\n"
            "mov %%ah, %0\n"
            "no_key:\n"
            : "=r"(scancode)
            :
            : "ax"
        );
        
        if (scancode == 0x48 && dir_y == 0) { dir_x = 0; dir_y = -1; }
        if (scancode == 0x50 && dir_y == 0) { dir_x = 0; dir_y = 1; }
        if (scancode == 0x4B && dir_x == 0) { dir_x = -1; dir_y = 0; }
        if (scancode == 0x4D && dir_x == 0) { dir_x = 1; dir_y = 0; }
        if (scancode == 0x01) break;
        
        for (int i = snake_length - 1; i > 0; i--) {
            snake_x[i] = snake_x[i - 1];
            snake_y[i] = snake_y[i - 1];
        }
        
        snake_x[0] += dir_x;
        snake_y[0] += dir_y;
        
        if (snake_x[0] <= 10 || snake_x[0] >= 69 || snake_y[0] <= 2 || snake_y[0] >= 21) {
            print_string("GAME OVER!", THEME_LIGHT_RED, (12 * SCREEN_WIDTH + 35) * 2);
            beep(400, 500);
            delay(2000);
            break;
        }
        
        if (snake_x[0] == food_x && snake_y[0] == food_y) {
            snake_length++;
            score += 10;
            food_x = get_random(12, 67);
            food_y = get_random(4, 19);
            beep(1200, 50);
        }
        
        char score_str[20] = "Score: ";
        char score_num[10];
        int_to_string(score, score_num);
        int len = string_length(score_str);
        for (int i = 0; score_num[i] != '\0'; i++) {
            score_str[len++] = score_num[i];
        }
        score_str[len] = '\0';
        print_string(score_str, THEME_YELLOW, (22 * SCREEN_WIDTH + 12) * 2);
        
        for (int i = snake_length - 1; i > 0; i--) {
            print_char(' ', THEME_TEXT, (snake_y[i] * SCREEN_WIDTH + snake_x[i]) * 2);
        }
    }
    
    print_string("Press any key...", THEME_TEXT, (23 * SCREEN_WIDTH + 32) * 2);
    read_key();
}

void clock_display() {
    clear_screen();
    draw_box(25, 8, 30, 10, THEME_PRIMARY);
    print_string("DIGITAL CLOCK", THEME_ACCENT, (9 * SCREEN_WIDTH + 33) * 2);
    
    print_string("Press ESC to exit", THEME_TEXT, (17 * SCREEN_WIDTH + 31) * 2);
    
    for (int i = 0; i < 300; i++) {
        int hour, minute, second;
        get_time(&hour, &minute, &second);
        
        char time_str[20];
        char h[3], m[3], s[3];
        int_to_string(hour, h);
        int_to_string(minute, m);
        int_to_string(second, s);
        
        int idx = 0;
        if (hour < 10) time_str[idx++] = '0';
        for (int j = 0; h[j] != '\0'; j++) time_str[idx++] = h[j];
        time_str[idx++] = ':';
        if (minute < 10) time_str[idx++] = '0';
        for (int j = 0; m[j] != '\0'; j++) time_str[idx++] = m[j];
        time_str[idx++] = ':';
        if (second < 10) time_str[idx++] = '0';
        for (int j = 0; s[j] != '\0'; j++) time_str[idx++] = s[j];
        time_str[idx] = '\0';
        
        print_string("     ", THEME_TEXT, (12 * SCREEN_WIDTH + 35) * 2);
        print_string(time_str, THEME_LIGHT_CYAN, (12 * SCREEN_WIDTH + 35) * 2);
        
        delay(1000);
        
        __asm__ volatile (
            "mov $0x01, %%ah\n"
            "int $0x16\n"
            "jz no_key_clock\n"
            "xor %%ah, %%ah\n"
            "int $0x16\n"
            "cmp $27, %%al\n"
            "je exit_clock\n"
            "no_key_clock:\n"
            "jmp end_clock\n"
            "exit_clock:\n"
            "mov $1, %0\n"
            "end_clock:\n"
            : "=r"(i)
            :
            : "ax"
        );
        
        if (i == 1) break;
    }
    
    beep(800, 100);
}

void system_info() {
    clear_screen();
    draw_box(15, 4, 50, 16, THEME_PRIMARY);
    print_string("SYSTEM INFORMATION", THEME_ACCENT, (5 * SCREEN_WIDTH + 31) * 2);
    
    print_string("OS Name    : Custom OS", THEME_TEXT, (7 * SCREEN_WIDTH + 20) * 2);
    print_string("Version    : 2.0 Enhanced", THEME_TEXT, (8 * SCREEN_WIDTH + 20) * 2);
    print_string("Platform   : x86", THEME_TEXT, (9 * SCREEN_WIDTH + 20) * 2);
    print_string("Build      : Prototype Extended", THEME_TEXT, (10 * SCREEN_WIDTH + 20) * 2);
    print_string("Memory     : 640 KB", THEME_TEXT, (11 * SCREEN_WIDTH + 20) * 2);
    print_string("Status     : Running", THEME_LIGHT_GREEN, (12 * SCREEN_WIDTH + 20) * 2);
    
    int hour, minute, second;
    get_time(&hour, &minute, &second);
    char time_str[30] = "Time       : ";
    char h[3], m[3], s[3];
    int_to_string(hour, h);
    int_to_string(minute, m);
    int_to_string(second, s);
    
    int idx = string_length(time_str);
    if (hour < 10) time_str[idx++] = '0';
    for (int i = 0; h[i] != '\0'; i++) time_str[idx++] = h[i];
    time_str[idx++] = ':';
    if (minute < 10) time_str[idx++] = '0';
    for (int i = 0; m[i] != '\0'; i++) time_str[idx++] = m[i];
    time_str[idx++] = ':';
    if (second < 10) time_str[idx++] = '0';
    for (int i = 0; s[i] != '\0'; i++) time_str[idx++] = s[i];
    time_str[idx] = '\0';
    
    print_string(time_str, THEME_TEXT, (13 * SCREEN_WIDTH + 20) * 2);
    
    print_string("Features   : 7 Apps Available", THEME_TEXT, (14 * SCREEN_WIDTH + 20) * 2);
    
    print_string("Press any key to continue...", THEME_SECONDARY, (18 * SCREEN_WIDTH + 26) * 2);
    read_key();
    beep(1000, 100);
}

void color_settings() {
    clear_screen();
    draw_box(20, 5, 40, 14, THEME_PRIMARY);
    print_string("COLOR THEME SETTINGS", THEME_ACCENT, (6 * SCREEN_WIDTH + 30) * 2);
    
    print_string("1. Blue Theme (Default)", THEME_TEXT, (9 * SCREEN_WIDTH + 24) * 2);
    print_string("2. Green Theme", THEME_TEXT, (10 * SCREEN_WIDTH + 24) * 2);
    print_string("3. Red Theme", THEME_TEXT, (11 * SCREEN_WIDTH + 24) * 2);
    print_string("4. Yellow Theme", THEME_TEXT, (12 * SCREEN_WIDTH + 24) * 2);
    
    print_string("Select (1-4): ", THEME_SECONDARY, (15 * SCREEN_WIDTH + 28) * 2);
    
    char choice = read_key();
    
    if (choice == '1') {
        THEME_PRIMARY = COLOR_CYAN;
        THEME_SECONDARY = COLOR_LIGHT_BLUE;
        THEME_ACCENT = COLOR_YELLOW;
    } else if (choice == '2') {
        THEME_PRIMARY = COLOR_GREEN;
        THEME_SECONDARY = COLOR_LIGHT_GREEN;
        THEME_ACCENT = COLOR_WHITE;
    } else if (choice == '3') {
        THEME_PRIMARY = COLOR_RED;
        THEME_SECONDARY = COLOR_LIGHT_RED;
        THEME_ACCENT = COLOR_WHITE;
    } else if (choice == '4') {
        THEME_PRIMARY = COLOR_YELLOW;
        THEME_SECONDARY = COLOR_BROWN;
        THEME_ACCENT = COLOR_WHITE;
    }
    
    beep(1200, 100);
    clear_screen();
    print_string("Theme changed successfully!", THEME_ACCENT, (12 * SCREEN_WIDTH + 26) * 2);
    delay(1000);
}

void guess_number_game() {
    clear_screen();
    draw_box(18, 6, 44, 14, THEME_PRIMARY);
    print_string("GUESS THE NUMBER GAME", THEME_ACCENT, (7 * SCREEN_WIDTH + 29) * 2);
    
    int target = get_random(1, 100);
    int attempts = 0;
    
    print_string("I'm thinking of a number (1-100)", THEME_TEXT, (9 * SCREEN_WIDTH + 24) * 2);
    
    while (attempts < 7) {
        print_string("Your guess: ", THEME_TEXT, (11 + attempts * 2) * SCREEN_WIDTH * 2 + 24 * 2);
        
        char guess_str[4] = {0};
        int idx = 0;
        
        while (1) {
            char key = read_key();
            if (key == '\r') break;
            if (key >= '0' && key <= '9' && idx < 3) {
                guess_str[idx++] = key;
                print_char(key, THEME_TEXT, ((11 + attempts * 2) * SCREEN_WIDTH + 36 + idx - 1) * 2);
            } else if (key == 8 && idx > 0) {
                idx--;
                print_char(' ', THEME_TEXT, ((11 + attempts * 2) * SCREEN_WIDTH + 36 + idx) * 2);
            }
        }
        
        int guess = string_to_int(guess_str);
        attempts++;
        
        if (guess == target) {
            print_string("Correct! You won!", THEME_LIGHT_GREEN, (19 * SCREEN_WIDTH + 31) * 2);
            beep(1500, 200);
            break;
        } else if (guess < target) {
            print_string("Too low!", THEME_LIGHT_RED, ((11 + attempts * 2) * SCREEN_WIDTH + 45) * 2);
            beep(400, 100);
        } else {
            print_string("Too high!", THEME_LIGHT_RED, ((11 + attempts * 2) * SCREEN_WIDTH + 45) * 2);
            beep(400, 100);
        }
        
        if (attempts == 7) {
            print_string("Game Over! Number was: ", THEME_LIGHT_RED, (19 * SCREEN_WIDTH + 24) * 2);
            char target_str[4];
            int_to_string(target, target_str);
            print_string(target_str, THEME_YELLOW, (19 * SCREEN_WIDTH + 47) * 2);
            beep(300, 500);
        }
    }
    
    print_string("Press any key...", THEME_TEXT, (21 * SCREEN_WIDTH + 32) * 2);
    read_key();
}

void show_about() {
    clear_screen();
    draw_box(15, 5, 50, 14, THEME_PRIMARY);
    print_string("ABOUT CUSTOM OS", THEME_ACCENT, (6 * SCREEN_WIDTH + 32) * 2);
    
    print_string("Custom Operating System v2.0", THEME_TEXT, (8 * SCREEN_WIDTH + 26) * 2);
    print_string("Enhanced Prototype Edition", THEME_TEXT, (9 * SCREEN_WIDTH + 27) * 2);
    
    print_string("Built with:", THEME_SECONDARY, (11 * SCREEN_WIDTH + 20) * 2);
    print_string("- x86 Assembly (NASM)", THEME_TEXT, (12 * SCREEN_WIDTH + 22) * 2);
    print_string("- C++ (Freestanding)", THEME_TEXT, (13 * SCREEN_WIDTH + 22) * 2);
    print_string("- Love and Coffee", THEME_TEXT, (14 * SCREEN_WIDTH + 22) * 2);
    
    print_string("Features: 7 Applications", THEME_LIGHT_GREEN, (16 * SCREEN_WIDTH + 28) * 2);
    
    print_string("Press any key...", THEME_TEXT, (18 * SCREEN_WIDTH + 32) * 2);
    read_key();
    beep(800, 100);
}

void handle_input() {
    while (1) {
        clear_screen();
        
        print_string("CUSTOM OS v2.0 - Enhanced Edition", THEME_ACCENT, (1 * SCREEN_WIDTH + 23) * 2);
        
        show_menu();
        
        char choice = read_key();
        
        beep(1000, 50);
        
        if (choice == '1') {
            text_editor();
        } else if (choice == '2') {
            calculator();
        } else if (choice == '3') {
            snake_game();
        } else if (choice == '4') {
            clock_display();
        } else if (choice == '5') {
            system_info();
        } else if (choice == '6') {
            color_settings();
        } else if (choice == '7') {
            guess_number_game();
        } else if (choice == '8') {
            show_about();
        } else if (choice == '9') {
            clear_screen();
            draw_box(25, 10, 30, 6, THEME_PRIMARY);
            print_string("Thank you!", THEME_ACCENT, (11 * SCREEN_WIDTH + 35) * 2);
            print_string("System halted safely.", THEME_TEXT, (13 * SCREEN_WIDTH + 29) * 2);
            beep(800, 200);
            break;
        }
    }
}
