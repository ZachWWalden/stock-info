// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Small example how to use the library.
// For more examples, look at demo-main.cc
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)
#include <bits/chrono.h>
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
#define MIN_CRON_STEPS 2
#define HR_CRON_STEPS 120
#define DAY_CRON_STEPS 2880
#define WEEK_CRON_STEPS 20160
#define MONTH_CRON_STEPS 80640 //defined as 4 weeks.

#define CONFIG_PATH "stocks/stocks.json"

enum CronStepEnum
{
	MINUTE = 0, HOUR = 1, DAY = 2, WEEK = 3, MONTH = 4
};

volatile std::vector<Stock> stocks;

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
  interrupt_received = true;
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
  std::string url = "https://www.alphavantage.co/query?function=TIME_SERIES_DAILY&symbol=NFLX&interval=1min&apikey=4ZE3A29HU6PM9YSU";
  ZwNetwork::Network network(url);
  network.makeRequest();

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

  // Animation finished. Shut down the RGB matrix.
  canvas->Clear();
  delete canvas;
  return 0;
}

int networkThread()
{

	//create network object
	//use std::string and its overloaded operators to form URLS
	for(int i = 0; i < stocks.size(); i++)
	{

	}
	while (!interrupt_received)
	{
		//Cron loop
		usleep(1000*1000*NUM_SECONDS);
	}

	return 0;
}
