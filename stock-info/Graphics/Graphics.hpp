#pragma once
#include "stdint.h"
#include "led-matrix.h"

using rgb_matrix::Canvas;

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
};

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

		void renderSprite(uint8_t x0, uint8_t y0, Sprite sprite);

		void PlotPoint(uint8_t x, uint8_t y, Color color);
		void BlendPixels(int y, int x, uint8_t*** buf_one, uint8_t*** buf_two, uint8_t alpha_one, uint8_t alpha_two);
		void BlendBuffers(int v_res, int h_res, uint8_t*** buf_one, uint8_t*** buf_two, uint8_t alpha_one, uint8_t alpha_two);

		uint8_t getHeight();
		void setHeight(uint8_t height);

		uint8_t getWidth();
		void setWidth(uint8_t width);

		void setRenderTarget(uint8_t*** render_target);
	private:
		void SetCanvasPixel(uint8_t x, uint8_t y, Color color);
};
