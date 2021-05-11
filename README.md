# Longan Labs IRduino Library

[![Actions Status](https://github.com/arduino/arduino-cli-example/workflows/test/badge.svg)](https://github.com/arduino/arduino-cli-example/actions)
[![Spell Check](https://github.com/arduino/compile-sketches/workflows/Spell%20Check/badge.svg)](https://github.com/arduino/compile-sketches/actions?workflow=Spell+Check)
[![codecov](https://codecov.io/gh/arduino/compile-sketches/branch/main/graph/badge.svg?token=Uv6f1ebMZ4)](https://codecov.io/gh/arduino/compile-sketches)

[IRduino](https://www.longan-labs.cc/1040001.html) is a peripheral device that allows almost any IR signal to be translated into commands. It works on many platforms, including PC, Mac, Raspberry Pi, and even some cell phones. The infrared device can be anything from an old TV remote, to an IR mouse or keyboard.

Decades of consumer electronics have relied on infrared remote controls. The result is piles of disused IR remotes collecting dust in closets and storage bins around the world. Our goal is to give you the power to put some of those idle remotes back to work in creative and productive ways. Enter the IRduino.

IRduino is made up of an ATmega32U4 Microcontroller (MCU) and an SMD (Surface Mounted Device) IR receiver component. The design is simplified even further by including the USB contacts directly on the board - and unlike many products on the market, the board is thick enough to sit snugly in your USB port. To keep the device humanized (and humorous), a little robot is screen-printed on the reverse side. Just like any good robot, it’s got two programmable LEDs for eyes.

IRduino can be both practical and entertaining. It can serve as an interface to your single-board XBMC media center. You can use your remote for complete control of simple games, or to extend your capabilities for complex gaming. The device will let you use any normal remote as a special presentation device. Use IRduino as an easily accessible way to launch your favorite applications. Remotely shut down or reboot a computer with a push of a button.

## Features

* Arduino-compatible: IRduino comes with the Arduino Leonardo bootloader pre-installed on the board, which makes IRduino fully compatible with the Arduino IDE for programming.
* Compact: IRduino is only 19mm x 35mm, which is smaller than most USB flash sticks.
* Works with most remotes: We have designed a library that is compatible with about 95% of infrared remotes on the market, from air conditioning remotes, to TV remotes, to DVD remotes, to washing machine remotes.

## Installation

1. [Download the library](https://github.com/Longan-Labs/Serial_CAN_Arduino/archive/refs/heads/master.zip)
2. Extract the zip file
3. In the Arduino IDe, navigate to Sketch > Include Library > Add .ZIP Library

## Examples

here are many examples implemented in this library. One of the examples is below. You can find other examples [here](./examples)

```Cpp
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
```


## Respository Contents

* [**/examples**](./examples) - Example sketches for the library (.ino). Run these from the Arduino IDE.
* [**keywords.txt**](./keywords.txt) - Keywords from this library that will be highlighted in the Arduino IDE.
* [**library.properties**](./library.properties) - General library properties for the Arduino package manager.

## Get a Dev Board

If you need a Dev board, plese try,

- [IRduino](https://www.longan-labs.cc/1040001.html)


## License

```
MIT License

Copyright (c) 2018 @ Longan Labs

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```

## Contact us

If you have any question, please feel free to contact [support@longan-labs.cc](support@longan-labs.cc)


[![Analytics](https://ga-beacon.appspot.com/UA-101965714-1/IRduino)](https://github.com/igrigorik/ga-beacon)
