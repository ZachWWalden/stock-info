#pragma once
#include "Graphics.hpp"

Graphics::Graphics(Canvas* canvas, uint8_t height, uint8_t width)
{
		this->canvas = canvas;
		this->height = height;
		this->width = width;
}
Graphics::~Graphics()
{

}

void Graphics::draw()
{
	for(int rows = 0; rows < this->height; rows++)
	{
		for(int cols = 0; cols < this->width; cols++)
		{
			this->SetCanvasPixel(cols, rows, Color(0xFF, this->render_target[rows][cols][0], this->render_target[rows][cols][1], this->render_target[rows][cols][2]));
		}
	}
}

void Graphics::PlotPoint(uint8_t x, uint8_t y, Color color)
{
	if(x >= this->width || y >= height || this->render_target == nullptr)
		return;

	//Plot point into this->render_target
	this->render_target[y][x][0] = color.red;
	this->render_target[y][x][1] = color.green;
	this->render_target[y][x][2] = color.blue;
}

void Graphics::BlendPixels(int y, int x, uint8_t*** buf_one, uint8_t*** buf_two, uint8_t alpha_one, uint8_t alpha_two)
{
	this->render_target[y][x][0] = ((((uint16_t)buf_one[y][x][0] * alpha_one)/255) + ((uint16_t)buf_two[y][x][0] * alpha_two)/255);
	this->render_target[y][x][1] = ((((uint16_t)buf_one[y][x][1] * alpha_one)/255) + ((uint16_t)buf_two[y][x][1] * alpha_two)/255);
	this->render_target[y][x][2] = ((((uint16_t)buf_one[y][x][2] * alpha_one)/255) + ((uint16_t)buf_two[y][x][2] * alpha_two)/255);
}
void Graphics::BlendBuffers(int v_res, int h_res, uint8_t*** buf_one, uint8_t*** buf_two, uint8_t alpha_one, uint8_t alpha_two)
{
	if(buf_one == nullptr || buf_two == nullptr)
	{
		return;
	}
	for(int rows = 0; rows < v_res; rows++)
	{
		for(int cols = 0; cols < h_res; cols++)
		{
			BlendPixels(rows, cols, buf_one, buf_two, alpha_one, alpha_two);
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

void Graphics::setRenderTarget(uint8_t*** render_target)
{
	if(render_target == nullptr)
	{
		return;
	}

	this->render_target = render_target;
}

void Graphics::clearRenderTarget()
{
	for(int y = 0; y < this->getHeight(); y++)
	{
		for(int x = 0; x < this->getWidth(); x++)
		{
			this->render_target[y][x][0] = 0;
			this->render_target[y][x][1] = 0;
			this->render_target[y][x][2] = 0;
		}
	}
}
