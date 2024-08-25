#include "crc16.h"

CRC16::CRC16() {
    crcPoly = 0x1021;
    crcInit = 0x0000;
    crc16 = crcInit;
}

uint16_t CRC16::crc16ProcessByte(uint8_t data) {
    uint8_t i;

    crc16 = crc16 ^ ((uint16_t)data << 8);
    for (uint8_t i = 0; i < 8; i++) {
        if (crc16 & 0x8000) {
            crc16 = (crc16 << 1) ^ crcPoly;
        } else {
            crc16 <<= 1;
        }
    }
    return crc16;
}

uint16_t CRC16::crc16ProcessBuff(const char *data, size_t dataSize) {
    while (dataSize --) {
        crc16ProcessByte(*(data++));
    }
    return crc16;
}
