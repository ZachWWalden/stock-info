#pragma once
#include <cstdint>
#include "../Graphics/Graphics.hpp"

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

FontStatus WriteChar(int x0, int y0, unsigned char letter, Font font, Color color);

FontStatus WriteString(int x0, int y0, char *string, int color, Font font, Color color);
