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

#include "Test.h"

// Immediate values used for shift amount in tests.
#define IMM_1  1
#define IMM_32 0

/* LSR - Immediate (Logical Shift Right)
   Encoding: 000 01 imm:5 Rm:3 Rd:3 */
void test_lsrImmediateR2by1toR0()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("00001iiiiimmmddd", IMM_1, R2, R0);
    setExpectedXPSRflags("nzc");
    setExpectedRegisterValue(R0, 0x22222222U >> 1);
}

void test_lsrImmediateR7by32toR0_ZeroResult()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("00001iiiiimmmddd", IMM_32, R7, R0);
    setExpectedXPSRflags("nZc");
    setExpectedRegisterValue(R0, 0x0);
}

void test_lsrImmediateR1by1toR7_CarryOut()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("00001iiiiimmmddd", IMM_1, R1, R7);
    setExpectedXPSRflags("nzC");
    setExpectedRegisterValue(R7, 0x11111111U >> 1);
}

void test_lsrImmediateR0by32_CarryOutAndIsZero()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 0x80000000U);
    emitInstruction16("00001iiiiimmmddd", IMM_32, R0, R0);
    setExpectedXPSRflags("nZC");
    setExpectedRegisterValue(R0, 0U);
}

// Can't generate a negative result as smallest shift is 1, meaning at least one 0 is shifted in from left.
