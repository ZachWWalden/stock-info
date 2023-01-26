#pragma once
#include "stdint.h"
#include "led-matrix.h"
#include "Sprite/Sprite.hpp"

using rgb_matrix::Canvas;

namespace ZwGraphics{
struct Color
{
	uint8_t alpha;
	uint8_t red;
	uint8_t green;
	uint8_t blue;

	Color()
	{

	}
	Color(uint8_t a, uint8_t r, uint8_t g, uint8_t b)
	{
		Color();
		alpha = a;
		red = r;
		green = g;
		blue = b;
	}
	Color invert()
	{
		return Color(alpha, ~red, ~blue, ~green);
	}
};

struct Point
{
	uint8_t x;
	uint8_t y;
	Point()
	{

	}
	Point(uint8_t new_x, uint8_t new_y)
	{
		x = new_x;
		y = new_y;
	}
};


struct Rectangle
{
	Point p_top_left;
	Point p_bot_right;
	Rectangle(Point new_p1, Point new_p2)
	{
		p_top_left = new_p1;
		p_bot_right = new_p2;
	}
};

struct Triangle
{
	Point p1;
	Point p2;
	Point p3;
	Triangle(Point new_p1, Point new_p2, Point new_p3)
	{
		p1 = new_p1;
		p2 = new_p2;
		p3 = new_p3;
	}
};

struct Circle
{
	Point center;
	uint8_t radius;
	Circle(uint8_t new_radius, Point new_center)
	{
		center = new_center;
		radius = new_radius;
	}
};

struct Gradient
{
	Color start;
	Color end;
	Gradient(Color start_color, Color end_color)
	{
		start = start_color;
		end = end_color;
	}
};

}

class Graphics
{
	//attributes
	public:

	private:
		Canvas* canvas;
		uint8_t height;
		uint8_t width;
		uint8_t*** render_target = nullptr;
	//methods
	public:
		Graphics(Canvas* canvas, uint8_t height, uint8_t width);
		~Graphics();

		void draw();

		//void renderSprite(uint8_t x0, uint8_t y0, Sprite sprite);

		void PlotPoint(uint8_t x, uint8_t y, ZwGraphics::Color color);

		void PlotPoint(ZwGraphics::Point point, ZwGraphics::Color color);

		void PlotLine(ZwGraphics::Point p1,ZwGraphics::Point p2, ZwGraphics::Color color);
		void PlotLineHorizontal(ZwGraphics::Point p1,ZwGraphics::Point p2, ZwGraphics::Color color);
		void PlotLineVertical(ZwGraphics::Point p1,ZwGraphics::Point p2, ZwGraphics::Color color);

		void PlotRectangle(ZwGraphics::Rectangle rect,ZwGraphics::Color color);
		void PlotRectangleFilled(ZwGraphics::Rectangle rect,ZwGraphics::Color color);

		void PlotTriangle(ZwGraphics::Triangle, ZwGraphics::Color color);
		void PlotTriangleFilled(ZwGraphics::Triangle, ZwGraphics::Color color);

		void PlotCircle(ZwGraphics::Circle circle, ZwGraphics::Color color);
		void PlotCircleFilled(ZwGraphics::Circle circle, ZwGraphics::Color color);

		void BlendPixels(int y, int x, uint8_t*** buf_one, uint8_t*** buf_two, uint8_t alpha_one, uint8_t alpha_two);
		void BlendBuffers(int v_res, int h_res, uint8_t*** buf_one, uint8_t*** buf_two, uint8_t alpha_one, uint8_t alpha_two);
		void Gradient1D(ZwGraphics::Gradient grad, ZwGraphics::Rectangle rect);
		void Gradient2D(ZwGraphics::Gradient grad_left_right, ZwGraphics::Gradient grad_top_bot, ZwGraphics::Rectangle rect);

		uint8_t getHeight();
		void setHeight(uint8_t height);

		uint8_t getWidth();
		void setWidth(uint8_t width);

		void setRenderTarget(uint8_t*** render_target);
		void clearRenderTarget();
	private:

		void PlotLineHigh(ZwGraphics::Point p1,ZwGraphics::Point p2, ZwGraphics::Color color);
		void PlotLineLow(ZwGraphics::Point p1,ZwGraphics::Point p2, ZwGraphics::Color color);

		void SetCanvasPixel(uint8_t x, uint8_t y, ZwGraphics::Color color);

		bool isPointOnScreen(ZwGraphics::Point pt);

		uint8_t sadd8(uint8_t a, uint8_t b);
};
