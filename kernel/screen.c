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