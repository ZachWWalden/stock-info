/*==================================================================================
 *Class - Simple as possible BitMap
 *Author - Zach Walden
 *Created - Dec. 19, 2022
 *Last Changed - Dec. 20, 2022
 *Description - Simple as possible Bitmap Uncompressed supports uo to 65,535 x 65,535 Pixel images
====================================================================================*/

/*
 * This program source code file is part of PROJECT_NAME
 *
 * Copyright (C) 2022 Zachary Walden zachary.walden@eagles.oc.edu
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/lgpl-3.0.en.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#include "stdint.h"

enum SapStatus
{
	SapSuccess, SapFileNotFound, SapIncorrectFileExtension
};
enum SapColorMode
{
	Rgb8Bpc,
	Rgb10Bpc,
	Bgr8Bpc,
	Bgr10Bpc,
	Mono4Bpc,
	Mono8Bpc,
	Mono10Bpc,
}

struct SapBitMapHeader
{
	uint16_t h_res;
	uint16_t v_res;
	SapColorMode color_mode;
};

class SapBitMap
{
	//Attributes
public:

private:

	uint8_t image[][][];
	//Methods
public:
	SapBitMap();
	SapBitMap(char* filename);
	SapBitMap(uint16_t h_res, uint16_t v_res, SapColorMode color_mode);
	~SapBitMap();

	SapStatus load(char* filename);
	SapStatus write(char* filename);

private:
};
