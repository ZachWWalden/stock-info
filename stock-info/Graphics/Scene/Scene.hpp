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

#pragma once
#include "stdint.h"
#include <vector>

struct SceneElement
{
	uint8_t x;
	uint8_t y;
	char* string = nullptr;
	Sprite* sprite = nullptr;

	SceneElement(uint8_t x_coord, uint8_t y_coord)
	{
		x = x_coord;
		y = y_coord;
	}
};

//State Declarations
enum SceneState
{
	Focused, TransitionIn, TransitionOut, Unused
};
enum SceneEvent
{
	BeginTransition, EndTransition, MaintainState
};

class Scene
{
	//Attributes
public:

private:
	uint8_t height;
	uint8_t width;
	uint8_t num_channels;
	uint8_t*** buffer;
	std::vector<SceneElement> elements;

	//State
	SceneState state = Unused;

	//State vairables
	uint8_t transition_rate = 17;
	uint8_t transparency = 0;
	//Methods
public:
	Scene(uint8_t height, uint8_t width, uint8_t num_channels);
	~Scene();

	void draw();
	bool addElement(SceneElement element);

	//Getters/Setters
	uint8_t getHeight();
	void setHeight(uint8_t height);

	uint8_t getWidth();
	void setWidth(uint8_t width);

	uint8_t*** getBuffer();

	std::vector* getElements();

	//State Methods.
	void HandleEvent(SceneEvent event);

	uint8_t getTransparency();
private:
};

class StockLogoScene : Scene
{

};

class StockGraphScene : Scene
{

};
