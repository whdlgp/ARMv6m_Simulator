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

/* LSR - Register (Logical Shift Right)
   Encoding: 010000 0011 Rm:3 Rdn:3 */
void test_lsrRegisterShiftValue1by1_CarryOutFromLowestBit()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 1);
    setRegisterValue(R7, 1);
    emitInstruction16("0100000011mmmddd", R0, R7);
    setExpectedXPSRflags("nZC");
    setExpectedRegisterValue(R7, 0);
}

void test_lsrRegisterShiftValue1by0_MinimumShift_CarryUnmodified()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    setRegisterValue(R7, 1);
    setRegisterValue(R0, 0);
    emitInstruction16("0100000011mmmddd", R0, R7);
    setExpectedXPSRflags("nzc");
    setExpectedRegisterValue(R7, 1);
}

void test_lsrRegisterShiftValue2by1_NoCarry()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, 2);
    setRegisterValue(R3, 1);
    emitInstruction16("0100000011mmmddd", R3, R2);
    setExpectedXPSRflags("nzc");
    setExpectedRegisterValue(R2, 2 >> 1);
}

void test_lsrRegisterShiftNegativeValueBy31()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, -1);
    setRegisterValue(R3, 31);
    emitInstruction16("0100000011mmmddd", R3, R2);
    setExpectedXPSRflags("nzC");
    setExpectedRegisterValue(R2, -1U >> 31);
}

void test_lsrRegisterShiftNegativeValueBy32_CarryOutFromHighestBit()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 0x80000000);
    setRegisterValue(R7, 32);
    emitInstruction16("0100000011mmmddd", R7, R0);
    setExpectedXPSRflags("nZC");
    setExpectedRegisterValue(R0, 0);
}

void test_lsrRegisterShiftNegativeValueBy33_ResultIsZero_CarryClear()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, -1);
    setRegisterValue(R3, 33);
    emitInstruction16("0100000011mmmddd", R3, R2);
    setExpectedXPSRflags("nZc");
    setExpectedRegisterValue(R2, 0);
}

void test_lsrRegisterMaximumShiftOf255_ResultIsZero_CarryClear()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, -1);
    setRegisterValue(R3, 255);
    emitInstruction16("0100000011mmmddd", R3, R2);
    setExpectedXPSRflags("nZc");
    setExpectedRegisterValue(R2, 0);
}

void test_lsrRegisterShiftOf256_ShouldBeTreatedAs0Shift_CarryUnmodified()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    setRegisterValue(R0, -1);
    setRegisterValue(R7, 256);
    emitInstruction16("0100000011mmmddd", R7, R0);
    setExpectedXPSRflags("NzC");
    setExpectedRegisterValue(R0, -1);
}
