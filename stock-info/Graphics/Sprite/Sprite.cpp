/*==================================================================================
 *Class - Sprite
 *Author - Zach Walden
 *Created - 1/30/23
 *Last Changed - 1/30/23
 *Description - Sprite, basic wrapper around a bitmap. Abstracts dynamic allocation.
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

#pragma once

#include "Sprite.hpp"
#include "../../Logging/Logging.hpp"

namespace ZwGraphics
{

Sprite::Sprite()
{

}
Sprite::Sprite(std::string filename, Point position)
{
	this->bmp = new ZwBitmap();
	if(bmp)
	{
		this->bmp->readBitmap(filename);
	}
	else
	{
		LOGV(filename,", Failed to allocate memory for Sprite.");
	}
	this->position = position;
}
Sprite::~Sprite()
{
	delete this->bmp;
}
uint8_t*** Sprite::getSpriteData()
{
	return this->bmp->getData();
}
uint32_t Sprite::getHeight()
{
	return this->bmp->getHeight();
}
uint32_t Sprite::getWidth()
{
	return this->bmp->getWidth();
}
Rectangle Sprite::getRect()
{
	return Rectangle(this->position, Point(this->getPosition().x + this->getWidth(), this->getPosition().y + this->getHeight()));
}
Point Sprite::getPosition()
{
	return this->position;
}
void Sprite::setPosition(Point position)
{
	this->position = position;
}


}

/*
<++> Sprite::<++>()
{

}
*/
