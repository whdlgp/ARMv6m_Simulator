/*  Copyright (C) 2017  Andrea Barisani (https://github.com/abarisani)

    Adapted from https://github.com/adamgreen/pinkySim testsuite
    Copyright (C) 2014  Adam Green (https://github.com/adamgreen);

    This program is free software; you can redistribute it and/or
    modify it under the terms of the GNU General Public License
    as published by the Free Software Foundation; either version 2
    of the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
*/

#include <stdarg.h>
#include <assert.h>

#include "UserInterface.h"
#include "Instruction.h"
#include "Memory.h"
#include "Register.h"
#include "Test.h"

static UserInterface* UI = UserInterface::getInstance();
static Memory* mem = Memory::getInstance();
static Register* reg = Register::getInstance();
static Instruction* ist = Instruction::getInstance();

void emitInstruction16Varg(const char* pEncoding, va_list valist)
{
    uint16_t    instr = 0;
    size_t      i = 0;
    char        last = '\0';
    const char* p;
    struct Field
    {
        uint32_t value;
        char     c;
    } fields[6];

    assert (16 == strlen(pEncoding));
    memset(fields, 0, sizeof(fields));

    // Go through pEncoding from left to right and find all fields to be inserted.
    p = pEncoding;
    while (*p)
    {
        char c = *p++;

        if (c != '1' && c != '0' && c != last)
        {
            // Determine if we already saw this field earlier.
            bool found = false;
            for (size_t j = 0 ; j < i ; j++)
            {
                if (fields[j].c == c)
                    found = true;
            }

            // If this is the first time we have seen the field, then save its value in fields array.
            if (!found)
            {
                assert (i < sizeof(fields)/sizeof(fields[0]));

                fields[i].value = va_arg(valist, uint32_t);
                fields[i].c = c;
                last = c;
                i++;
            }
        }
    }

    // Go through pEncoding again from right to left and insert field bits.
    p = pEncoding + 15;
    while (p >= pEncoding)
    {
        char c = *p--;

        instr >>= 1;

        if (c == '1')
        {
            instr |= (1 << 15);
        }
        else if (c == '0')
        {
            instr |= (0 << 15);
        }
        else
        {
            size_t j;
            for (j = 0 ; j < i ; j++)
            {
                if (fields[j].c == c)
                    break;
            }
            assert (j != i);

            instr |= (fields[j].value & 1) << 15;
            fields[j].value >>= 1;
        }
    }

    mem->write2Byte(reg->R[PC], instr);
    ist->decode();
}

void emitInstruction16(const char* pEncoding, ...)
{
    va_list     valist;

    va_start(valist, pEncoding);
    emitInstruction16Varg(pEncoding, valist);
    va_end(valist);
}

void setExpectedXPSRflags(const char* pExpectedFlags)
{
    int ret;

    // Remember what expected APSR flags should be after instruction execution and flip initial flag state to make
    // sure that simular correctly flips the state and doesn't just get lucky to match a pre-existing condition.
    while (*pExpectedFlags)
    {
        switch (*pExpectedFlags)
        {
        case 'n':
            ret = reg->PSR[psrN] == 0;
            break;
        case 'N':
            ret = reg->PSR[psrN] == 1;
            break;
        case 'z':
            ret = reg->PSR[psrZ] == 0;
            break;
        case 'Z':
            ret = reg->PSR[psrZ] == 1;
            break;
        case 'c':
            ret = reg->PSR[psrC] == 0;
            break;
        case 'C':
            ret = reg->PSR[psrC] == 1;
            break;
        case 'v':
            ret = reg->PSR[psrV] == 0;
            break;
        case 'V':
            ret = reg->PSR[psrV] == 1;
            break;
        }

        if (!ret)
        {
            UI->memPrint();
            printf(" FAIL: mismatch for %c flag!\n", *pExpectedFlags);
            exit(1);
        }

        pExpectedFlags++;
    }
}

void setExpectedRegisterValue(int index, uint32_t expectedValue)
{
    if (reg->R[index] != expectedValue) {
        UI->memPrint();
        printf(" FAIL: mismatch for reg[%d ] != 0x%08x\n", index, expectedValue);
        exit(1);
    }
}

void setRegisterValue(int index, uint32_t value)
{
    reg->R[index] = value;
}

void setInitialRegisterValues()
{
    reg->R[PC] = INITIAL_PC;
    reg->R[SP] = INITIAL_SP;
    reg->R[LR] = INITIAL_LR;

    /* Randomly initialize each APSR flag to help verify that the simulator doesn't clear/set a bit that the
       specification indicates shouldn't be modified by an instruction. */
    for (int i = 0 ; i < 4 ; i++)
    {
        int setOrClear = rand() & 1;
        reg->PSR[i] = setOrClear;
    }

    uint32_t value = 0;

    /* Place 0x11111111 in R1, 0x22222222 in R2, etc. */
    for (int i = 0 ; i < 13 ; i++)
        {
            setRegisterValue(i, value);
            setExpectedRegisterValue(i, value);
            value += 0x11111111;
        }
}

void clearCarry()
{
    reg->PSR[psrC] = 0;
}

void setCarry()
{
    reg->PSR[psrC] = 1;
}

void clearZero()
{
    reg->PSR[psrZ] = 0;
}

void setZero()
{
    reg->PSR[psrZ] = 1;
}

void clearNegative()
{
    reg->PSR[psrN] = 0;
}

void setNegative()
{
    reg->PSR[psrN] = 1;
}

void clearOverflow()
{
    reg->PSR[psrV] = 0;
}

void setOverflow()
{
    reg->PSR[psrV] = 1;
}
