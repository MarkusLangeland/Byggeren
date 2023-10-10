#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>
#include <util/delay.h>
#include "font.h"
#include "oled.h"

static void write_c(uint8_t command){
	volatile char* command_address = (char*)0x1000;
	command_address[0] = command; 
}

static void write_d(uint8_t data){
	volatile uint8_t* data_address = (uint8_t*) 0x1200;
	data_address[0] = data; 
}

void go_to_line(int line) {
	if (line >= 0 && line <=7) {
		write_c(0xb0+line);	
	} else {
		printf("Invalid line!");
	}
}

void oled_clear_line(uint8_t line) {
	go_to_line(line);
	go_to_col(0);
	for (int j = 0; j <= 127; j++){
		write_d(0);
	}
}



void go_to_col(int col) {
	if (col >= 0 && col <= 127){
		write_c(0x21);
		write_c(col);
		write_c(0xFF);
	}
}



void go_to_pos(int line, int col) {
		go_to_line(line);
		go_to_col(col);
}

void fill_screen(){
	
	//for (int i = 0; i <= 7; i++){
		//write_c(0xb0+i);
		//for (int i = 0; i <= 127; i++){
			//write_d(0x0f);
		//}
	//}
	go_to_pos(0,50);
	//oled_print_char('a'); 
	//oled_clear_line(0);
	
	char test[] = "adasd";
	oled_print_string(test);
}

void oled_init()
{
	write_c(0xae); // display off
	write_c(0xa1); //segment remap
	write_c(0xda); //common pads hardware: alternative
	write_c(0x12);
	write_c(0xc8); //common output scan direction:com63~com0
	write_c(0xa8); //multiplex ration mode:63
	write_c(0x3f);
	write_c(0xd5); //display divide ratio/osc. freq. mode
	write_c(0x80);
	write_c(0x81); //contrast control
	write_c(0x50);
	write_c(0xd9); //set pre-charge period
	write_c(0x21);
	write_c(0x20); //Set Memory Addressing Mode
	write_c(0x02);
	write_c(0xdb); //VCOM deselect level mode
	write_c(0x30);
	write_c(0xad); //master configuration
	write_c(0x00);
	write_c(0xa4); //out follows RAM content
	write_c(0xa6); //set normal display
	write_c(0xaf); // display on
	
	
	write_c(0x20); //Set Memory Addressing Mode
	write_c(0x02);
	oled_screen_clear(); 
}

void oled_print_char(char letter){
	if (letter >= ' ' && letter <= '~'){
		for (int i = 0; i < 5; i++){
			uint8_t c = pgm_read_byte(&(font5[letter - 32][i]));
			write_d(c);
		}
	} 
}

void oled_print_string(char* letters) {
	int i = 0;
	while (letters[i] != '\0') {
		if (letters[i] >= ' ' && letters[i] <= '~'){
			oled_print_char(letters[i]);
		}
		++i;
	}
}

void oled_screen_clear(){
	for (int i = 0; i <= 7; i++){
		write_c(0xb0+i);
		for (int j = 0; j <= 127; j++){
			write_d(0);
		}
	}		
}

void oled_write_data(){
	write_d(0x0f); 
}

