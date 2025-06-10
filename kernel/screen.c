#include "stdint.h"
#include "screen.h"

#define VGA_MEMORY 0xB8000
#define BLACK 0
#define GREEN 2
#define SCREEN_WIDTH 80
#define SCREEN_HEIGHT 25 

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

void clear_screen() {
    uint16_t* vga = (uint16_t*) VGA_MEMORY;
    const uint16_t color = (GREEN << 8) | (BLACK << 12); // first 4 bytes: background, then foreground, then character
    
    for (uint16_t i = 0; i < SCREEN_HEIGHT * SCREEN_WIDTH; i++) {
            *vga = ' ' | color;
            vga++;
    }
}