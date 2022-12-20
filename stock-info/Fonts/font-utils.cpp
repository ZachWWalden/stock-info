/*******************************************************************************
 * Text drawing functions past this point.                                     *
 *******************************************************************************/
/************************************************
 * WriteChar Function - function plots a single *
 * character.                                   *
 ************************************************/
int WriteChar(int x0, int y0, unsigned char letter, int color, int backcolor){
    int x,y,ySize,xSize;
    unsigned char mask;

    if(letter<0x20||letter>0x7E) // if function is sent a ASCII character it can't print
        return(GDGL_OUTOFRANGE); // return Out of Range error
    letter-=0x20;                // subtract unused ASCII characters so variable
                                 // 'letter' can be used for an arrays value

    for(x=x0;x<(5*tsize)+x0;x+=tsize){           // Please don't try to understand this - just accept it.
        mask=1;                                  // reset mask variable
        for(y=y0;y<(8*tsize)+y0;y=y+tsize){      //
            for(xSize=0;xSize<tsize;xSize++)     //
                for(ySize=0;ySize<tsize;ySize++) //
                    PlotPoint(x+xSize,y+ySize,((Dfont[letter][((x-x0)/tsize)] & mask) ? color:backcolor));
            mask<<=1;                            // shift the mask left 1 bit
        }
    }
    return(GDGL_SUCCESS);
}
/************************************************
 * WriteChar Function - function plots a string *
 ************************************************/
int WriteString(int x0, int y0, char *string, int color, int backcolor){
    int error_code=0;

    while(*string) // will loop until NULL is reached (0x00)
    {
        error_code=WriteChar(x0, y0, *string, color, backcolor); // write the current character to the screen

        if(error_code!=GDGL_SUCCESS) // if WriteChar returns an error
            return(error_code);      // stop and return it to the user

        if(txwrap) {                         // if the user wants the text to wrap:
            if(Scrn_W-(x0+5*tsize)<5*tsize){ // if there is not enough room to print the character on the same line
                y0+=8*tsize;                 // drop the current line down one
                if(Scrn_H-y0<8*tsize)        // if there's not enough room to print the character on the next line
                    return(GDGL_PRNTCUTOFF); // return error
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
    return(GDGL_SUCCESS); // return success code
}
