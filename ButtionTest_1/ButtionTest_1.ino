/**
   @example CompText.ino

   @par How to Use
   This example shows that ,when the "+" component on the Nextion screen is released,
   the value of text component will plus 1,when the "-" component released ,the value of
   text component will minus 1 every time.

   @author  Wu Pengfei (email:<pengfei.wu@itead.cc>)
   @date    2015/7/10
   @copyright
   Copyright (C) 2014-2015 ITEAD Intelligent Systems Co., Ltd. \n
   This program is free software; you can redistribute it and/or
   modify it under the terms of the GNU General Public License as
   published by the Free Software Foundation; either version 2 of
   the License, or (at your option) any later version.
*/

#include "Nextion.h"


// Declare a text object [page id:0,component id:2, component name: "textNumber"].
NexText textNumber = NexText(0, 2, "textNumber");

// Declare a button object [page id:0,component id:3, component name: "buttonPlus"].
NexButton buttonPlus = NexButton(0, 3, "buttonPlus");

// Declare a button object [page id:0,component id:4, component name: "buttonMinus"].
NexButton buttonMinus = NexButton(0, 4, "buttonMinus");

int number = 50;
char buffer[10] = {0};


/*
   Register object textNumber, buttonPlus, buttonMinus, to the touch event list.
*/
NexTouch *nex_listen_list[] =
{
  &textNumber,
  &buttonPlus,
  &buttonMinus,
  NULL
};



/*
   Button0 component pop callback function.
   In this example,the value of the text component will plus one every time when button0 is released.
*/
void buttonPlusPushCallback(void *ptr)
{
  dbSerialPrintln("buttonPlusPushCallback");

  if (number < 100) number += 1;

  memset(buffer, 0, sizeof(buffer)); // clear buffer
  itoa(number, buffer, 10);
  textNumber.setText(buffer);
}

/*
   Button1 component push callback function.
   In this example,the value of the text component will minus one every time when button1 is pressed.
*/
void buttonMinusPushCallback(void *ptr)
{
  dbSerialPrintln("buttonMinusPushCallback");

  if (number > 0) number -= 1;
  
  memset(buffer, 0, sizeof(buffer));  // clear buffer
  itoa(number, buffer, 10);
  textNumber.setText(buffer);
}

void setup(void)
{
  /* Set the baudrate which is for debug and communicate with Nextion screen. */
  nexInit();
  
  Serial.begin(115200);

  Serial.println("Start");

  /* Register the pop event callback function of the current button0 component. */
  buttonPlus.attachPush(buttonPlusPushCallback);

  /* Register the pop event callback function of the current button1 component. */
  buttonMinus.attachPush(buttonMinusPushCallback);

  dbSerialPrintln("Setup done");
}

void loop(void)
{
  nexLoop(nex_listen_list);
}

