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

uint32_t Register::regRead(uint8_t index)
{
    uint32_t retval;

    if(index == PC)
        retval = this->R[PC]+4;
    else
        retval = this->R[index];

    return retval;
}

void Register::regWrite(uint8_t index, uint32_t val)
{
    this->R[index] = val;
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

void Register::updatePC(uint8_t instLength)
{
    //If Branch instructions throws value, than use that value.
    if(throwCheck())
    {
        pcWrite(throwAddr);
        throwBit = 0;
    }
    //Check if ADD or MOV instruction change PC directly
    else if(changePCCheck())
    {
        PCdirectChange = 0;
    }
    else
    {
        //if Branch or ADD, MOV instructions doesn't change PC,
        //than increase PC depending on the length of the instruction.
        if(instLength == 16)
            R[PC] += 2;
        else if(instLength == 32)
            R[PC] += 4;
    }

    //Finally, the PC value must be aligned to match the instruction length.
    R[PC] = R[PC] & 0xfffffffe;
}

void Register::changePC()
{
    this->PCdirectChange = 1;
}

uint8_t Register::changePCCheck()
{
    return this->PCdirectChange ? 1 : 0;
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
            if((PSR[psrC] == 0) || (PSR[psrZ] == 1))
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
            if((PSR[psrZ] == 1) || (PSR[psrN] != PSR[psrV]))
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
