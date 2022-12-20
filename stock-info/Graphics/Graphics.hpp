#pragma once
#include "stdint.hpp"

void BlendPixels(int y, int x, uint8_t* result, uint8_t* buf_one, uint8_t* buf_two, uint8_t alpha_one, uint8_t alpha_two)
{
	result[y][x][0] = ((((uint16_t)buf_one[y][x][0] * alpha_one)/255) + ((uint16_t)buf_two[y][x][0] * alpha_two)/255);
	result[y][x][1] = ((((uint16_t)buf_one[y][x][1] * alpha_one)/255) + ((uint16_t)buf_two[y][x][1] * alpha_two)/255);
	result[y][x][2] = ((((uint16_t)buf_one[y][x][2] * alpha_one)/255) + ((uint16_t)buf_two[y][x][2] * alpha_two)/255);
}
void BlendBuffers(int v_res, int h_res, uint8_t* result, uint8_t* buf_one, uint8_t* buf_two, uint8_t alpha_one, uint8_t alpha_two)
{
	for(int rows = 0; rows < v_res; rows++)
	{
		for(int cols = 0; cols < h_res; cols++)
		{
			BlendPixels(rows, cols, result, buf_one, buf_two, alpha_one, alpha_two);
		}
	}
}
