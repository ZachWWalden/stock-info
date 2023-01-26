#pragma once
#include "Graphics.hpp"
#include "stdlib.h"
#include <cmath>

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
			this->SetCanvasPixel(cols, rows, ZwGraphics::Color(0xFF, this->render_target[rows][cols][0], this->render_target[rows][cols][1], this->render_target[rows][cols][2]));
		}
	}
}

void Graphics::PlotPoint(uint8_t x, uint8_t y, ZwGraphics::Color color)
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

void Graphics::PlotPoint(ZwGraphics::Point point, ZwGraphics::Color color)
{
	if(point.x >= this->width || point.y >= height || this->render_target == nullptr)
		return;

	//Plot point into this->render_target
	this->render_target[point.y][point.x][0] = color.red;
	this->render_target[point.y][point.x][1] = color.green;
	this->render_target[point.y][point.x][2] = color.blue;

}
void Graphics::PlotLine(ZwGraphics::Point p1,ZwGraphics::Point p2, ZwGraphics::Color color)
{
	int x1,x2,y1,y2;
	x1 = p1.x;
	x2 = p2.x;
	y1 = p1.y;
	y2 = p2.y;

	//Detect Horizontal/Vertical Lines
	if(x1 == x2)
	{
		//Vertical Line
		this->PlotLineVertical(p1, p2, color);
	}
	else if (y1 == y2)
	{
		//Horizontal Line
		this->PlotLineHorizontal(p1, p2, color);
	}
	else
	{
		//Normal Line
		if(std::abs(y2 - y1) < std::abs(x2-x1))
		{
			if(x1 > x2)
			{
				this->PlotLineLow(p2, p1, color);
			}
			else
			{
				this->PlotLineLow(p1, p2, color);
			}
		}
		else
		{
			if(y1 > y2)
			{
				this->PlotLineHigh(p2, p1, color);
			}
			else
			{
			this->PlotLineHigh(p1, p2, color);
			}
		}
	}
}
void Graphics::PlotLineHigh(ZwGraphics::Point p1,ZwGraphics::Point p2, ZwGraphics::Color color)
{
	//All coordinates will be in quadrant 1.
	///Cast to 32-bit signed integers.
	int dx, dy, D, x_inc, x, x1, x2, y1, y2;
	x1 = p1.x;
	x2 = p2.x;
	y1 = p1.y;
	y2 = p2.y;
	dx = x2 - x1;
	dy = y2 - y1;
	x_inc = 1;
	if(dx < 0)
	{
		x_inc = -1;
		dx = -dx;
	}
	D = (dx << 1) - dy;
	x = x1;

	for(int y = y1; y <= y2; y++)
	{
		this->PlotPoint(ZwGraphics::Point(x, y), color);
		if(D > 0)
		{
			x += x_inc;
			D += (dx - dy) << 1;
		}
		else
		{
			D += dx << 1;
		}
	}
}
void Graphics::PlotLineLow(ZwGraphics::Point p1,ZwGraphics::Point p2, ZwGraphics::Color color)
{
	//All coordinates will be in quadrant 1.
	///Cast to 32-bit signed integers.
	int dx, dy, D, y_inc, y, x1, x2, y1, y2;
	x1 = p1.x;
	x2 = p2.x;
	y1 = p1.y;
	y2 = p2.y;
	dx = x2 - x1;
	dy = y2 - y1;
	y_inc = 1;
	if(dy < 0)
	{
		y_inc = -1;
		dy = -dy;
	}
	D = (dy << 1) - dx;
	y = y1;

	for(int x = x1;  x<= x2; x++)
	{
		this->PlotPoint(ZwGraphics::Point(x, y), color);
		if(D > 0)
		{
			y += y_inc;
			D += (dy - dx) << 1;
		}
		else
		{
			D += dy << 1;
		}
	}
}
void Graphics::PlotLineHorizontal(ZwGraphics::Point p1,ZwGraphics::Point p2, ZwGraphics::Color color)
{
	uint8_t x_start, x_end;
	if(p2.x > p1.x)
	{
		x_start = p1.x;
		x_end = p2.x;
	}
	else
	{
		x_start = p2.x;
		x_end = p1.x;
	}

	//Y stays the same for the whole time
	for(uint8_t x = x_start; x <= x_end; x++)
	{
		this->PlotPoint(ZwGraphics::Point(x, p1.y), color);
	}
}
void Graphics::PlotLineVertical(ZwGraphics::Point p1,ZwGraphics::Point p2, ZwGraphics::Color color)
{
	uint8_t y_start, y_end;
	if(p2.y > p1.y)
	{
		y_start = p1.y;
		y_end = p2.y;
	}
	else
	{
		y_start = p2.y;
		y_end = p1.y;
	}

	//X stays the same for the whole time
	for(uint8_t y = y_start; y <= y_end; y++)
	{
		this->PlotPoint(ZwGraphics::Point(p1.x, y), color);
	}
}


void Graphics::PlotRectangle(ZwGraphics::Rectangle rect,ZwGraphics::Color color)
{
	uint8_t dx, dy;
	dx = rect.p_bot_right.x - rect.p_top_left.x;
	dy = rect.p_bot_right.y - rect.p_top_left.y;

	this->PlotLineVertical(rect.p_top_left, ZwGraphics::Point(rect.p_top_left.x, rect.p_top_left.y + dy), color);
	this->PlotLineVertical(ZwGraphics::Point(rect.p_top_left.x + dx,rect.p_bot_right.y),rect.p_bot_right, color);
	this->PlotLineHorizontal(rect.p_top_left, ZwGraphics::Point(rect.p_top_left.x + dx, rect.p_top_left.y), color);
	this->PlotLineHorizontal(ZwGraphics::Point(rect.p_top_left.x,rect.p_bot_right.y + dy),rect.p_bot_right, color);
}
void Graphics::PlotCircle(ZwGraphics::Circle circle, ZwGraphics::Color color)
{
	//only supports circles with odd radii, to support even radii, add 1 to radius, but do not render that midpoint.
	int r, x_mid, y_mid, y, x, err;
	r = circle.radius;
	x_mid = circle.center.x;
	y_mid = circle.center.y;
	x = 0;
	y = r;
	err = 3 - (r << 1);
	//Check for overflow issues
	if(!(x_mid + r < this->getWidth() && x_mid - r >= 0 && y_mid + r < this->getHeight() && y_mid - r >= 0))
		return;
	//Plot the middle points if radius is odd.
	this->PlotPoint(ZwGraphics::Point(x_mid, y_mid + r), color);
	this->PlotPoint(ZwGraphics::Point(x_mid, y_mid - r), color);
	this->PlotPoint(ZwGraphics::Point(x_mid + r, y_mid), color);
	this->PlotPoint(ZwGraphics::Point(x_mid - r, y_mid), color);

	while(y >= x)
	{
		x++;
		if(err > 0)
		{
			err += ((x - y) << 2) + 10;
			y--;
		}
		else
		{
			err += (x << 2) + 6;
		}
		//Plot the points
		this->PlotPoint(ZwGraphics::Point(x_mid + x,y_mid + y), color);
		this->PlotPoint(ZwGraphics::Point(x_mid + x,y_mid - y), color);
		this->PlotPoint(ZwGraphics::Point(x_mid - x,y_mid + y), color);
		this->PlotPoint(ZwGraphics::Point(x_mid - x,y_mid - y), color);
		this->PlotPoint(ZwGraphics::Point(x_mid + y,y_mid + x), color);
		this->PlotPoint(ZwGraphics::Point(x_mid + y,y_mid - x), color);
		this->PlotPoint(ZwGraphics::Point(x_mid - y,y_mid + x), color);
		this->PlotPoint(ZwGraphics::Point(x_mid - y,y_mid - x), color);

	}
}
void Graphics::PlotCircleFilled(ZwGraphics::Circle circle, ZwGraphics::Color color)
{
	//only supports circles with odd radii, to support even radii, add 1 to radius, but do not render that midpoint.
	int r, x_mid, y_mid, y, x, err;
	r = circle.radius;
	x_mid = circle.center.x;
	y_mid = circle.center.y;
	x = 0;
	y = r;
	err = 3 - (r << 1);
	//Check for overflow issues
	if(!(x_mid + r < this->getWidth() && x_mid - r >= 0 && y_mid + r < this->getHeight() && y_mid - r >= 0))
		return;
	//Plot the middle points if radius is odd.
	this->PlotLine(circle.center, ZwGraphics::Point(x_mid, y_mid + r), color);
	this->PlotLine(circle.center, ZwGraphics::Point(x_mid, y_mid - r), color);
	this->PlotLine(circle.center, ZwGraphics::Point(x_mid + r, y_mid), color);
	this->PlotLine(circle.center, ZwGraphics::Point(x_mid - r, y_mid), color);

	while(y >= x)
	{
		x++;
		if(err > 0)
		{
			err += ((x - y) << 2) + 10;
			y--;
		}
		else
		{
			err += (x << 2) + 6;
		}
		//Plot the points
		this->PlotLine(circle.center, ZwGraphics::Point(x_mid + x,y_mid + y), color);
		this->PlotLine(circle.center, ZwGraphics::Point(x_mid + x,y_mid - y), color);
		this->PlotLine(circle.center, ZwGraphics::Point(x_mid - x,y_mid + y), color);
		this->PlotLine(circle.center, ZwGraphics::Point(x_mid - x,y_mid - y), color);
		this->PlotLine(circle.center, ZwGraphics::Point(x_mid + y,y_mid + x), color);
		this->PlotLine(circle.center, ZwGraphics::Point(x_mid + y,y_mid - x), color);
		this->PlotLine(circle.center, ZwGraphics::Point(x_mid - y,y_mid + x), color);
		this->PlotLine(circle.center, ZwGraphics::Point(x_mid - y,y_mid - x), color);

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

void Graphics::SetCanvasPixel(uint8_t x, uint8_t y, ZwGraphics::Color color)
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
