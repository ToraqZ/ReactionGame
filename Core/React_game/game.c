/*
 * game.c
 *
 *  Created on: Feb 20, 2024
 *      Author: anahide
 */

#include "game.h"
#include "max7219.h"

void init_game(MAX7219_Handle_TypeDef *max7219_handle){
	HAL_StatusTypeDef max7219_status = HAL_OK;

	max7219_status = max7219_init(&max7219_handle);
}

