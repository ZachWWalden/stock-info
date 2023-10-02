/*==================================================================================
 *Class - Stock
 *Author - Zach Walden
 *Created - 7/6/2023
 *Last Changed - 7/6/2023
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

#include <vector>
#include <jsoncpp/json/json.h>

#include "../Graphics/Scene/Scene.hpp"
#include "../Logging/Logging.hpp"

namespace ZwStock
{

enum ApiFunction
{
	TIME_SERIES_INTRADAY, TIME_SERIES_DAILY, TIME_SERIES_WEEKLY, TIME_SERIES_MONTHLY
};

struct SeriesData
{
	ApiFunction function;
	Json::Value data; //general data semaphore only is waited on while these are updated. Network thread will only request semaphore once it has data from the stock api.
	std::string interval;
	int NUM_CRON_STEPS;
	int cronCounter;
	bool dataChanged = false;
};

class Stock
{
	//Attributes
public:

private:
	std::vector<ZwGraphics::Scene*> scenes;
	std::vector<SeriesData*> data;

	std::string ticker;
	std::string imagePath;
	//Methods
public:
	Stock();
	Stock(std::string ticker, std::string imagePath);
	~Stock();

	ZwGraphics::Scene* getScene(int index);
	int getNumScenes();

	void addScene(ZwGraphics::Scene* scene);

	SeriesData* getData(int index);
	int getNumDataSeries();

	void addDataSeries(SeriesData* dataSeries);

	std::string getTicker();
	std::string getImagePath();

	void draw();

private:
};

}
