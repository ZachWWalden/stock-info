#pragma once
#include "text-utils.hpp"
#include "font-4x6.hpp"
#include "font-5x8.hpp"
#include "font-7x9.hpp"
#include "font-9x16.hpp"

/************************************************
 * WriteChar Function - function plots a single *
 * character.                                   *
 ************************************************/
FontStatus WriteChar(int x0, int y0, uint8_t letter, Font font, Color color)
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
FontStatus WriteString(int x0, int y0, char *string, Font font, Color color){
    FontStatus error_code=FontSuccess;
    uint8_t txwrap = 0;

    while(*string) // will loop until NULL is reached (0x00)
    {
        error_code=WriteChar(x0, y0, *string, font, color); // write the current character to the screen

        if(error_code!=FontSuccess) // if WriteChar returns an error
            return(error_code);      // stop and return it to the user

        if(txwrap) {                         // if the user wants the text to wrap:
            if(Scrn_W-(x0+5*tsize)<5*tsize){ // if there is not enough room to print the character on the same line
                y0+=8*tsize;                 // drop the current line down one
                if(Scrn_H-y0<8*tsize)        // if there's not enough room to print the character on the next line
                    return(FontPrintCutoff); // return error
                x0=0;                        // reset x axis
                string++;                    // increment the current character
            }
            else {                                  // else
                x0+=5*tsize;                        // do the regular text stuff
                PlotVLine(x0,y0,7*tsize,backcolor); //
                string++;                           //
                x0++;                               //
            }
        }
        else {                                 // else if the user does not want the text to wrap:
            x0+=5*tsize;                       // increment the x axis to make a spot for the new character
            PlotVLine(x0,y0,7*tsize,backcolor);// plot a blank line between characters
            string++;                          // increment the current character
            x0++;                              // increment x axis to make room for line just plotted
        }
    }
    return(FontSuccess); // return success code
}
