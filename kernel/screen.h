#ifndef SCREEN_H
#define SCREEN_H

void print_char(char c);
void clear_screen(uint16_t color, uint16_t* vga);
void hello_world(int len, uint16_t color, uint16_t* vga);
void print_char_at_pos(char c, int x, int y);
void test_asm();
void print_int(uint16_t num, uint16_t digits, uint16_t color, uint16_t* vga);
uint16_t number_of_digits(uint16_t n);
void print_E(uint16_t color, uint16_t* vga);
void print_P(uint16_t color, uint16_t* vga);
void print_O(uint16_t color, uint16_t* vga);
void print_S(uint16_t color, uint16_t* vga);
void print_intro(uint16_t color, uint16_t* vga);
void print_logo(uint16_t color, uint16_t* vga);

#endif
