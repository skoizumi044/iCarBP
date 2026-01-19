/**
 * @file HardwareSerial.cpp
 * @brief HardwareSerial for RX
 * @author KSEII T.Terazawa
 * @copyright 2020 Kernel Software Engineering
 */


#include <Std_Types.h>
#include <BSW/IODrivers/Sci.h>

#include "HardwareSerial.h"


HardwareSerial::HardwareSerial(void)
{
    peekedData = -1;
}


void HardwareSerial::begin(unsigned long baud)
{
    Sci_Init(baud);
}


void HardwareSerial::end()
{
    Sci_DeInit();
}


int HardwareSerial::available(void)
{
  return ((int)((uint32_t)Sci_GetRecvBytes()));
}


int HardwareSerial::peek(void)
{
    uint8_t rxBuffer;
    
    /* peeked? */
    if (peekedData != -1)
    {
    }
    /* read from fifo */
    else if (Sci_Recv1BAsync(&rxBuffer) != 0)
    {
        /* peek data */
        peekedData = (int)((uint32_t)rxBuffer);
    }
    else
    {
        /* nothing to do */
    }
    
    return (peekedData);
}


int HardwareSerial::read(void)
{
    uint8_t rxBuffer;
    
    /* peeked? */
    if (peekedData != -1)
    {
        rxBuffer = (uint8_t)peekedData;
        
        /* peeked data = unavailable */
        peekedData = -1;
    }
    /* read from fifo */
    else if (Sci_Recv1BAsync(&rxBuffer) == 0)
    {
        return (-1);
    }
    else
    {
        /* nothing to do */
    }
    
    return ((int)((uint32_t)rxBuffer));
}


int HardwareSerial::availableForWrite(void)
{
    return ((int)((uint32_t)Sci_GetSendBufferRemain()));
}


void HardwareSerial::flush()
{
    Sci_WaitForSendEnd();
}


size_t HardwareSerial::write(uint8_t c)
{
    /* try to send */
    while (Sci_Send1BAsync(c) == 0)
    {
    }

    return (1);
}


HardwareSerial Serial;
