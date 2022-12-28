#pragma once
#include "Graphics.hpp"

Graphics::Graphics(Canvas* canvas, uint8_t height, uint8_t width)
{
		this->canvas = canvas;
		this->height = height;
		this->width = width;
}

void Graphics::draw(uint8_t*** buffer)
{
	for(int rows = 0; rows < this->height; rows++)
	{
		for(int cols = 0; cols < this->width; cols++)
		{
			this->SetCanvasPixel(cols, rows, Color(0xFF, buffer[rows][cols][0], buffer[rows][cols][1], buffer[rows][cols][2]));
		}
	}
}

void Graphics::PlotPoint(uint8_t x, uint8_t y, Color color, uint8_t*** buffer)
{
	if(x >= this->width || y >= height || buffer == nullptr)
		return;

	//Plot point into buffer
	buffer[y][x][0] = color.red;
	buffer[y][x][1] = color.green;
	buffer[y][x][2] = color.blue;
}

void Graphics::BlendPixels(int y, int x, uint8_t*** result, uint8_t*** buf_one, uint8_t*** buf_two, uint8_t alpha_one, uint8_t alpha_two)
{
	result[y][x][0] = ((((uint16_t)buf_one[y][x][0] * alpha_one)/255) + ((uint16_t)buf_two[y][x][0] * alpha_two)/255);
	result[y][x][1] = ((((uint16_t)buf_one[y][x][1] * alpha_one)/255) + ((uint16_t)buf_two[y][x][1] * alpha_two)/255);
	result[y][x][2] = ((((uint16_t)buf_one[y][x][2] * alpha_one)/255) + ((uint16_t)buf_two[y][x][2] * alpha_two)/255);
}
void Graphics::BlendBuffers(int v_res, int h_res, uint8_t*** result, uint8_t*** buf_one, uint8_t*** buf_two, uint8_t alpha_one, uint8_t alpha_two)
{
	for(int rows = 0; rows < v_res; rows++)
	{
		for(int cols = 0; cols < h_res; cols++)
		{
			BlendPixels(rows, cols, result, buf_one, buf_two, alpha_one, alpha_two);
		}
	}
}

uint8_t Graphics::getHeight()
{
	return this->height;
}
void Graphics::setHeight(uint8_t height)
{
	this->height = height;
}
uint8_t Graphics::getWidth()
{
	return this->width;
}
void Graphics::setWidth(uint8_t width)
{
	this->width = width;
}

void Graphics::SetCanvasPixel(uint8_t x, uint8_t y, Color color)
{
	this->canvas->SetPixel(x, y, color.red, color.blue, color.green);
}
