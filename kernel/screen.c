#include "stdint.h"
#include "screen.h"

#define VGA_MEMORY 0xB8000
#define BLACK 0
#define GREEN 2
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25 

void hello_world(int len, uint16_t color, uint16_t* vga) {
    char s[] = "Hello"; // This works it just has to be less than like 10 bytes 
    for(int i = 0; i < len; i++) {
        vga[i] = s[i] | color;
    }
}

void print_char(char c) {
    volatile uint16_t* vga = (uint16_t*) VGA_MEMORY;
    const uint16_t color = (GREEN << 8) | (BLACK << 12); // first 4 bytes: backgroun.ld -o bin/kernel.bin build/kernel.o build/myasm.o --oformat bina, then foreground, then character
    *vga = c | color;
}

void print_char_at_pos(char c, int x, int y) {
    volatile uint16_t* vga = (uint16_t*) VGA_MEMORY;
    const uint16_t color = (GREEN << 8) | (BLACK << 12); // first 4 bytes: background, then foreground, then character
    for (int i = 0; i < y * SCREEN_WIDTH + x; i++) {
        vga++;
    }
    *vga = c | color; 
}

void clear_screen(uint16_t color, uint16_t* vga) {
    for (uint16_t i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++) {
            vga[i] = ' ' | color;
    }
}

void test_asm() {
    uint32_t a = 7;
    uint32_t b = 2;
    uint32_t result;

    asm volatile (
        "addl %%ebx, %%eax;"
        : "=a" (result)
        : "a" (a), "b" (b)
    );

    if (result < 10)
        print_char('0' + result);  // Should print '8'
    else
        print_char('?');  // Error case
}

// works up to 5 digits
void print_int(uint16_t num, uint16_t digits, uint16_t color, uint16_t* vga) {
    int digit = 0;
    int ten_pow = 1;
    int copy = num;

    for(int i = 0; i < digits - 1; i++) {
        ten_pow *= 10;
    }

    int i = 0;
  
    while(copy > 0) {
         digit = (num / ten_pow) % 10;
         vga[i] = ('0' + digit) | color;
         i++;
         ten_pow /= 10;
         copy /= 10;
     }
}

uint16_t number_of_digits(uint16_t n) {
    int count = 0;

    while(n > 0) {
        count++;
        n/=10;
    }
    return count;
}

void print_E(uint16_t color, uint16_t* vga) {
    char line_1[] = " ______ ____   ___   ____";

    for(int i = 0; i < 28; i++) {
        vga[i] = line_1[i] | color;
    }

    for(int i = 1; i <= 5; i++) {
        print_char_at_pos('|', 0, i);
        print_char_at_pos('|', 7, i);
    }
    for(int i = 3; i <= 6; i++) {
        print_char_at_pos('_', i, 1);
    }
    print_char_at_pos('|', 2, 2);

    print_char_at_pos('_', 3, 2);
    print_char_at_pos('_', 4, 2);

    print_char_at_pos('|', 5, 3);

    print_char_at_pos('_', 3, 3);
    print_char_at_pos('_', 4, 3);

    print_char_at_pos('|', 2, 4);

    print_char_at_pos('_', 3, 4);
    print_char_at_pos('_', 4, 4);
    print_char_at_pos('_', 5, 4);
    print_char_at_pos('_', 6, 4);

    for(int i = 1; i <= 6; i++) {
        print_char_at_pos('_', i, 5);
    }
}

void print_P(uint16_t color, uint16_t* vga) {
    print_char_at_pos('_', 8, 5);

    print_char_at_pos('|', 9, 5);
    print_char_at_pos('|', 9, 4);

    print_char_at_pos('_', 10, 3);
    print_char_at_pos('_', 11, 3);
    print_char_at_pos('/', 12, 3);
    
    print_char_at_pos('|', 13, 2);

    print_char_at_pos('\\', 12, 1);

    print_char_at_pos('|', 9, 2);
    print_char_at_pos(')', 11, 2);

    print_char_at_pos('_', 10, 1);
    print_char_at_pos('_', 10, 2);
}

void print_O(uint16_t color, uint16_t* vga) {
    print_char_at_pos('/', 14, 1);
    print_char_at_pos('|', 13, 3);
    print_char_at_pos('|', 13, 4);
    print_char_at_pos('\\', 14, 5);

    print_char_at_pos('_', 15, 5);
    print_char_at_pos('_', 16, 5);
    print_char_at_pos('_', 17, 5);

    print_char_at_pos('/', 18, 5);
    print_char_at_pos('|', 19, 4);
    print_char_at_pos('|', 19, 3);
    print_char_at_pos('|', 19, 2);
    print_char_at_pos('\\', 18, 1);

    print_char_at_pos('_', 16, 4);
    print_char_at_pos('|', 17, 4);
    print_char_at_pos('|', 17, 3);
    print_char_at_pos('|', 17, 2);
    print_char_at_pos('_', 16, 1);
    print_char_at_pos('|', 15, 2);
    print_char_at_pos('|', 15, 3);
    print_char_at_pos('|', 15, 4);
}

void print_S(uint16_t color, uint16_t* vga) {
    print_char_at_pos('/', 20, 1);
    print_char_at_pos('\\', 20, 2);

    print_char_at_pos('_', 21, 2);
    print_char_at_pos('_', 22, 2);
    print_char_at_pos('_', 23, 2);

    print_char_at_pos('\\', 24, 3);
    print_char_at_pos('/', 24, 4);

    print_char_at_pos('_', 20, 4);
    print_char_at_pos('_', 21, 4);
    print_char_at_pos('_', 22, 4);
    print_char_at_pos('_', 23, 4);
    print_char_at_pos('|', 19, 5);

    print_char_at_pos('_', 20, 5);
    print_char_at_pos('_', 21, 5);
    print_char_at_pos('_', 22, 5);
    print_char_at_pos('_', 23, 5);
    print_char_at_pos('_', 24, 5);
    print_char_at_pos('/', 25, 5);

    print_char_at_pos('|', 26, 4);
    print_char_at_pos('\\', 26, 3);
    //print_char_at_pos('|', 26, 2);
    print_char_at_pos('\\', 26, 1);

    print_char_at_pos('_', 22, 1);
    print_char_at_pos('_', 23, 1);
    print_char_at_pos('_', 24, 1);
    print_char_at_pos('_', 25, 1);
}

void print_intro(uint16_t color, uint16_t* vga) {
    char version[] = "EPOS v0.1";

    for (int i = 0; i < 10; i++) {
        print_char_at_pos(version[i], i, 7);
    }
}

void print_logo(uint16_t color, uint16_t* vga) {
    print_E(color, vga);
    print_P(color, vga);
    print_O(color, vga);
    print_S(color, vga);

    print_intro(color, vga);
}
