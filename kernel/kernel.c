#include "stdint.h"
#include "screen.h"

void main();

#define VGA_MEMORY 0xB8000
#define BLACK 0
#define GREEN 2
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25 

void _start() {
    main();
    
    while(1) {
        asm("hlt");
    }
}

void main() {
    // you can return values, but global variables and including other functions from other files doesn't work yet.
    // the warp agent was helpful in fixing my previous errors

    // if you want to get other files to work you need to change how you compile 

    // Have some manner of "CRT" (C run-time) code executes .data initialization to fix global variables

    const uint16_t color = (GREEN << 8) | (BLACK << 12); // first 4 bytes: background, then foreground, then character
    volatile uint16_t* vga = (uint16_t*) VGA_MEMORY;
    // hello_world(5, color, vga);
    // test_asm();

    print_int(12345, 5, color, vga);
    // clear_screen(color, vga);

    // print_char_at_pos('x', 40, 12); // print an x in the middle of the screen 

    // Your bss or data segment is probably set up incorrectly becuase the gloabal variables don't work as intended. 

    // print_char('A');
    // clear_screen();
}

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