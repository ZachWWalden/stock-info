/*==================================================================================
 *Class - Scene
 *Author - Zach Walden
 *Created - 12/20/22
 *Last Changed - 12/20/22
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



class Scene
{
	//Attributes
public:

private:
	uint8_t* sceneBuffer;
	char** stockTicker;
	uint8_t numStrings = 0;
	//Methods
public:
	Scene();
	~Scene();
	
	virtual void draw() = 0;
private:
};

class StockLogoScene : Scene
{

};

class StockGraphScene : Scene
{

};
