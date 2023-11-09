/*
 * menu.c
 *
 * Created: 19.10.2023 15:48:31
 *  Author: karitro
 */ 

#include <util/delay.h>
#include <stdbool.h>
#include "user_input.h"
#include "oled.h"
#include "can_controller.h"
#include <time.h>

long long int score = 0;

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
		Direction joyPos = get_direction(oled);
		switch (joyPos)
		{
			case DOWN:
			if (*selected < 2) {
				*selected = *selected + 1;
			} else {
				*selected = 0;
			}
			_delay_ms(600);
			break;
			case UP:
			if (*selected > 0) {
				*selected = *selected - 1;
			} else {
				*selected = 2;
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
		go_to_pos(0,0);
		oled_print_string("Playing game");
		send_user_input_to_node2();
		oled_screen_clear();
		return;
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
		Direction joyPos = get_direction(oled);
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


void send_user_input_to_node2() {
	time_t currentTime;
	struct tm *timeInfo;
	
	volatile uint8_t* node2 = (uint8_t*)0x13ff;
	while(true) {
		userInput input = get_user_input(node2);
		if (input.right_button_press) {
			return;
		}
		go_to_pos(2,0);
		char str[50];
		snprintf(str, sizeof(str), "SCORE: %d", score);
		oled_print_string(str);
		score++;
		//oled_print_string();
		
		message_type msg = {111, 8, {input.JoyX, input.JoyY, input.rightSlider, input.right_button_press}};
		can_send(&msg);
	}
}