/*==================================================================================
 *Class - Scene
 *Author - Zach Walden
 *Created - 1/1/23
 *Last Changed - 1/1/23
 *Description - Contains the data to render a scene to a target buffer. Also contains
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

#include "Scene.hpp"
#include "../../Utils/triplepointer.hpp"
#include "stdint.h"

namespace ZwGraphics
{

Scene::Scene(Graphics* graphics, uint8_t height, uint8_t width, uint8_t num_channels)
{
	this->height = height;
	this->width = width;
	this->numChannels = num_channels;

	this->graphics = graphics;
	//Use new data to allocate memory
	this->buffer = allocTriplePointer<uint8_t>(this->height, this->width, this->numChannels, 0x00);
}
Scene::~Scene()
{
	//Free Dynamically allocated buffer
	deallocTriplePointer<uint8_t>(this->buffer, this->height, this->width);
	//Deallocate SceneElements
	for(long unsigned int i = 0; i < this->elements.size(); i++)
	{
		delete this->elements[i];
	}
}
void Scene::draw()
{
	//set graphics singleton render target to our scene buffer.
	this->graphics->setRenderTarget(this->buffer);
	this->graphics->setHeight(this->height);
	this->graphics->setWidth(this->width);
	//loop trhough elements
	for (long unsigned int i = 0; i < this->elements.size(); i++)
	{
		elements[i]->draw();
	}
}
bool Scene::addElement(SceneElement* element)
{
	this->elements.push_back(element);
	return true;
}
uint8_t Scene::getHeight()
{
	return this->height;
}
void Scene::setHeight(uint8_t height)
{
	this->height = height;
}
uint8_t Scene::getWidth()
{
	return this->width;
}
void Scene::setWidth(uint8_t width)
{
	this->width = width;
}
uint8_t*** Scene::getBuffer()
{
	return this->buffer;
}
std::vector<SceneElement*>* Scene::getElements()
{
	return &(this->elements);
}
void Scene::HandleEvent(SceneEvent event)
{
	if(this->state == Unused)
	{
		if(event == BeginTransition)
		{
			this->state=TransitionIn;
			this ->transparency = 0;
		}
	}
	else if(this->state == TransitionIn)
	{
		if(event == EndTransition)
		{
			this->state = Focused;
		}
		else if (event == IncrementFrame)
		{
			this->transparency += this->transitionRate;
		}
	}
	else if(this->state == TransitionOut)
	{
		if(event == EndTransition)
		{
			this->state = Unused;
		}
		else if (event == IncrementFrame)
		{
			this->transparency -= this->transitionRate;
		}
	}
	else if(this->state == Focused)
	{
		if(event == BeginTransition)
		{
			this-> state = TransitionOut;
		}
	}
}
uint8_t Scene::getTransparency()
{
	return this->transparency;
}

}















/*
<++> Scene::<++>()
{

}
*/
