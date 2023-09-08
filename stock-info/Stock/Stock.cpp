/*==================================================================================
 *Class -
 *Author - Zach Walden
 *Created -
 *Last Changed -
 *Description -
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

#include "Stock.hpp"
namespace ZwStock
{

Stock::Stock()
{

}

Stock::Stock(std::string ticker, std::string imagePath)
{
	this->ticker = ticker;
	this->imagePath = imagePath;
}

Stock::~Stock()
{

}

ZwGraphics::Scene* Stock::getScene(int index)
{
	if(index >= this->scenes.size())
	{
		LOG("Index out of range");
		return nullptr;
	}

	return this->scenes[index];
}

int Stock::getNumScenes()
{
	return this->scenes.size();
}

void Stock::addScene(ZwGraphics::Scene* scene)
{
	this->scenes.push_back(scene);
}

SeriesData* Stock::getData(int index)
{
	if(index >= this->data.size())
	{
		LOG("Index out of range");
		return nullptr;
	}

	return this->data[index];
}
int Stock::getNumDataSeries()
{
	return this->data.size();
}
void Stock::addDataSeries(SeriesData* dataSeries)
{
	this->data.push_back(dataSeries);
}
std::string Stock::getTicker()
{
	return this->ticker;
}
void Stock::draw()
{
	for (int i = 0; i < this->scenes.size(); i++)
	{
		this->scenes[i]->draw();
	}
}

}

















/*
<++> Stock::<++>()
{

}
*/
