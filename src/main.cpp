#include "WString.h"
#include <Arduino.h>

#include <M5Unified.h>
#include <M5GFX.h>

//#include <bitset>
#include <cstdint>
#include <vector>

#include "prog.h"

// theforge.nekoweb.org

//         :XXXXo;'                .;lXXXXl         
//         cNX....                  ....KNo         
//         ,do                          ld;         
//         ...    .cccccc:  ;cccccc.    ...         
//                ,NNxx0N0  kNKxxNN:                
//                'KK. cKk  xKo  KK;                
//                .::  .:;  ,:'  ::.                
//              ,::::  .::::::'  ::::;              
//                                                  
//              cxc  ',. .xx. .,,  :xo              
//         .'.  ,:,  ...  ::.  ..  ':;  .'.         
//         ,xd                          lx;         
//         cNX''..                  ..''KNo         
//         :KKKKl;'                .;cKKKKc      

//ForgeWorks

//In engineering I trust, and in excellence i confide.

//All rights reserved. (c) 2025 ForgeWorks

// SimuGen: Blood type probability calculator

M5Canvas canvas(&M5.Display);

void setupGraphics();
void redraw();
void prog();

#define color_depth 1

void setup() {
  /* Serial.begin(115200) */
  auto cfg = M5.config();

  #if defined(ARDUINO)
  cfg.serial_baudrate =
      115200; // default=115200. if "Serial" is not needed, set to 0.
  #endif

  M5.begin(cfg);

  // Log to screen
  
  M5.setLogDisplayIndex(0);
  M5.Display.setTextWrap(true, true);
  M5.Display.setTextScroll(true);
  
  // Log all to screen
  M5.Log.setLogLevel(m5::log_target_display, ESP_LOG_VERBOSE);

  if (M5.Rtc.isEnabled()) {
    M5.Rtc.setSystemTimeFromRtc(); // restore time after reboot
  }

  setupGraphics();
}



void loop() {
  M5.update();

  //redraw();

  prog();

  while (true) {}
}

void setupGraphics() {
  M5.Display.setBrightness(128);
  

  // Set to landscape mode
  if (M5.Display.width() < M5.Display.height()) {
    M5.Display.setRotation(M5.Display.getRotation() ^ 1);
  }

  // Adapt text height to minimum.
  int textsize = M5.Display.height() / 160;
  if (textsize == 0) {
    textsize = 1;
  }

  canvas.createSprite(M5.Display.width(), M5.Display.height());
  
  // 4 color palette.
  canvas.setColorDepth(color_depth);

  canvas.setPaletteColor(0, TFT_BLACK);
  canvas.setPaletteColor(1, TFT_WHITE);
  canvas.setPaletteColor(2, TFT_GREEN);
  canvas.setPaletteColor(3, TFT_RED);

  canvas.setTextSize(0);
  
  canvas.fillScreen(TFT_BLACK);
  canvas.pushSprite(0, 0);
}

void drawDnaHelix(float t);

void redraw() {
  
  /* canvas.drawTriangle(100, 20, 150, 80, 50, 80, TFT_WHITE); */
  drawDnaHelix(millis() / 1000.0f);

  canvas.pushSprite(0, 0);
  delay(50);
}