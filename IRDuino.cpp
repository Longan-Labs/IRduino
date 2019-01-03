/*-------------------------------------------------------------------------- +
  IRduino.cpp
  2017 Copyright (c) Longan Labs.  All right reserved.
 
  Author: Stephen,stephen@longan-labs.cc
  
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
#include <Arduino.h>
#include <IRDuino.h>
#include <IRDuinoRecv.h>

#define PINIR               6

#define __DBG               0

void IRduino::begin()
{
    num_code= 0;

    Keyboard.begin();
    IR.Init(PINIR);
    
    for(int i=A0; i<=A5; i++)
    {
        pinMode(i, OUTPUT);
        digitalWrite(i, HIGH);                      // all led off
    }
    
    led(B1, 1);
    led(B2, 1);
}

// control led
void IRduino::led(int pin, int state)
{
    if(pin>A5 || pin<A0)return;                     // err pin
    
    int pin_off = (pin<=A2) ? 0 : 3;
    
    for(int i=A0+pin_off; i<=(A2+pin_off); i++)     // all led off in one side
    {
        digitalWrite(i, HIGH);
    }
    digitalWrite(pin, 1-state);
}

// all led off
void IRduino::all_led_off()
{
    for(int i=A0; i<=A5; i++)
    {
        digitalWrite(i, HIGH);
    }
}

// press a key, then release it
void IRduino::keyPressRelease(unsigned char keyNum)
{
    Keyboard.press(keyNum);
    delay(1);
    Keyboard.release(keyNum);
}

/*
 * enter a string
 */
void IRduino::printf(char *str)
{
    if(NULL == str)return;

    while(*str)
    {
        keyPressRelease(str[0]);
        str++;
    }

}

/*
 * find if this ir code was stored, if not return -1
 */
int IRduino::find_ir_code(int irCode)
{
    for(int i=0; i<num_code; i++)
    {
        if(irCode == ir_code[i])
        {
            return i;
        }
    }

    return -1;
}


/*
 * add an task
 */
bool IRduino::addItem(int irCode, void (*pfun)())
{
    ir_code[num_code]    = irCode;
    task_fun[num_code++] = pfun;
    // FIXME: undocumented symantics... asumming returning true means successful add
    return true;
}

/* process */
void IRduino::process()
{
    if(!isGetIrDta())return;


    int irCode = getIrDta();

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
    
    int task_loca = find_ir_code(irCode);
    
    if(task_loca >= 0)                  // find
    {
        Serial.print("task_loca = ");
        Serial.println(task_loca);
        
        led(G1, 1);
        led(G2, 1);
        delay(100);
        led(G1, 0);
        led(G2, 0);
        
        (task_fun[task_loca])();
    }
    else
    {
        Serial.println("can't find this ir code");
        led(R1, 1);
        led(R2, 1);
        delay(100);
        led(R1, 0);
        led(R2, 0);
    }
    
    Serial.println("+------------------------------------------------------+\r\n\r\n");
}



IRduino iRduino;
