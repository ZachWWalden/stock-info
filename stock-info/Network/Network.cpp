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

#include "Network.hpp"
#include <cstdlib>
#include <curl/curl.h>
#include <curl/easy.h>
#include <cstring>
#include <string>

#include "../Logging/Logging.hpp"

Network::Network()
{

}

Network::Network(std::string url)
{
	//initialize curl object
	this->initCurl();
	this->url = url;

}

Network::~Network()
{
	if(this->curl != nullptr)
		curl_easy_cleanup(this->curl);
}


void Network::makeRequest()
{
	curl_easy_setopt(this->curl, CURLOPT_URL, this->url.c_str());
	CURLcode res = curl_easy_perform(this->curl);

}

std::size_t Network::WriteCallback(void* received_data, std::size_t size, std::size_t nmemb, void* userdata)
{
	std::size_t realsize = size * nmemb;
	Response* mem = (Response*)userdata;

	char* ptr = (char*)realloc(mem->memory, mem->size + realsize + 1);
	if(!ptr)
	{
		//Out of Memory
		LOG("Out of Memory, malloc returned NULL");
		return 0;
	}

	mem->memory = ptr;
	std::memcpy(&(mem->memory[mem->size]), received_data, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	printf("%s", mem->memory);

	return realsize;
}

void Network::setURL(std::string url)
{
	this->url = url;
}

void Network::initCurl()
{
	this->curl = curl_easy_init();
	curl_easy_setopt(this->curl, CURLOPT_WRITEFUNCTION, this->WriteCallback);
	curl_easy_setopt(this->curl, CURLOPT_WRITEDATA, (void*)this->response);
}
















/*
<++> Network::<++>()
{

}
*/
