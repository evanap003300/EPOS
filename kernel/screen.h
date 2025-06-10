#ifndef SCREEN_H
#define SCREEN_H

void print_char(char c);
void clear_screen(uint16_t color, uint16_t* vga);
void hello_world(int len, uint16_t color, uint16_t* vga);
void print_char_at_pos(char c, int x, int y);

#endif