/*
 * menu.c
 *
 * Created: 19.10.2023 15:48:31
 *  Author: karitro
 */ 

#include <util/delay.h>
#include <stdbool.h>
#include "joystickAndSlider.h"
#include "oled.h"


void menu_init() {
	volatile uint8_t* oled = (uint8_t*)0x13ff;
	int selected = 0;
	while (true) {
		int userinput = menu_main(oled, &selected);
		menu_sub(userinput, oled);
	}

}




int menu_main(uint8_t* oled, int* selected) {
	while (true) {
		Direction joyPos = getDirection(oled);
		switch (joyPos)
		{
			case DOWN:
			if (*selected < 2) {
				*selected = *selected + 1;
			}
			_delay_ms(600);
			break;
			case UP:
			if (*selected > 0) {
				*selected = *selected - 1;
			}
			_delay_ms(600);
			break;
			case RIGHT:
			return *selected;
			break;
			
			case LEFT:
			break;
			default:
			printf("");
			break;
		}
		go_to_pos(0,0);
		oled_print_string("   Play");
		go_to_pos(1,0);
		oled_print_string("   Highscore");
		go_to_pos(2,0);
		oled_print_string("   Settings");
		switch(*selected) {
			case 0:
			go_to_pos(0,0);
			oled_clear_line(0);
			oled_print_string("-> Play");
			break;
			case 1:
			go_to_pos(1,0);
			oled_clear_line(1);
			oled_print_string("-> Highscore");
			break;
			case 2:
			go_to_pos(2,0);
			oled_clear_line(2);
			oled_print_string("-> Settings");
			break;
			default:
			break;
		}
	}
	return -1;
}

void menu_sub(int userInput, uint8_t* oled) {
	switch (userInput) {
		case 0:
		oled_screen_clear();
		oled_print_string("Playing game");
		break;
		case 1:
		oled_screen_clear();
		go_to_pos(0,0);
		oled_print_string("High score: ");
		break;
		case 2:
		oled_screen_clear();
		go_to_pos(0,0);
		oled_print_string("Settings:");
		break;
	}
	while (true) {
		Direction joyPos = getDirection(oled);
		switch (joyPos)
		{
			case LEFT:
			oled_screen_clear();
			return;
			_delay_ms(600);
			break;
			//case UP:
			//if (selected > 0) {
			//selected = selected - 1;
			//}
			//_delay_ms(600);
			//break;
			//case RIGHT:
			//return selected;
			//break;
			//
			//case LEFT:
			//break;
			default:
			printf("");
			break;
		}
	}
}