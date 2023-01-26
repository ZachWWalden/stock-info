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

#include "Text/Text.hpp"
#include "Graphics/Graphics.hpp"
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

//Allocate Triple Pointer
template <typename T>
T*** allocTriplePointer(int y, int x, int depth, T initial_value)
{
	T*** ret_value = new T**[y];
	for(int i = 0; i < y; i++)
	{
		ret_value[i] = new T*[x];
		for(int j = 0; j < x; j++)
		{
			ret_value[i][j] = new T[depth];
			//Initialize values
			for(int k = 0; k < depth; k++)
			{
				ret_value[i][j][k] = initial_value;
			}
		}
	}
	return ret_value;
}

//De-Allocate Triple Pointer
template <typename T>
void deallocTriplePointer(T*** pointer, int y, int x)
{
	for(int i = 0; i < y; i++)
	{
		for(int j = 0; j < x; j++)
		{
			delete [] pointer[i][j];
		}
		delete [] pointer[i];
	}
	delete [] pointer;
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

  //Create Frame Buffer
  uint8_t*** frmBuff = allocTriplePointer<uint8_t>(V_RES, H_RES, NUM_CHANNELS, (uint8_t)0x00);
  // It is always good to set up a signal handler to cleanly exit when we
  // receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
  // for that.
  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

  Graphics graphics_mgr(canvas, V_RES, H_RES);
  graphics_mgr.setRenderTarget(frmBuff);
  ZwGraphics::Color render_color(255, 0, 0, 0);

  while(!interrupt_received)
  {
	//measure time at start
	graphics_mgr.clearRenderTarget();
	graphics_mgr.Gradient1D(ZwGraphics::Gradient(ZwGraphics::Color(255, 25, 59, 120), ZwGraphics::Color(255, 200, 59, 200)), ZwGraphics::Rectangle(ZwGraphics::Point(32,0), ZwGraphics::Point(63,31)));
	graphics_mgr.Gradient2D(ZwGraphics::Gradient(ZwGraphics::Color(255, 25, 59, 120), ZwGraphics::Color(255, 200, 59, 200)), ZwGraphics::Gradient(ZwGraphics::Color(255, 0,0,0), ZwGraphics::Color(255,0,255,0)), ZwGraphics::Rectangle(ZwGraphics::Point(0,0), ZwGraphics::Point(31,31)));
	graphics_mgr.PlotTriangle(ZwGraphics::Triangle(ZwGraphics::Point(25,9), ZwGraphics::Point(33, 25), ZwGraphics::Point(47,5)), render_color);
	graphics_mgr.draw();
	render_color.red++;
	render_color.green++;
	render_color.blue++;
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
  deallocTriplePointer(frmBuff, V_RES, H_RES);

  return 0;
}
