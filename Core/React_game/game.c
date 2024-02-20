/*
 * game.c
 *
 *  Created on: Feb 20, 2024
 *      Author: anahide
 */

#include "game.h"

static Game_Handle_TypeDef *game_handle = NULL;

static FSM_Handle_TypeDef *fsm_handle = NULL;

static FSM_State_TypeDef states_list[] = {
		{ STATE_START, &state_start },
		{ STATE_GP, &state_gp },
		{ STATE_WP, &state_wp },
		{ STATE_WAIT, &state_wait },
		{ STATE_DISP, &state_disp },
		{ STATE_STOP, &state_stop }

};

uint8_t LETTERS[26] = { 0b01111101, // A
						0b01111111, // B
						0b00111001, // C
						0b00111111, // D
						0b01111001, // E
						0b01110001, // F
						0b01111011, // G
						0b01110110, // H
						0b00000110, // I
						0b00011110, // J
						0b01110110, // K
						0b00111000, // L
						0b01010100, // M
						0b00010101, // N
						0b00011101, // O
						0b01100111, // P
						0b01100111, // Q
						0b01010000, // R
						0b01101101, // S
						0b01111000, // T
						0b00111110, // U
						0b00111000, // V
						0b01010100, // W
						0b01110110, // X
						0b01101110, // Y
						0b01011011, // Z
						};

int tab_case[5][4]={{1,0,0,0},
		             {0,1,0,0},
					 {0,0,1,0},
					 {0,0,0,1},
					 {1,1,1,1}};

static void set_new_state(FSM_State_Enum _new_state){
	if ((_new_state >= 0) && (_new_state < fsm_handle->states_list_sz)){
		fsm_handle->state = fsm_handle->states_list[_new_state];
	}
}

HAL_StatusTypeDef init_game(Game_Handle_TypeDef *_game_handle, FSM_Handle_TypeDef *_fsm_handle){
	HAL_StatusTypeDef max7219_status = HAL_OK;
	//HAL_StatusTypeDef led_array_status = HAL_OK;

	game_handle = _game_handle;
	fsm_handle = _fsm_handle;

	max7219_status = max7219_init(&game_handle->max7219_handle);

	if (max7219_status != HAL_OK)
		return max7219_status;

	fsm_handle->states_list = states_list;
	fsm_handle->states_list_sz = sizeof(states_list) / sizeof(FSM_State_TypeDef);

	set_new_state(STATE_START);

	return HAL_OK;
}


HAL_StatusTypeDef run_game(void){
	fsm_handle->state.state_callback();

	switch (fsm_handle->state.state){
	case STATE_START:
		break;
	case STATE_WP:
		break;
	case STATE_GP:
		break;
	case STATE_WAIT:
		break;
	case STATE_DISP:
		break;
	case STATE_STOP:
		break;
	}

	return HAL_OK;
}

void state_start(void){

}
void state_wp(void){

}
void state_gp(void){

}
void state_wait(void){

}
void state_disp(void){

}
void state_stop(void){

}

HAL_StatusTypeDef display_letter(MAX7219_Handle_TypeDef max7219_handle, char letter, int pos){
HAL_StatusTypeDef max7219_status;

if(letter >= 'A' && letter <= 'Z'){
	max7219_status = max7219_display_no_decode(pos, LETTERS[letter - 'A']);
}
return max7219_status;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

}

