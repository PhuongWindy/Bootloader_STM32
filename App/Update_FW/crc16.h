#ifndef CRC16_H
#define CRC16_H

#include <stddef.h>
#include <stdint.h>

class CRC16
{
public:
    CRC16();
    uint16_t crc16ProcessByte(uint8_t data);
    uint16_t crc16ProcessBuff(const char *data, size_t dataSize);
private:
    uint16_t crcPoly;
    uint16_t crcInit;
    uint16_t crc16;
};

#endif // CRC16_H
