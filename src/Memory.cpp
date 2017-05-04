/*
 * Memory.cpp
 *
 *  Created on: 2016. 12. 9.
 *      Author: ygcho
 */

#include "Memory.h"

Memory Memory::memInst;

void Memory::init(char* binFile, char* dumpFile)
{
    FILE* bf;
    int fileSize;

    this->instFileName = binFile;
    this->dumpFileName = dumpFile;

    if((bf = fopen(binFile, "rb")) == NULL)
    {
        printf("file open error\n");
    }

    fseek(bf, 0, SEEK_END);
    fileSize = ftell(bf);
    fseek(bf, 0, SEEK_SET);

    fread(mem, 1, fileSize, bf);

    instFileSize = fileSize;

    fclose(bf);
}

uint8_t Memory::readByte(uint32_t index)
{
    index = relocateSRAM(index);

    return this->mem[index];
}

uint16_t Memory::read2Byte(uint32_t index)
{
    index = relocateSRAM(index);

    return this->mem[index]
           | (this->mem[index + 1] << 8);
}

uint32_t Memory::read4Byte(uint32_t index)
{
    index = relocateSRAM(index);

    return  this->mem[index]
            | (this->mem[index + 1] << 8)
            | (this->mem[index + 2] << 16)
            | (this->mem[index + 3] << 24);
}

void Memory::writeByte(uint32_t index, uint8_t data)
{
    index = relocateSRAM(index);

    this->mem[index] = data;
}

void Memory::write2Byte(uint32_t index, uint16_t data)
{
    index = relocateSRAM(index);

    this->mem[index] = data & 0xff;
    this->mem[index + 1] = (data >> 8) & 0xff;
}

void Memory::write4Byte(uint32_t index, uint32_t data)
{
    index = relocateSRAM(index);

    this->mem[index] = data & 0xff;
    this->mem[index + 1] = (data >> 8) & 0xff;
    this->mem[index + 2] = (data >> 16) & 0xff;
    this->mem[index + 3] = (data >> 24) & 0xff;
}

uint32_t Memory::relocateSRAM(uint32_t index)
{
    if (index >= SRAM_BASE)
    {
        index = index - SRAM_BASE + MEM_MAXSIZE;
    }

    return index;
}

void Memory::dumpPrint()
{
    FILE* df;
    uint32_t i;

    if((df = fopen(this->dumpFileName, "wb")) == NULL)
    {
        printf("file open error\n");
    }

    for(i = 0; i < MEM_MAXSIZE; i += 4)
    {
        fprintf(df, "%02x : %02x_%02x_%02x_%02x\n", i+MEM_BASE, mem[i+3]
                                                              , mem[i+2]
                                                              , mem[i+1]
                                                              , mem[i]);
    }

    fclose(df);
}
