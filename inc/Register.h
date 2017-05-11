/*
 * Register.h
 *
 *  Created on: 2016. 12. 9.
 *      Author: ygcho
 */

#ifndef INC_REGISTER_H_
#define INC_REGISTER_H_

#include "ctocpp.h"

enum
{
    SP = 13,
    LR,
    PC,

    psrN = 0,
    psrZ,
    psrC,
    psrV,

    REG_SIZE = 16,
    PSR_SIZE = 4,
};

class Register
{
public :
    Register()
    {
        throwBit = 0;
        throwAddr = 0;
    }
    static Register* getInstance() { return &regInst; }

    uint32_t R[REG_SIZE];
    uint32_t PSR[PSR_SIZE];

    void init();

    void regWriteWithPCcheck(uint8_t regNum,uint32_t val);
    void pcWrite(uint32_t addr);

    void throwPC(uint32_t addr);
    void updatePC();

    uint8_t checkCond(uint8_t cond);
private :
    static Register regInst;

    //for PC register handle.
    uint8_t throwBit;
    uint32_t throwAddr;
    uint8_t throwCheck();
};



#endif /* INC_REGISTER_H_ */
