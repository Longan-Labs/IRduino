/*-------------------------------------------------------------------------- +
  Task_Mode_UDLR.ino
  2017 Copyright (c) Longan Labs.  All right reserved.
 
  Author: Stephen,stephen@longan-labs.cc
  
  Function - 
  It's Demo will access press up, down, left and right via 4 ir remote key.
  
  -------------------
  The MIT License (MIT)

  Copyright (c) 2017 Longan Labs
 
  Permission is hereby granted, free of charge, to any person obtaining a copy
  of this software and associated documentation files (the "Software"), to deal
  in the Software without restriction, including without limitation the rights
  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
  copies of the Software, and to permit persons to whom the Software is
  furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included in
  all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
  THE SOFTWARE.
-----------------------------------------------------------------------------*/

#include <IRDuino.h>
     
// IR CODE DEFINE
#define IR_CODE_UP          0xce
#define IR_CODE_DOWN        0xe6
#define IR_CODE_LEFT        0x56
#define IR_CODE_RIGHT       0x96
#define IR_CODE_SPACE       0xd6
     
void setup()
{
    iRduino.begin();
    Serial.begin(115200);
    
    // add task item
    iRduino.addItem(IR_CODE_UP, task_up);
    iRduino.addItem(IR_CODE_DOWN, task_down);
    iRduino.addItem(IR_CODE_LEFT, task_left);
    iRduino.addItem(IR_CODE_RIGHT, task_right);
    iRduino.addItem(IR_CODE_SPACE, task_space);
}


void loop()
{
    iRduino.process();
}

// add task
void task_up()
{
    iRduino.keyPressRelease(KEY_UP_ARROW);
}

void task_down()
{  
    iRduino.keyPressRelease(KEY_DOWN_ARROW);
}

void task_left()
{
    iRduino.keyPressRelease(KEY_LEFT_ARROW);
}

void task_right()
{
    iRduino.keyPressRelease(KEY_RIGHT_ARROW);
}

void task_space()
{
    iRduino.keyPressRelease(KEY_SPACE);
}

// END FILE