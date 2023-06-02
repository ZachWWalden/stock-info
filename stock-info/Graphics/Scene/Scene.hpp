/*==================================================================================
 *Class - Scene
 *Author - Zach Walden
 *Created - 12/20/22
 *Last Changed - 2/15/23
 *Description - Represents a Scene to be displayed. deallocates scene elements and framebuffer.
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
#include "../Sprite/Sprite.hpp"
#include "../Graphics.hpp"

//for rendering
#include "SceneElement.hpp"
namespace ZwGraphics
{
//State Declarations
enum SceneState
{
	Focused, TransitionIn, TransitionOut, Unused
};
enum SceneEvent
{
	BeginTransition, EndTransition, MaintainState, IncrementFrame
};

class Scene
{
	//Attributes
public:

private:
	uint8_t height;
	uint8_t width;
	uint8_t numChannels;

	Graphics* graphics;

	uint8_t*** buffer;
	std::vector<SceneElement*> elements;

	//State
	SceneState state = Unused;

	//State vairables
	uint8_t transitionRate = 17;
	uint8_t transparency = 0;
	//Methods
public:
	Scene(Graphics* graphics, uint8_t height, uint8_t width, uint8_t num_channels);
	~Scene();

	void draw();
	bool addElement(SceneElement* element);

	//Getters/Setters
	uint8_t getHeight();
	void setHeight(uint8_t height);

	uint8_t getWidth();
	void setWidth(uint8_t width);

	uint8_t*** getBuffer();

	std::vector<SceneElement*>* getElements();

	//State Methods.
	void HandleEvent(SceneEvent event);

	uint8_t getTransparency();
private:
};

}
