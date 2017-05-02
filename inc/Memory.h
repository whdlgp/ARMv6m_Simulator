/*
 * Memory.h
 *
 *  Created on: 2016. 12. 9.
 *      Author: ygcho
 */

#ifndef INC_MEMORY_H_
#define INC_MEMORY_H_

#include "ctocpp.h"

#define MEM_MAXSIZE 0x40000
#define MEM_BASE 0x00

class Memory
{
public :
    Memory()
    {
        instFileSize = 0;
        instFileName = "example00.bin";
        dumpFileName = "dump.txt";
    }

    uint32_t instFileSize;

    static Memory* getInstance() { return &memInst; }
    void init(char* binFIle, char* dumpFile);

    uint8_t readByte(uint32_t index);
    uint16_t read2Byte(uint32_t index);
    uint32_t read4Byte(uint32_t index);

    void writeByte(uint32_t index, uint8_t data);
    void write2Byte(uint32_t index, uint16_t data);
    void write4Byte(uint32_t index, uint32_t data);

    void dumpPrint();
private :
    static Memory memInst;

    uint8_t mem[MEM_MAXSIZE];
    const char* dumpFileName;
    const char* instFileName;
};

#endif /* INC_MEMORY_H_ */
