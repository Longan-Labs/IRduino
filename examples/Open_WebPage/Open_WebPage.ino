/*-------------------------------------------------------------------------- +
  Open_WebPage.ino
  2017 Copyright (c) Longan Labs.  All right reserved.
 
  Author: Stephen,stephen@longan-labs.cc
  
  Function - 
  
  This demo will open a web page when you insert your IRDuino to a PC
  This demo can only support Windows, not for linux and osx.
  
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

void openWebPage()
{
    iRduino.press(KEY_RIGHT_GUI);           // window
    iRduino.press('r');                     // win+R, you know that if you use a Windows system
    
    delay(200);
    iRduino.releaseAll();
    
    delay(100);
    
    iRduino.printf("iexplore.exe ");
    delay(100);
    iRduino.printf("http://docs.longan-labs.cc/IRduino/");
    
    delay(100);
    iRduino.keyPressRelease(KEY_RETURN);

}

void setup()
{
    iRduino.begin();
    
    delay(1000);
    openWebPage();
}


void loop()
{
    //iRduino.process();
}

// END FILE