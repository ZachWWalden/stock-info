/*==================================================================================
 *Class - Network
 *Author - Zach Walden
 *Created - 6/9/2023
 *Last Changed - 7/6/2023
 *Description - OO libcurl wrapper. The way is handles request data assumes that any Network
 *              request made to this wrapper will return json.
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

#include <cstddef>
#include <cstdlib>
#include <curl/curl.h>
#include <string>

#include "stdint.h"

#include "../Stock/Stock.hpp"

#define ALPHAVANTAGE_API_KEI "4ZE3A29HU6PM9YSU"

namespace ZwNetwork
{

struct Response
{
	char* memory;
	std::size_t size;

	Response()
	{
		memory = (char*)malloc(0);
		size = 0;
	}
};

class Network
{
	//Attributes
public:

private:
	CURL* curl = nullptr;
	std::string url;
	std::string BASE_URL = "https://www.alphavantage.co/query?function=";
	std::string SYMBOL = "&symbol=", INTERVAL = "&interval=",API_KEY = "&apikey=4ZE3A29HU6PM9YSU";
	std::string TS_INTRADAY = "TIME_SERIES_INTRADAY", TS_WEEKLY = "TIME_SERIES_WEEKLY", TS_MONTHLY = "TIME_SERIES_MONTHLY";
	Response* response = new Response();

	char errorBuffer[CURL_ERROR_SIZE + 10];
	//Methods
public:
	Network();
	Network(std::string url);
	~Network();

	Response* makeRequest();

	static std::size_t WriteCallback(void* received_data, std::size_t size, std::size_t nmemb, void* userdata);

	std::string getURL();
	void setURL(std::string url);
	void buildURL(std::string ticker, ZwStock::ApiFunction apiFunction, std::string interval);


private:
	void initCurl();
};

}
