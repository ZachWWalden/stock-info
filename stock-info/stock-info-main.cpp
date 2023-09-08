// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Small example how to use the library.
// For more examples, look at demo-main.cc
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)
#include <bits/chrono.h>
#include <cstddef>
#include <cstdlib>
#include <json/config.h>
#include <json/reader.h>
#include <json/value.h>
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <string>
#include <pthread.h>
#include <semaphore.h>
#include <json/json.h>
#include <fstream>
#include <iostream>
#include <vector>
#include <chrono>

#include "Graphics/Graphics.hpp"
#include "Graphics/Scene/Scene.hpp"
#include "Graphics/Sprite/Sprite.hpp"
#include "Utils/triplepointer.hpp"
#include "Network/Network.hpp"
#include "stdint.h"
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

//Define constants for screen resolution and pixel channels.
#define V_RES 32
#define H_RES 64
#define NUM_CHANNELS 3

#define NUM_SECONDS 30
#define MIN_CRON_STEPS 60/NUM_SECONDS
#define HR_CRON_STEPS 60*MIN_CRON_STEPS
#define DAY_CRON_STEPS 24*HR_CRON_STEPS
#define WEEK_CRON_STEPS 7*DAY_CRON_STEPS
#define MONTH_CRON_STEPS 4*WEEK_CRON_STEPS //defined as 4 weeks.

#define CONFIG_PATH "stocks/stocks.json"

enum CronStepEnum
{
	MINUTE = 0, HOUR = 1, DAY = 2, WEEK = 3, MONTH = 4
};

std::vector<ZwStock::Stock*> stocks;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
}
void* networkThread(void* arg);
int getNumCronSteps(Json::Value series)
{
	int unitCronSteps = 0;
	//get unit
	if(series["update_unit"].asString().compare("m") == 0)
		unitCronSteps = MIN_CRON_STEPS;
	else if (series["update_unit"].asString().compare("hr") == 0)
		unitCronSteps = HR_CRON_STEPS;
	else if (series["update_unit"].asString().compare("d") == 0)
		unitCronSteps = HR_CRON_STEPS;
	else if (series["update_unit"].asString().compare("w") == 0)
		unitCronSteps = HR_CRON_STEPS;
	else if (series["update_unit"].asString().compare("mn") == 0)
		unitCronSteps = HR_CRON_STEPS;

	return unitCronSteps;
}
/*
static void Fill(uint8_t* frmBuff, uint8_t red, uint8_t green, uint8_t blue)
{
	for(int rows = 0; rows < V_RES; rows++)
	{
		for(int cols = 0; cols < H_RES; cols++)
		{
			frmBuff[rows][cols][0] = red;
			frmBuff[rows][cols][1] = blue;
			frmBuff[rows][cols][2] = green;
		}
	}
}
*/

int main(int argc, char *argv[]) {
  RGBMatrix::Options defaults;
  defaults.hardware_mapping = "adafruit-hat";  // or e.g. "adafruit-hat"
  defaults.rows = V_RES;
  defaults.cols = H_RES;
  defaults.chain_length = 1;
  defaults.parallel = 1;
  //This sets the default brightness.
  defaults.brightness = 50;
  defaults.scan_mode = 0;
  defaults.show_refresh_rate = true;
  Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
  if (canvas == NULL)
    return 1;

  // It is always good to set up a signal handler to cleanly exit when we
  // receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
  // for that.
  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  ZwGraphics::Graphics graphics_mgr(canvas, V_RES, H_RES);
  ZwGraphics::Font font916 = graphics_mgr.fontFactory(ZwGraphics::Font9x16);
  ZwGraphics::Font font79 = graphics_mgr.fontFactory(ZwGraphics::Font7x9);

  //open list of tickers and ticker parameters.
  Json::Value root;
  std::ifstream ifs;
  ifs.open(CONFIG_PATH);

  Json::CharReaderBuilder builder;
  JSONCPP_STRING errs;

  if(!Json::parseFromStream(builder, ifs, &root, &errs))
  {
  	std::cout << errs << std::endl;
	return EXIT_FAILURE;
  }
  //build stock data structure.
  //allocate memory for stocks vector based on number of stocks.
  Json::Value stocksJson = root["stocks"];
  //Resize stock vector based on the number of stocks in the configuration file.
  stocks.resize(stocksJson.size());
  for(int i = 0; i < stocksJson.size(); ++i)
  {
	Json::Value curStock = stocks[i];
	//allocate new stock object, add it to vector of stocks.
	ZwStock::Stock* newStock = new ZwStock::Stock(curStock["ticker"].asString(), curStock["image"].asString());
	//loop thorugh time series.
	Json::Value seriesJson = curStock["series"];

	for(int j = 0; j < seriesJson.size(); ++j)
	{
		Json::Value curSeries = seriesJson[i];
		ZwStock::SeriesData* newSeries = new ZwStock::SeriesData();
		//TODO un hardcode
		newSeries->function = ZwStock::ApiFunction::TIME_SERIES_INTRADAY;
		newSeries->NUM_CRON_STEPS = getNumCronSteps(curSeries) * curSeries["update_interval"].asInt();
		newSeries->interval = curSeries["interval"].asString();

	}
  }

  //start network thread and wait for data.
  long unsigned int tid;
  pthread_create(&tid, NULL, networkThread, &tid);

  while(!interrupt_received)
  {
	//measure time at start
	auto startTime = std::chrono::high_resolution_clock::now();
	//DO STUFF
	//{

	//}
	graphics_mgr.draw();
	//measure time at end
	auto endTime = std::chrono::high_resolution_clock::now();
	//find execution time
	auto execTime = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
	//subtract execution time from target frame period.
	int sleepTime = 33333 - (int)execTime.count();

	//sleep
	usleep(sleepTime); //period for 30fps
  }

  //wait on network thread to exit.
  pthread_join(tid, NULL);

  // Animation finished. Shut down the RGB matrix.
  canvas->Clear();
  delete canvas;
  return 0;
}

void* networkThread(void* arg)
{

	//create network object
	std::string url = "https://www.alphavantage.co/query"; //dummy URL
    ZwNetwork::Network network(url);
    ZwNetwork::Response* response;
	//get initial network data.
	//acquire semaphore
	for(int i = 0; i < stocks.size(); i++)
	{
		for (int j = 0; j < stocks[i]->getNumDataSeries(); j++)
		{
			ZwStock::SeriesData* curSeries = stocks[i]->getData(i);
			//get data from network.
			network.buildURL(stocks[i]->getTicker(), curSeries->function, curSeries->interval);
			response = network.makeRequest();
			//marshall json
			Json::Value root;
			Json::CharReaderBuilder builder;
			JSONCPP_STRING errs;
			Json::CharReader* reader(builder.newCharReader());
			if(!reader->parse(response->memory, response->memory + response->size, &root, &errs))
			{
				std::cout << "error parsing network json" << std::endl;
			}
			//free memory
			delete response->memory;
			curSeries->data = root;
		}
	}
	//release semaphore.
	while (!interrupt_received)
	{
		//Cron loop
		usleep(1000*1000*NUM_SECONDS);
		//loop through stocks and update data accordingly
		for(int i = 0; i < stocks.size(); i++)
		{
			for (int j = 0; j < stocks[i]->getNumDataSeries(); j++)
			{
				ZwStock::SeriesData* curSeries = stocks[i]->getData(i);
				curSeries->cronCounter++;
				//if cron counter == NUM_CRON_STEPS
				if(curSeries->cronCounter == curSeries->NUM_CRON_STEPS)
				{
					//get data from network.
					network.buildURL(stocks[i]->getTicker(), curSeries->function, curSeries->interval);
					response = network.makeRequest();
					//marshall json
					Json::Value root;
					Json::CharReaderBuilder builder;
					JSONCPP_STRING errs;
					Json::CharReader* reader(builder.newCharReader());
					if(!reader->parse(response->memory, response->memory + response->size, &root, &errs))
					{
						std::cout << "error parsing network json" << std::endl;
					}
					//free memory
					delete response->memory;
					curSeries->data = root;
					curSeries->cronCounter = 0;
				}
			}
		}
	}
	pthread_exit(0);
}
