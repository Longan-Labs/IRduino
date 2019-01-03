/*
 * IRremote
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * For details, see http://arcfn.com/2009/08/multi-protocol-infrared-remote-library.htm http://arcfn.com
 * Edited by Mitra to add new controller SANYO
 *
 * Modified by Stephen (stephen@longan-labs.cc)
 * 2014-6-24
 *
 * change log:
 * - recv only the last byte
 *
 * Interrupt code based on NECIRrcv by Joe Knapp
 * http://www.arduino.cc/cgi-bin/yabb2/YaBB.pl?num=1210243556
 * Also influenced by http://zovirl.com/2008/11/12/building-a-universal-remote-with-an-arduino/
 *
 * JVC and Panasonic protocol added by Kristian Lauszus (Thanks to zenwheel and other people at the original blog post)
 *
 * Modified by Llama, reeed1024@gmail.com
 * Receive Only One Byte
 */

#ifndef __IRDUINORECV_H__
#define __IRDUINORECV_H__

// len, start_H, start_L, nshort, nlong, data_len, data[data_len]....
#define D_LEN       0
#define D_STARTH    1
#define D_STARTL    2
#define D_SHORT     3
#define D_LONG      4
#define D_DATALEN   5
#define D_DATA      6


#define USECPERTICK     50          // microseconds per clock interrupt tick

// Marks tend to be 100us too long, and spaces 100us too short
// when received due to sensor lag.
#define MARK_EXCESS 100

#define __DEBUG     0

// Results returned from the decoder
class decode_results {

    public:
    volatile unsigned int *rawbuf; // Raw intervals in .5 us ticks
    int rawlen;           // Number of records in rawbuf.
};

// main class for receiving IR
class IRSendRev
{
private:

    decode_results results;
    
    unsigned char oneByte;

    //**************************rev**********************************
    
private:

    int decode(decode_results *results);
    void enableIRIn();
    
public:


    void Init(int revPin);                          // init
    void Init();
    int Recv();     // 
    unsigned char IsDta();                          // if IR get data

    
    unsigned char isDtaQueue();                     // if Queue get data

    unsigned char RecvQueue(int nShort);            // get the byte from queue
    
    unsigned char RecvQueue()
    {
        return oneByte;
    }

    void Clear();                                   // clear IR data

};

extern IRSendRev IR;

#endif
