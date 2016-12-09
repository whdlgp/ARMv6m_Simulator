/*
 * Register.cpp
 *
 *  Created on: 2016. 12. 9.
 *      Author: ygcho
 */

#include "Register.h"
#include "Memory.h"

Register Register::regInst;

void Register::init()
{
    Memory* mem = Memory::getInstance();
    uint8_t i; //for loop count

    //stack pointer initialize
    R[SP] = mem->read4Byte(0);

    //PC initialize
    R[PC] = mem->read4Byte(4) & 0xfffffffe; // Since the LSB is fixed at 0bit
    R[LR] = 0xffffffff;

    //arguments, preserved, scratch initialize
    for(i = 0; i < 13; i++)
        R[i] = 0;

    //NZCV initialize
    for(i = 0; i < 4; i++)
        PSR[i] = 0;
}

void Register::pcWrite(uint32_t addr)
{
    R[PC] = addr & 0xfffffffe;
}

void Register::throwPC(uint32_t addr)
{
    throwBit = 1;
    throwAddr = addr;
}

void Register::updatePC()
{
    if(throwCheck())
    {
        pcWrite(throwAddr);
        throwBit = 0;
    }
}

uint8_t Register::throwCheck()
{
    return throwBit ? 1 : 0;
}

uint8_t Register::checkCond(uint8_t cond)
{
    uint8_t ret = 0;

    switch(cond)
    {
        case 0 :
            ret = PSR[psrZ] ? 1 : 0;
            break;
        case 1 :
            ret = PSR[psrZ] ? 0 : 1;
            break;
        case 2 :
            ret = PSR[psrC] ? 1 : 0;
            break;
        case 3 :
            ret = PSR[psrC] ? 0 : 1;
            break;
        case 4 :
            ret = PSR[psrN] ? 1 : 0;
            break;
        case 5 :
            ret = PSR[psrN] ? 0 : 1;
            break;
        case 6 :
            ret = PSR[psrV] ? 1 : 0;
            break;
        case 7 :
            ret = PSR[psrV] ? 0 : 1;
            break;
        case 8 :
            if((PSR[psrC] == 1) && (PSR[psrZ] == 0))
                ret = 1;
            else
                ret = 0;
            break;
        case 9 :
            if((PSR[psrC] == 0) && (PSR[psrZ] == 1))
                ret = 1;
            else
                ret = 0;
            break;
        case 10 :
            if(PSR[psrN] == PSR[psrV])
               ret = 1;
            else
               ret = 0;
            break;
        case 11 :
            if(PSR[psrN] != PSR[psrV])
               ret = 1;
            else
               ret = 0;
            break;
        case 12 :
            if((PSR[psrZ] == 0) && (PSR[psrN] == PSR[psrV]))
                ret = 1;
            else
                ret = 0;
            break;
        case 13 :
            if((PSR[psrZ] == 1) && (PSR[psrN] != PSR[psrV]))
                ret = 1;
            else
                ret = 0;
            break;
        case 14 :
                ret = 1;
            break;
        default :
            break;
    }

    return ret;
}
