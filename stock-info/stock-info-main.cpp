// -*- mode: c++; c-basic-offset: 2; indent-tabs-mode: nil; -*-
// Small example how to use the library.
// For more examples, look at demo-main.cc
//
// This code is public domain
// (but note, that the led-matrix library this depends on is GPL v2)
#include <unistd.h>
#include <math.h>
#include <stdio.h>
#include <signal.h>
#include <string>

#include "Graphics/Graphics.hpp"
#include "Graphics/Scene/Scene.hpp"
#include "Graphics/Sprite/Sprite.hpp"
#include "Utils/triplepointer.hpp"
#include "stdint.h"
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

//Define constants for screen resolution and pixel channels.
#define V_RES 32
#define H_RES 64
#define NUM_CHANNELS 3

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
  char ticker[] = "NFLX";
  char price[] = "$353.11";
  ZwGraphics::Color text_color(255, 255, 0, 0);
  std::string filename = "stocks/nflx.bmp";
  ZwGraphics::Scene* nflxScene = new ZwGraphics::Scene(&graphics_mgr, V_RES, H_RES, 3);
  nflxScene->addElement(new ZwGraphics::StringSceneElement(&graphics_mgr, ZwGraphics::Point(H_RES - 4*9, 0), ticker, font916, text_color));
  nflxScene->addElement(new ZwGraphics::StringSceneElement(&graphics_mgr, ZwGraphics::Point(H_RES - 7*7, 22), price, font79, text_color));
  nflxScene->addElement(new ZwGraphics::SpriteSceneElement(&graphics_mgr, new ZwGraphics::Sprite(filename, ZwGraphics::Point(0,0))));
  while(!interrupt_received)
  {
	//measure time at start
	nflxScene->draw();
	graphics_mgr.draw();
	//draw string
	//clear framebuffer
	//measure time at end

	//find execution time

	//subtract execution time from target frame period.

	//sleep
	usleep(1*1000);
  }

  // Animation finished. Shut down the RGB matrix.
  canvas->Clear();
  delete canvas;
  delete nflxScene;
  return 0;
}
