#pragma once
#include "Text.hpp"

/************************************************
 * WriteChar Function - function plots a single *
 * character.                                   *
 ************************************************/
FontStatus Text::WriteChar(int x0, int y0, uint8_t letter, Font font, Color color)
{
	//Check if the character is off of the screen
	if(x0 > (this-graphics_mgr->getWidth() - font.width) || y0 > (this->graphics_mgr->getHeight() - font.num_rows))
	{
		return FontPrintCutoff;
	}
	//from width and row num, find initial shift value.
	uint8_t shift_val = (font.row_size * 8) - font.width;
	//set initial x value
	uint8_t x = x0 + (font.width - 1);
	//row byte loop
	for(int row_byte = font.row_size; row_byte >= 0; row_byte--)
	{
		//loop through each mask value
		while(shift_val < 8)
		{
			//Draw column
			for(uint8_t y = y0; y < font.num_rows;y++)
			{
				if(((font.font[letter + row_byte + ((y - y0) * font.row_size)] >> shift_val) & 0x01) == 0x01)
				{
					this->graphics_mgr->PlotPoint(x,y,color);
				}
			}
			shift_val++;
			x--;
		}
		shift_val = 0;
	}
	return FontSuccess;
}
/************************************************
 * WriteString Function - function plots a string *
 ************************************************/
FontStatus Text::WriteString(int x0, int y0, char *string, Font font, Color color){
    FontStatus error_code=FontSuccess;
    uint8_t txwrap = 0;

    while(*string) // will loop until NULL is reached (0x00)
    {
        error_code=WriteChar(x0, y0, *string, font, color); // write the current character to the screen

        if(error_code!=FontSuccess) // if WriteChar returns an error
            return(error_code);      // stop and return it to the user

        x0 += font.width;                       // increment the x axis to make a spot for the new character
        //PlotVLine(x0,y0,7*tsize,backcolor);// plot a blank line between characters
        string++;                          // increment the current character
        x0++;                              // increment x axis to make room for line just plotted
    }
    return(FontSuccess); // return success code
}