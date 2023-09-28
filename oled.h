#pragma once 

static void write_c(uint8_t data);  
void oled_init(); 
void oled_write_data(); 
void fill_screen();
void oled_screen_clear(); 
void go_to_pos();
void go_to_col();
void go_to_line();
void oled_print_char(char c);
void oled_print_string(char* letters);
void oled_clear_line(uint8_t line);
	

