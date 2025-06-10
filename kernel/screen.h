#ifndef SCREEN_H
#define SCREEN_H

void print_char(char c);
void clear_screen(uint16_t color, uint16_t* vga);
void hello_world(int len, uint16_t color, uint16_t* vga);
void print_char_at_pos(char c, int x, int y);
void test_asm();
void print_int(uint16_t num, uint16_t digits, uint16_t color, uint16_t* vga);

#endif