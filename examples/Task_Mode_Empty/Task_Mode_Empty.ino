/*-------------------------------------------------------------------------- +
  Task_Mode_Empty.ino
  2017 Copyright (c) Longan Labs.  All right reserved.
 
  Author: Stephen,stephen@longan-labs.cc
  
  Function - 
  It's an empty task mode demo.
  You can add your task here
  Of curse you should get the IR code first - via the Get_IR_Code example
  
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

/*
 * define your IR code here
 */

#define IR_CODE_XXX   0x10

void setup()
{
    iRduino.begin();
    Serial.begin(115200);
    
/*
 * Add Item here
 */
    iRduino.addItem(IR_CODE_XXX, task_xxx);
    
}


void loop()
{
    iRduino.process();
}


/*
 * Add your task here
 */
void task_xxx()
{
    // add function
}

// END FILE