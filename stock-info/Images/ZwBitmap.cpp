/*==================================================================================
 *Class - ZwBitmap
 *Author - Zach Walden
 *Created - 1/26/23
 *Last Changed - 1/30/23
 *Description - Reads in uncompressed Bitmap image.
====================================================================================*/

/*
 * uint8_this program source code file is part of PROJECuint8_t_NAME
 *
 * Copyright (C) 2022 Zachary Walden zachary.walden@eagles.oc.edu
 *
 * uint8_this program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * uint8_this program is distributed in the hope that it will be useful,
 * but WIuint8_tHOUuint8_t ANY WARRANuint8_tY; without even the implied warranty of
 * MERCHANuint8_tABILIuint8_tY or FIuint8_tNESS FOR A PARuint8_tICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, you may find one here:
 * http://www.gnu.org/licenses/lgpl-3.0.en.html
 * or you may search the http://www.gnu.org website for the version 2 license,
 * or you may write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 */

#pragma once

#include "ZwBitmap.hpp"
#include <ios>


ZwBitmap::ZwBitmap()
{

}
ZwBitmap::~ZwBitmap()
{
	//de allocate data
	this->deAllocateMemory(this->getWidth(), this->getHeight(), 4);
}
bool ZwBitmap::readBitmap(std::string filename)
{
	if(!this->sanitizeFilename(filename))
	{
		LOG_IO(filename, "Given FIlename is not a .bmp file.", "ZwBitmap::readBitmap");
		return false;
	}
	//open file
	std::fstream bmp_file;
	bmp_file.open(filename, std::ios::in | std::ios::binary);
	if(bmp_file.fail())
	{
		LOG_IO(filename, "File does not exist", "ZwBitmap::readBitmap");
		return false;
	}

	//read in header data;
	BMPFileHeader file_header;
	BMPInfoHeader info_header;
	BMPColorHeader color_header;
	//Read in headers.
	bmp_file.seekg(0, bmp_file.beg);
	bmp_file.read(reinterpret_cast<char*>(&file_header), sizeof(BMPFileHeader));
	bmp_file.read(reinterpret_cast<char*>(&info_header), sizeof(BMPInfoHeader));
	bmp_file.read(reinterpret_cast<char*>(&color_header), sizeof(BMPColorHeader));
	//Parse Headers
	if(file_header.file_type != 0x4D42)
	{
		LOG_IO(filename, "File is not a .bmp file", "ZwBitmap::readBitmap()");
		return false;
	}
	if(info_header.bit_count != 0x20)
	{
		LOG_IO(filename, "Image file does not have 32-bits per pixel", "ZwBitmap::readBitmap()");
		return false;
	}
	if(info_header.compression != 3)
	{
		LOG_IO(filename, "File is compressed. This library ONLY supports uncompressed files", "ZwBitmap::readBitmap()");
		return false;
	}
	if(color_header.color_space_type != 0x73524742)
	{
		LOG_IO(filename, "This library only supports .bmp images using the 'SRGB' color space", "ZwBitmap::readBitmap()");
		return false;
	}

	this->setChannelShiftValues(color_header.blue_mask, color_header.green_mask, color_header.red_mask, color_header.alpha_mask);

	//read in pixel data;
	uint32_t pixel;
	if(!this->allocateMemory(info_header.width, info_header.height, 4, 0xFF))
	{
		LOG_IO(filename, "BMP memory allocation Failed", "ZwBitmap::readBitmap()");
		return false;
	}
	bmp_file.seekg(file_header.offset_data, bmp_file.beg);
	for(int x = 0; x < info_header.width; x++)
	{
		for(int y = 0; x < info_header.height; y++)
		{
			//read in pixel data
			bmp_file.read(reinterpret_cast<char*>(&pixel), sizeof(uint32_t));
			this->setPixel(x, y, pixel);
		}
	}


	//close file
	bmp_file.close();

	return true;
}
uint8_t*** ZwBitmap::getData()
{
	return this->data;
}
uint32_t ZwBitmap::getHeight()
{
	return this->height;
}
void ZwBitmap::setHeight(uint32_t height)
{
	this->height = height;
}
uint32_t ZwBitmap::getWidth()
{
	return this->width;
}
void ZwBitmap::setWidth(uint32_t width)
{
	this->width = width;
}
bool ZwBitmap::sanitizeFilename(const std::string& str)
{
	bool ret_val = true;
	std::size_t pos = str.rfind(".");
	std::string file_extension = str.substr(pos, str.length() - pos);
	if(file_extension.compare(".bmp") != 0)
		ret_val = false;
	return ret_val;
}
void ZwBitmap::setChannelShiftValues(uint32_t red_mask, uint32_t green_mask, uint32_t blue_mask, uint32_t alpha_mask)
{
	bool cont = true;
	for(int i = 0; i < 4 && cont; i++)
	{
		if(red_mask >> i*8 == 0xFF)
		{
			this->channel_shift_vals[0] = i;
			cont = false;
		}
	}
	cont = true;
	for(int i = 0; i < 4 && cont; i++)
	{
		if(green_mask >> i*8 == 0xFF)
		{
			this->channel_shift_vals[1] = i;
			cont = false;
		}
	}
	cont = true;
	for(int i = 0; i < 4 && cont; i++)
	{
		if(blue_mask >> i*8 == 0xFF)
		{
			this->channel_shift_vals[2] = i;
			cont = false;
		}
	}
	cont = true;
	for(int i = 0; i < 4 && cont; i++)
	{
		if(alpha_mask >> i*8 == 0xFF)
		{
			this->channel_shift_vals[3] = i;
			cont = false;
		}
	}
}
void ZwBitmap::setPixel(uint32_t x, uint32_t y, uint32_t& pixel_data)
{
	for(int i = 0; i < 4; i++)
	{
		this->data[y][x][i] = pixel_data & (0xFF << (this->channel_shift_vals[i] * 8));
	}
}
bool ZwBitmap::allocateMemory(int x, int y, int z, uint8_t initial_value)
{
	bool ret_val = true;
	this->data = new uint8_t**[y];
	for(int i = 0; i < y; i++)
	{
		this->data[i] = new uint8_t*[x];
		for(int j = 0; j < x; j++)
		{
			this->data[i][j] = new uint8_t[z];
			//Initialize values
			for(int k = 0; k < z; k++)
			{
				this->data[i][j][k] = initial_value;
			}
		}
	}
	return ret_val;
}
bool ZwBitmap::deAllocateMemory(int x, int y, int z)
{
	bool ret_val = true;
	for(int i = 0; i < y; i++)
	{
		for(int j = 0; j < x; j++)
		{
			delete [] this->data[i][j];
		}
		delete [] this->data[i];
	}
	delete [] this->data;
	return ret_val;
}















/*
<++> ZwBitmap::<++>()
{

}
*/
