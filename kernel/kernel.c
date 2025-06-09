#include "stdint.h"

#define VGA_MEMORY 0xB8000
#define BLACK 0
#define GREEN 2
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25 

// add this to header file
void print_char(char c);
void clear_screen();
void hello_world();
void print_char_at_pos(char c, int x, int y);

void main() {
    // hello_world(6);

    // implement a cursor tonight 

    print_char_at_pos('x', 40, 12); // print an x in the middle of the screen 

    // Your bss segment is probably set up incorrectly becuase the gloabal variables don't work as intended. 

    // print_char('A');
    // clear_screen();
}

void hello_world(int len) {
    volatile uint16_t* vga = (uint16_t*) VGA_MEMORY;
    const uint16_t color = (GREEN << 8) | (BLACK << 12); // first 4 bytes: background, then foreground, then character
    
    char s[] = "Hello"; // This works it just has to be less than like 10 bytes 
    vga--;

    for(int i = 0; i < len; i++) {
        *vga = s[i] | color;
        vga++;
    }
}

void print_char(char c) {
    volatile uint16_t* vga = (uint16_t*) VGA_MEMORY;
    const uint16_t color = (GREEN << 8) | (BLACK << 12); // first 4 bytes: background, then foreground, then character
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


// Works 
void clear_screen() {
    uint16_t* vga = (uint16_t*) VGA_MEMORY;
    const uint16_t color = (GREEN << 8) | (BLACK << 12); // first 4 bytes: background, then foreground, then character
    
    for (uint16_t i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++) {
            *vga = ' ' | color;
            vga++;
    }
}
