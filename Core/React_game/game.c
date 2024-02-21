/*
 * game.c
 *
 *  Created on: Feb 20, 2024
 *      Author: anahide
 */

#include "game.h"

static Game_Handle_TypeDef *game_handle = NULL;

static FSM_Handle_TypeDef *fsm_handle = NULL;

static FSM_State_TypeDef states_list[] = { { STATE_START, &state_start }, {
		STATE_WP, &state_wp }, { STATE_GP, &state_gp }, { STATE_WAIT,
		&state_wait }, { STATE_DISP, &state_disp },
		{ STATE_LOOSE, &state_loose }, };

uint8_t checkP1 = 0;
uint8_t checkP2 = 0;
uint8_t checkP3 = 0;
uint8_t checkP4 = 0;

uint8_t actualBTN1;
uint8_t actualBTN2;
uint8_t actualBTN3;
uint8_t actualBTN4;

uint8_t LETTERS[26] = { 0b01110111, // A
		0b01111111, // B
		0b01001110, // C
		0b00111101, // D
		0b01001111, // E
		0b01000111, // F
		0b01111011, // G
		0b00110111, // H
		0b00110000, // I
		0b00111000, // J
		0b00110111, // K
		0b00001110, // L
		0b01110110, // M
		0b00010101, // N
		0b01111110, // O
		0b01100111, // P
		0b01110011, // Q
		0b00000101, // R
		0b01011011, // S
		0b00001111, // T
		0b00111110, // U
		0b00111110, // V
		0b01010100, // W
		0b01110110, // X
		0b01101110, // Y
		0b01011011, // Z
		};

int tab_case[5][4] = { { 1, 0, 0, 0 }, { 0, 1, 0, 0 }, { 0, 0, 1, 0 }, { 0, 0,
		0, 1 }, { 1, 1, 1, 1 } };

static void set_new_state(FSM_State_Enum _new_state) {
	if ((_new_state >= 0) && (_new_state < fsm_handle->states_list_sz)) {
		fsm_handle->state = fsm_handle->states_list[_new_state];

		fsm_handle->controllers.state_execution_count = 0;
		fsm_handle->controllers.animation_state = ANIMATION_RUNNING;
		fsm_handle->controllers.state_base_time = HAL_GetTick();

		actualBTN1 = fsm_handle->inputs.nb_press_btn1;
		actualBTN2 = fsm_handle->inputs.nb_press_btn2;
		actualBTN3 = fsm_handle->inputs.nb_press_btn3;
		actualBTN4 = fsm_handle->inputs.nb_press_btn4;

		srand(HAL_GetTick());

		fsm_handle->controllers.randomTime = (rand() % 4501) + 500;
		fsm_handle->controllers.randomCase = rand() % 5;
	}
	max7219_erase_no_decode();
}

HAL_StatusTypeDef init_game(Game_Handle_TypeDef *_game_handle,
		FSM_Handle_TypeDef *_fsm_handle) {
	HAL_StatusTypeDef max7219_status = HAL_OK;
	//HAL_StatusTypeDef led_array_status = HAL_OK;

	game_handle = _game_handle;
	fsm_handle = _fsm_handle;

	max7219_status = max7219_init(&game_handle->max7219_handle);

	if (max7219_status != HAL_OK)
		return max7219_status;

	fsm_handle->states_list = states_list;
	fsm_handle->states_list_sz = sizeof(states_list)
			/ sizeof(FSM_State_TypeDef);

	fsm_handle->controllers.randomTime = 0;
	fsm_handle->controllers.randomCase = 0;

	set_new_state(STATE_START);

	return HAL_OK;
}

HAL_StatusTypeDef run_game(void) {
	fsm_handle->state.state_callback();
	fsm_handle->controllers.state_execution_count += 1;

	switch (fsm_handle->state.state) {
	case STATE_START:
		if (fsm_handle->controllers.animation_state == ANIMATION_ENDED) {
			set_new_state(STATE_WP);
		}
		break;
	case STATE_WP:
		checkP1 = fsm_handle->inputs.nb_press_btn1 - actualBTN1;
		checkP2 = fsm_handle->inputs.nb_press_btn2 - actualBTN2;
		checkP3 = fsm_handle->inputs.nb_press_btn3 - actualBTN3;
		checkP4 = fsm_handle->inputs.nb_press_btn4 - actualBTN4;
		if (checkP1 != 0 || checkP2 != 0 || checkP3 != 0 || checkP4 != 0) {
			set_new_state(STATE_WAIT);
		}

		break;
	case STATE_GP:
		if (HAL_GetTick() - fsm_handle->controllers.state_base_time <= 10000) {
			switch (fsm_handle->controllers.randomCase) {
			case 0:
				checkP1 = fsm_handle->inputs.nb_press_btn1 - actualBTN1;
				if (checkP1 != 0) {
					fsm_handle->controllers.timing = (HAL_GetTick()
							- fsm_handle->controllers.state_base_time);
					set_new_state(STATE_DISP);
				}
				break;
			case 1:
				checkP2 = fsm_handle->inputs.nb_press_btn2 - actualBTN2;
				if (checkP2 != 0) {
					fsm_handle->controllers.timing = (HAL_GetTick()
							- fsm_handle->controllers.state_base_time);
					set_new_state(STATE_DISP);
				}
				break;
			case 2:
				checkP3 = fsm_handle->inputs.nb_press_btn3 - actualBTN3;
				if (checkP3 != 0) {
					fsm_handle->controllers.timing = (HAL_GetTick()
							- fsm_handle->controllers.state_base_time);
					set_new_state(STATE_DISP);
				}
				break;
			case 3:
				checkP4 = fsm_handle->inputs.nb_press_btn4 - actualBTN4;
				if (checkP4 != 0) {
					fsm_handle->controllers.timing = (HAL_GetTick()
							- fsm_handle->controllers.state_base_time);
					set_new_state(STATE_DISP);
				}
				break;

			case 4:
				checkP1 = fsm_handle->inputs.nb_press_btn1 - actualBTN1;
				checkP2 = fsm_handle->inputs.nb_press_btn2 - actualBTN2;
				checkP3 = fsm_handle->inputs.nb_press_btn3 - actualBTN3;
				checkP4 = fsm_handle->inputs.nb_press_btn4 - actualBTN4;
				if (checkP1 != 0 && checkP2 != 0 && checkP3 != 0
						&& checkP4 != 0) {
					fsm_handle->controllers.timing = (HAL_GetTick()
							- fsm_handle->controllers.state_base_time);
					set_new_state(STATE_DISP);
				}
				break;
			}
		} else {
			set_new_state(STATE_LOOSE);
		}
		break;
	case STATE_DISP:
		if (fsm_handle->controllers.animation_state == ANIMATION_ENDED) {
			set_new_state(STATE_WP);
		}
		break;
	case STATE_WAIT:
		if (fsm_handle->controllers.animation_state == ANIMATION_ENDED) {
			set_new_state(STATE_GP);
		}
		break;
	case STATE_LOOSE:
		if (fsm_handle->controllers.animation_state == ANIMATION_ENDED) {
			set_new_state(STATE_WP);
		}
		break;
	}

	return HAL_OK;
}

void state_start(void) {
	HAL_StatusTypeDef max7219_status;

	//Affichage
	max7219_status = display_letter(game_handle->max7219_handle, 'G', 0);
	if (max7219_status != HAL_OK)
		Error_Handler();
	max7219_status = display_letter(game_handle->max7219_handle, 'A', 1);
	if (max7219_status != HAL_OK)
		Error_Handler();
	max7219_status = display_letter(game_handle->max7219_handle, 'M', 2);
	if (max7219_status != HAL_OK)
		Error_Handler();
	max7219_status = display_letter(game_handle->max7219_handle, 'E', 3);
	if (max7219_status != HAL_OK)
		Error_Handler();

	//Ellapsed time
	if (HAL_GetTick() - fsm_handle->controllers.state_base_time >= 3000) {
		fsm_handle->controllers.animation_state = ANIMATION_ENDED;
	}

}
void state_wp(void) {
	HAL_StatusTypeDef max7219_status;

	max7219_status = display_letter(game_handle->max7219_handle, 'P', 0);
	if (max7219_status != HAL_OK)
		Error_Handler();
	max7219_status = display_letter(game_handle->max7219_handle, 'R', 1);
	if (max7219_status != HAL_OK)
		Error_Handler();
	max7219_status = display_letter(game_handle->max7219_handle, 'E', 2);
	if (max7219_status != HAL_OK)
		Error_Handler();
	max7219_status = display_letter(game_handle->max7219_handle, 'S', 3);
	if (max7219_status != HAL_OK)
		Error_Handler();

}
void state_gp(void) {

	HAL_StatusTypeDef max7219_status;
	switch (fsm_handle->controllers.randomCase) {
	case 0:
		max7219_status = max7219_display_no_decode(0, 0b00110000);
		if (max7219_status != HAL_OK)
			Error_Handler();
		break;
	case 1:
		max7219_status = max7219_display_no_decode(1, 0b01101101);
		if (max7219_status != HAL_OK)
			Error_Handler();
		break;
	case 2:
		max7219_status = max7219_display_no_decode(2, 0b01111001);
		if (max7219_status != HAL_OK)
			Error_Handler();
		break;
	case 3:
		max7219_status = max7219_display_no_decode(3, 0b00110011);
		if (max7219_status != HAL_OK)
			Error_Handler();
		break;

	case 4:
		max7219_status = max7219_display_no_decode(0, 0b00110000);
		if (max7219_status != HAL_OK)
			Error_Handler();
		max7219_status = max7219_display_no_decode(1, 0b01101101);
		if (max7219_status != HAL_OK)
			Error_Handler();
		max7219_status = max7219_display_no_decode(2, 0b01111001);
		if (max7219_status != HAL_OK)
			Error_Handler();
		max7219_status = max7219_display_no_decode(3, 0b00110011);
		if (max7219_status != HAL_OK)
			Error_Handler();
		break;
	}
}

void state_disp(void) {
	HAL_StatusTypeDef max7219_status;
	int mil, cent, diz, ent;

	mil = fsm_handle->controllers.timing / 1000;
	cent = (fsm_handle->controllers.timing / 100) % 10;
	diz = (fsm_handle->controllers.timing / 10) % 10;
	ent = fsm_handle->controllers.timing % 10;

	max7219_status = max7219_display_decode(0, mil);
	if (max7219_status != HAL_OK)
		Error_Handler();
	max7219_status = max7219_display_decode(1, cent);
	if (max7219_status != HAL_OK)
		Error_Handler();
	max7219_status = max7219_display_decode(2, diz);
	if (max7219_status != HAL_OK)
		Error_Handler();
	max7219_status = max7219_display_decode(3, ent);
	if (max7219_status != HAL_OK)
		Error_Handler();

	if (HAL_GetTick() - fsm_handle->controllers.state_base_time >= 3000) {
		fsm_handle->controllers.animation_state = ANIMATION_ENDED;
	}
}

void state_wait(void) {
	while ((HAL_GetTick() - fsm_handle->controllers.state_base_time)
			< fsm_handle->controllers.randomTime)
		;
	fsm_handle->controllers.animation_state = ANIMATION_ENDED;
}

void state_loose(void) {
	HAL_StatusTypeDef max7219_status;

	while ((HAL_GetTick() - fsm_handle->controllers.state_base_time) < 3000) {
		max7219_status = display_letter(game_handle->max7219_handle, 'L', 0);
		if (max7219_status != HAL_OK)
			Error_Handler();
		max7219_status = display_letter(game_handle->max7219_handle, 'O', 1);
		if (max7219_status != HAL_OK)
			Error_Handler();
		max7219_status = display_letter(game_handle->max7219_handle, 'O', 2);
		if (max7219_status != HAL_OK)
			Error_Handler();
		max7219_status = display_letter(game_handle->max7219_handle, 'S', 3);
		if (max7219_status != HAL_OK)
			Error_Handler();
	}

	fsm_handle->controllers.animation_state = ANIMATION_ENDED;
}

HAL_StatusTypeDef display_letter(MAX7219_Handle_TypeDef max7219_handle,char letter, int pos) {

	HAL_StatusTypeDef max7219_status;

	if (letter >= 'A' && letter <= 'Z') {
		max7219_status = max7219_display_no_decode(pos, LETTERS[letter - 'A']);
	}
	return max7219_status;
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {

	switch (GPIO_Pin) {
	case BTN1_Pin:
		fsm_handle->inputs.nb_press_btn1++;
		break;
	case BTN2_Pin:
		fsm_handle->inputs.nb_press_btn2++;
		break;
	case BTN3_Pin:
		fsm_handle->inputs.nb_press_btn3++;
		break;
	case BTN4_Pin:
		fsm_handle->inputs.nb_press_btn4++;
		break;
	}

}

