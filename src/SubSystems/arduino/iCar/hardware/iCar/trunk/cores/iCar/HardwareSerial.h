/**
 * @file HardwareSerial.h
 * @brief HardwareSerial for RX
 * @author KSEII T.Terazawa
 * @copyright 2020 Kernel Software Engineering
 */


#ifndef HardwareSerial_h
#define HardwareSerial_h

#include "Stream.h"

class HardwareSerial : public Stream
{
protected:
    int peekedData;
    
public:
    HardwareSerial(void);
    void begin(unsigned long baud);
    void end();
    virtual int available(void);
    virtual int peek(void);
    virtual int read(void);
    virtual int availableForWrite(void);
    virtual void flush(void);
    virtual size_t write(uint8_t);
    operator bool() { return true; }
};

extern HardwareSerial Serial;

#endif
