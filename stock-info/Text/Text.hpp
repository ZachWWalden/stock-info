#pragma once
#include "stdint.h"
#include "../Graphics/Graphics.hpp"

enum FontStatus
{
	FontOutOfRange, FontSuccess, FontPrintCutoff
};
enum Fonts
{
	Font4x6, Font5x8, Font7x9, Font9x16
};
 struct Font
{
	uint8_t num_rows;
	uint8_t row_size;
	uint8_t width;
	uint8_t* font;

	Font(uint8_t rows, uint8_t row_byte_num, uint8_t cols, uint8_t* fontAddr)
	{
		num_rows = rows;
		row_size = row_byte_num;
		width = cols;
		font = fontAddr;
	}
};

class Text
{
	//Attributes
	public:

	private:
		static uint8_t console_font_4x6[];
		static uint8_t console_font_5x8[];
		static uint8_t console_font_7x9[];
		static uint8_t console_font_9x16[];

		Graphics* graphics_mgr;

	//Methods
	public:
		Text();
		Text(Graphics* graphics_mgr);
		~Text();

		FontStatus WriteChar(int x0, int y0, uint8_t letter, Font font, ZwGraphics::Color color);
		FontStatus WriteString(int x0, int y0, char *string, Font font, ZwGraphics::Color color);

		Font fontFactory(Fonts font_name);
	private:

};
