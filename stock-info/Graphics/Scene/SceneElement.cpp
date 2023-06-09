/*==================================================================================
 *Class - SceneElement
 *Author - Zach Walden
 *Created - 5/30/23
 *Last Changed - 5/30/23
 *Description - SceneElement Context
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


#include "../Graphics.hpp"
#include "../Sprite/Sprite.hpp"

namespace ZwGraphics {

class SceneElement
{
	//Attributes
public:

private:
	Graphics* graphics = nullptr;
	Point position;
	//Methods
public:
	SceneElement(Graphics* graphics, Point position)
	{
		this->graphics = graphics;
		this->position = position;
	}
	virtual ~SceneElement()
	{

	}

	virtual void draw() = 0;

	Point getPosition()
	{
		return this->position;
	}

	Graphics* getRenderer()
	{
		return this->graphics;
	}
private:
};

//Concrete Strategies
class CharSceneElement : public SceneElement
{
	private:
		char character;
		Font cFont;
		Color cColor;
	public:
		CharSceneElement(Graphics* graphics, Point position, char character, Font cFont, Color cColor) : SceneElement(graphics, position)
		{
			this->character = character;
			this->cFont = cFont;
			this->cColor = cColor;
		}
		void draw() override
		{
			if(this->getRenderer() == nullptr)
				return;
			this->getRenderer()->PlotChar(this->getPosition(), this->character, this->cFont, this->cColor);
		}
};

class StringSceneElement : public SceneElement
{
	private:
		char* string;
		Font sFont;
		Color sColor;
	public:
		~StringSceneElement()
		{

		}
		StringSceneElement(Graphics* graphics, Point position, char* string, Font sFont, Color sColor) : SceneElement(graphics, position)
		{
			this->string = string;
			this->sFont = sFont;
			this->sColor = sColor;
		}
		void draw() override
		{
			if(this->getRenderer() == nullptr)
				return;
			this->getRenderer()->PlotString(this->getPosition(), this->string, this->sFont, this->sColor);
		}
};

class SpriteSceneElement : public SceneElement
{
	private:
		Sprite* sprite;
	public:
		~SpriteSceneElement()
		{
			delete this->sprite;
		}
		SpriteSceneElement(Graphics* graphics, Sprite* sprite) : SceneElement(graphics, sprite->getPosition())
		{
			this->sprite = sprite;
		}
		void draw() override
		{
			if(this->getRenderer() == nullptr)
				return;
			this->getRenderer()->PlotSprite(this->sprite->getRect(), this->sprite->getSpriteData());
		}
};

class LineSceneElement : public SceneElement
{
	private:
		Point pStart, pEnd;
		Color lColor;
	public:
		LineSceneElement(Graphics* graphics, Point pStart, Point pEnd, Color lColor) : SceneElement(graphics, pStart)
		{
			this->pStart = pStart;
			this->pEnd = pEnd;
			this->lColor = lColor;
		}
		void draw() override
		{
			if(this->getRenderer() == nullptr)
				return;
			this->getRenderer()->PlotLine(pStart, pEnd, lColor);
		}
};

class RectangleSceneElement : public SceneElement
{
	private:
		Rectangle rRect;
		Color rColor;
	public:
		RectangleSceneElement(Graphics* graphics, Rectangle rRect, Color rColor) : SceneElement(graphics, rRect.p_top_left)
		{
			this->rRect = rRect;
			this->rColor = rColor;
		}
		void draw() override
		{
			if(this->getRenderer() == nullptr)
				return;
			this->getRenderer()->PlotRectangle(rRect, rColor);
		}
};

class FilledRectangleSceneElement : public SceneElement
{
	private:
		Rectangle rRect;
		Color rColor;
	public:
		FilledRectangleSceneElement(Graphics* graphics, Rectangle rRect, Color rColor) : SceneElement(graphics, rRect.p_top_left)
		{
			this->rRect = rRect;
			this->rColor = rColor;
		}
		void draw() override
		{
			if(this->getRenderer() == nullptr)
				return;
			this->getRenderer()->PlotRectangleFilled(rRect, rColor);
		}
};

class CircleSceneElement : public SceneElement
{
	private:
		Circle cCircle;
		Color cColor;
	public:
		CircleSceneElement(Graphics* graphics, Circle cCircle, Color cColor) : SceneElement(graphics, cCircle.center)
		{
			this->cCircle = cCircle;
			this->cColor = cColor;
		}
		void draw() override
		{
			if(this->getRenderer() == nullptr)
				return;
			this->getRenderer()->PlotCircle(cCircle, cColor);
		}
};

class FilledCircleSceneElement : public SceneElement
{
	private:
		Circle cCircle;
		Color cColor;
	public:
		FilledCircleSceneElement(Graphics* graphics, Circle cCircle, Color cColor) : SceneElement(graphics, cCircle.center)
		{
			this->cCircle = cCircle;
			this->cColor = cColor;
		}
		void draw() override
		{
			if(this->getRenderer() == nullptr)
				return;
			this->getRenderer()->PlotCircleFilled(cCircle, cColor);
		}
};

class TriangleSceneElement : public SceneElement
{
	private:
		Triangle tTriangle;
		Color tColor;
	public:
		TriangleSceneElement(Graphics* graphics, Triangle tTriangle, Color tColor) : SceneElement(graphics, tTriangle.p1)
		{
			this->tTriangle = tTriangle;
			this->tColor = tColor;
		}
		void draw() override
		{
			if(this->getRenderer() == nullptr)
				return;
			this->getRenderer()->PlotTriangle(tTriangle, tColor);
		}
};

class FilledTriangleSceneElement : public SceneElement
{
	private:
		Triangle tTriangle;
		Color tColor;
	public:
		FilledTriangleSceneElement(Graphics* graphics, Triangle tTriangle, Color tColor) : SceneElement(graphics, tTriangle.p1)
		{
			this->tTriangle = tTriangle;
			this->tColor = tColor;
		}
		void draw() override
		{
			if(this->getRenderer() == nullptr)
				return;
			this->getRenderer()->PlotTriangleFilled(tTriangle, tColor);
		}
};

class GradientSceneElement : public SceneElement
{
	private:
		Gradient gGradient;
		Rectangle gRect;
	public:
		GradientSceneElement(Graphics* graphics, Rectangle gRect, Gradient gGradient) : SceneElement(graphics, gRect.p_top_left)
		{
			this->gGradient = gGradient;
			this->gRect = gRect;
		}
		void draw() override
		{
			if(this->getRenderer() == nullptr)
				return;
			this->getRenderer()->Gradient1D(gGradient, gRect);
		}
};

class Gradient2dSceneElement : public SceneElement
{
	private:
		Gradient gGradient1, gGradient2;
		Rectangle gRect;
	public:
		Gradient2dSceneElement(Graphics* graphics, Rectangle gRect, Gradient gGradient1, Gradient gGradient2) : SceneElement(graphics, gRect.p_top_left)
		{
			this->gGradient1 = gGradient1;
			this->gGradient2 = gGradient2;
			this->gRect = gRect;
		}
		void draw() override
		{
			if(this->getRenderer() == nullptr)
				return;
			this->getRenderer()->Gradient2D(gGradient1, gGradient2, gRect);
		}
};

}
