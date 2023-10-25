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

#include "../include/led-matrix.h"
#include "stdint.h"
using rgb_matrix::RGBMatrix;
using rgb_matrix::Canvas;

//Define constants for screen resolution and pixel channels.
#define V_RES 64
#define H_RES 64
#define NUM_CHANNELS 3

#define NUM_SECONDS 30

#define IMAGE_PATH "stocks/"

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
  defaults.brightness = 10;
  defaults.scan_mode = 0;
  defaults.show_refresh_rate = false;
  Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
  if (canvas == NULL)
    return 1;

  // It is always good to set up a signal handler to cleanly exit when we
  // receive a CTRL-C for instance. The DrawOnCanvas() routine is looking
  // for that.
  signal(SIGTERM, InterruptHandler);
  signal(SIGINT, InterruptHandler);

	for(int rows = 0; rows < V_RES; rows++)
	{
		for(int cols = 0; cols < H_RES; cols++)
		{
			canvas->SetPixel(cols, rows, 0x0F, 0x0F, 0x0F);
		}
	}

	usleep(1000*1000*NUM_SECONDS);

  // Animation finished. Shut down the RGB matrix.
  canvas->Clear();
  delete canvas;
  return 0;
}
