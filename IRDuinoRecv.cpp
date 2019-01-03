/*
 * IRremote
 * Version 0.11 August, 2009
 * Copyright 2009 Ken Shirriff
 * For details, see http://arcfn.com/2009/08/multi-protocol-infrared-remote-library.html
 *
 * Modified by Paul Stoffregen <paul@pjrc.com> to support other boards and timers
 * Modified  by Mitra Ardron <mitra@mitra.biz>
 * Added Sanyo and Mitsubishi controllers
 * Modified Sony to spot the repeat codes that some Sony's send
 *
 * Modifier by
 * Interrupt code based on NECIRrcv by Joe Knapp
 * http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1210243556
 * Also influenced by http://zovirl.com/2008/11/12/building-a-universal-remote-with-an-arduino/
 *
 * Modified by Llama, reeed1024@gmail.com
 * Receive Only One Byte
 *
 */
#include "IRDuinoRecvInt.h"
#include "IRDuinoRecv.h"

// Provides ISR
#include <avr/interrupt.h>


volatile irparams_t irparams;

unsigned char queue_ir[16];
unsigned char queue_index = 0;
    
void clearQueueIndex()
{
#if __DEBUG
    Serial.println("clear index now");
#endif
    queue_index = 0;
}

void pushQueue(unsigned char dta)                           // push data to queue_ir
{
    queue_ir[queue_index++] = dta;
    
    queue_index = queue_index>15 ? 0 : queue_index;
}

unsigned char IRSendRev::isDtaQueue()                       // if Queue get data
{
    return 1;
}

unsigned char IRSendRev::RecvQueue(int nShort)              // get the byte from queue
{
    unsigned char dtaGet = 0;
    nShort*=3;
    
    for(int i=0; i<8; i++)
    {
        if((queue_ir[2*i] + queue_ir[2*i+1]) > nShort)
        {
            dtaGet |= 0x01;

        }

        dtaGet = dtaGet<<1;
    }
    oneByte = dtaGet;
    return dtaGet;
}

void IRSendRev::Init(int revPin)
{
    irparams.recvpin    = revPin;
    enableIRIn(); // Start the receiver
    delay(20);
    Clear();
}

void IRSendRev::Init()
{
    delay(20);
    Clear();
}

// initialization
void IRSendRev::enableIRIn() 
{
    cli();
    // setup pulse clock timer interrupt
    // Prescale /8 (16M/8 = 0.5 microseconds per tick)
    // Therefore, the timer interval can range from 0.5 to 128 microseconds
    // depending on the reset value (255 to 0)
    TIMER_CONFIG_NORMAL();

    //Timer2 Overflow Interrupt Enable
    TIMER_ENABLE_INTR;

    TIMER_RESET;

    sei();  // enable interrupts

    // initialize state machine variables
    irparams.rcvstate = STATE_IDLE;
    irparams.rawlen = 0;

    // set pin modes
    pinMode(irparams.recvpin, INPUT);
}

// TIMER2 interrupt code to collect raw data.
// Widths of alternating SPACE, MARK are recorded in rawbuf.
// Recorded in ticks of 50 microseconds.
// rawlen counts the number of entries recorded so far.
// First entry is the SPACE between transmissions.
// As soon as a SPACE gets long, ready is set, state switches to IDLE, timing of SPACE continues.
// As soon as first MARK arrives, gap width is recorded, ready is cleared, and new logging starts

ISR(TIMER_INTR_NAME)
{
    TIMER_RESET;

    uint8_t irdata = (uint8_t)digitalRead(irparams.recvpin);

    irparams.timer++; // One more 50us tick

    switch(irparams.rcvstate) 
    {
        case STATE_IDLE: // In the middle of a gap
        if (irdata == MARK) 
        {
            if (irparams.timer < GAP_TICKS) 
            {
                // Not big enough to be a gap.
                irparams.timer = 0;
            }
            else {
                // gap just ended, record duration and start recording transmission
                irparams.rawlen = 0;
                irparams.rawlen++;
                clearQueueIndex();
                
                irparams.timer = 0;
                irparams.rcvstate = STATE_MARK;
                
            }
        }
        break;
        case STATE_MARK: // timing MARK
        if (irdata == SPACE) 
        {   // MARK ended, record time
            irparams.rawlen++;
            pushQueue(irparams.timer);
            
            irparams.timer = 0;
            irparams.rcvstate = STATE_SPACE;
        }
        break;
        case STATE_SPACE: // timing SPACE
        if (irdata == MARK) 
        { // SPACE just ended, record it
            irparams.rawlen++;
            pushQueue(irparams.timer);
            irparams.timer = 0;
            irparams.rcvstate = STATE_MARK;
        }
        else 
        { // SPACE
            if (irparams.timer > GAP_TICKS) 
            {
                // big SPACE, indicates gap between codes
                // Mark current code as ready for processing
                // Switch to STOP
                // Don't reset timer; keep counting space width
                irparams.rcvstate = STATE_STOP;
            }
        }
        break;
        case STATE_STOP:            // waiting, measuring gap
        if (irdata == MARK)         // reset gap timer
        { 
            irparams.timer = 0;
        }
        break;
    }
}

void IRSendRev::Clear() 
{
    irparams.rcvstate = STATE_IDLE;
    irparams.rawlen = 0;
}

// Decodes the received IR message
// Returns 0 if no data ready, 1 if data ready.
// Results of decoding are stored in results
int IRSendRev::decode(decode_results *results) 
{
    //results->rawbuf = irparams.rawbuf;
    results->rawlen = irparams.rawlen;
    if (irparams.rcvstate != STATE_STOP) 
    {
        return ERR;
    }
    // Throw away and start over
    Clear();
    return 1;
}

int IRSendRev::Recv()
{
    int count       = results.rawlen;
    
    int nshort = 1000;
    int nlong  = 0;
    // count nshort here
    
    for(int i=0; i<16; i++)
    {
        if(queue_ir[i] < nshort)
        {
            nshort = queue_ir[i];
        }
        if(queue_ir[i] > nlong)
        {
            nlong = queue_ir[i];
        }
    }
    
    if(count > 30)
    {
        RecvQueue(nshort);
        Clear();
        return oneByte;
    }

    Clear(); // Receive the next value
    
    return -1;
}

//if get some data from IR
unsigned char IRSendRev::IsDta()
{
    if(decode(&results))
    {
        int count       = results.rawlen;
        
        if(count < 32/* || (count -4)%8 != 0*/)
        {
#if __DEBUG
            Serial.print("IR GET BAD DATA!\r\n");
#endif
            Clear();        // Receive the next value
            return 0;
        }

        return 1;
    }
    
    return 0;
}

IRSendRev IR;
