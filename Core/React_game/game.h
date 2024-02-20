/*
 * game.h
 *
 *  Created on: Feb 20, 2024
 *      Author: anahide
 */

#ifndef REACT_GAME_GAME_H_
#define REACT_GAME_GAME_H_

#include "max7219.h"
#include "main.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct {
	//TypeDef_Led_Array led_array;
	MAX7219_Handle_TypeDef max7219_handle;
} Game_Handle_TypeDef;

typedef enum {
	STATE_START = 0, // START
	STATE_WP = 1, // Wait player
	STATE_GP = 2, // Generate pattern
	STATE_WAIT = 3, // Wait
	STATE_DISP = 4, // Display
	STATE_STOP = 5, // Stop & print
} FSM_State_Enum;

typedef enum {
	ANIMATION_RUNNING,
	ANIMATION_ENDED,
} FSM_Animation_Enum;

typedef struct {
	FSM_State_Enum state;
	void (*state_callback) ();
} FSM_State_TypeDef;

typedef struct {
	FSM_State_TypeDef state;
	FSM_State_TypeDef *states_list;
	size_t states_list_sz;
} FSM_Handle_TypeDef;

HAL_StatusTypeDef init_game(Game_Handle_TypeDef *game_handle, FSM_Handle_TypeDef *_fsm_handle);
HAL_StatusTypeDef run_game(void);

void state_start(void);
void state_wp(void);
void state_gp(void);
void state_wait(void);
void state_disp(void);
void state_stop(void);

HAL_StatusTypeDef display_letter(MAX7219_Handle_TypeDef max7219_handle, char letter, int pos);

#endif /* REACT_GAME_GAME_H_ */
