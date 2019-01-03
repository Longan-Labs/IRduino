/*-------------------------------------------------------------------------- +
  GetIRCode.ino
  2017 Copyright (c) Longan Labs.  All right reserved.
 
  Author: Stephen,stephen@longan-labs.cc
  
  Function - 
  Insert your IRDuino, upload the code, then open Serial monitor,
  Choose baudrate 115200, then point your IR remote to IRduino,
  Press any key, you will get a Byte data. This is the code.
  
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

#define INFO_STR "This is an demo of IRDuino - Get IR Code\r\nMore dtails refer to https://github.com/Longan-Labs/IRduino\r\n\r\n"


void setup()
{
    Serial.begin(115200);
    while(!Serial);
    Serial.println(INFO_STR);
    
    iRduino.begin();
}

void loop()
{
    if(iRduino.isGetIrDta())                              // get IR data
    {
        int irCode = iRduino.getIrDta();
        
        Serial.println("+------------------------------------------------------+");
        if(irCode<=0)
        {
            Serial.println("get error code, try again");
        }
        else
        {
            Serial.print("get IR Code: 0x");
            Serial.println(irCode, HEX);
        }
        Serial.println("+------------------------------------------------------+\r\n\r\n");
    }
}

// END FILE
