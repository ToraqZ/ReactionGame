/*
 * game.h
 *
 *  Created on: Feb 20, 2024
 *      Author: anahi
 */

#ifndef REACT_GAME_GAME_H_
#define REACT_GAME_GAME_H_

int tab_case[5][4]={{1,0,0,0},
		             {0,1,0,0},
					 {0,0,1,0},
					 {0,0,0,1},
					 {1,1,1,1}};

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

void init_game(MAX7219_Handle_TypeDef *max7219_handle);
#endif /* REACT_GAME_GAME_H_ */
