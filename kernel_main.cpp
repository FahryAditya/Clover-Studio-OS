#include "kernel.h"

extern "C" void kernel_main() {
    clear_screen();
    
    print_string("====================================", COLOR_CYAN, SCREEN_WIDTH * 0 * 2 + 22);
    print_string("  WELCOME TO CLOVER OS v2.0", COLOR_YELLOW, SCREEN_WIDTH * 1 * 2 + 26);
    print_string("====================================", COLOR_CYAN, SCREEN_WIDTH * 2 * 2 + 22);
    
    handle_input();
    
    while (1) {
        __asm__ volatile ("hlt");
    }
}
