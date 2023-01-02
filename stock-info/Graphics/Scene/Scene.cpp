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

#include "CHANGE.hpp"

Scene::Scene(uint8_t height, uint8_t width, uint8_t num_channels)
{
	this->height = height;
	this->width = width;
	this->num_channels = num_channels;
	//Use new data to allocate memory
}
~Scene()
{
	//Free Dynamically allocated buffer
}
void Scene::draw()
{

}
bool Scene::addElement(SceneElement element)
{

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
std::vector* Scene::getElements()
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
		if(event == EndTransition
	}
	else if(this->state == TransitionOut)
	{

	}
	else if(this->state ++ Focused)
	{

	}
}
uint8_t Scene::getTransparency()
{
	return this->transparency;
}

















/*
<++> CHANGE::<++>()
{

}
*/
