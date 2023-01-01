#pragma once
#include "stdint.h"
#include "../Graphics/Graphics.hpp"

#include "console_font_4x6.hpp"
#include "console_font_5x8.hpp"
#include "console_font_7x9.hpp"
#include "console_font_9x16.hpp"

enum FontStatus
{
	FontOutOfRange, FontSuccess, FontPrintCutoff
};
 struct Font
{
	uint8_t num_rows;
	uint8_t row_size;
	uint8_t width;
	uint8_t tsize;
	uint8_t* font;
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
		~Text();

		FontStatus WriteChar(int x0, int y0, uint8_t letter, Font font, Color color);
		FontStatus WriteString(int x0, int y0, char *string, Font font, Color color);
	private:
};
