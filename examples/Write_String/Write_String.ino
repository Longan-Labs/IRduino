/*-------------------------------------------------------------------------- +
  Write_String.ino
  2017 Copyright (c) Longan Labs.  All right reserved.
 
  Author: Stephen,stephen@longan-labs.cc
  
  Function - 
  Logout enter key in Window system.
  You sholed get a your ir remote key by the demo Get_IR_Code
  
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

#define IRCODE_LOGOUT       0xEA
#define IRCODE_ENTERKEY     0x72

#define WINDOWS_KEY         "123456"

void setup()
{
    iRduino.begin();                            // initialize
}

void loop()
{
    if(iRduino.isGetIrDta())                    // get IR data
    {
        int irCode = iRduino.getIrDta();
        irCodeProcess(irCode);
    }
}

/*
 * process the ir command here
 */
void irCodeProcess(int irCode)
{
    if(irCode<=0)return;                        // error code
    
    switch(irCode)
    {
        case IRCODE_LOGOUT:                     // log out
        
        task_logout();
        
        break;
        
        case IRCODE_ENTERKEY:
        
        task_enterKey();

        default:;
    }
}


/*
 * Logout of windows
 */
void task_logout()
{
    iRduino.press(KEY_LEFT_CTRL);
    iRduino.press(KEY_LEFT_ALT);
    iRduino.press(KEY_DELETE);                  // Ctrl+Alt+Delete
    
    delay(500);                                 // delay 500ms

    iRduino.releaseAll();                       // release All

    iRduino.press(KEY_LEFT_ALT);           
    iRduino.press('k');                         // Alt+k

    delay(100);
    iRduino.releaseAll();                       // release All
}

/*
 * Enter Key
 */
void task_enterKey()
{
    iRduino.keyPressRelease(KEY_RETURN);        // press enter
    delay(500);
    iRduino.printf(WINDOWS_KEY);           // enter key
    iRduino.keyPressRelease(KEY_RETURN);        // release enter
}

// END FILE