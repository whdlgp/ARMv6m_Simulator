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

/* ROR - Register (ROtate Right)
   Encoding: 010000 0111 Rm:3 Rdn:3 */
void test_rorRegisterRotate1by1_CarryOutFromLowestBit()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 1);
    setRegisterValue(R7, 1);
    emitInstruction16("0100000111mmmddd", R0, R7);
    setExpectedXPSRflags("NzC");
    setExpectedRegisterValue(R7, 0x80000000);
}

void test_rorRegisterRotate1by0_MinimumShift_CarryUnmodified()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 1);
    setRegisterValue(R7, 0);
    emitInstruction16("0100000111mmmddd", R7, R0);
    setExpectedXPSRflags("nz");
    setExpectedRegisterValue(R0, 1);
}

void test_rorRegisterRotate2by1_NoCarry()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, 2);
    setRegisterValue(R3, 1);
    emitInstruction16("0100000111mmmddd", R3, R2);
    setExpectedXPSRflags("nzc");
    setExpectedRegisterValue(R2, 2 >> 1);
}

void test_rorRegisterRotate16Bits()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, 0x12345678);
    setRegisterValue(R3, 16);
    emitInstruction16("0100000111mmmddd", R3, R2);
    setExpectedXPSRflags("nzc");
    setExpectedRegisterValue(R2, 0x56781234);
}

void test_rorRegisterRotateWithShiftOf31()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, 0x80000000);
    setRegisterValue(R3, 31);
    emitInstruction16("0100000111mmmddd", R3, R2);
    setExpectedXPSRflags("nzc");
    setExpectedRegisterValue(R2, 0x00000001);
}

void test_rorRegisterRotateBy32_CarryOutHighestBit()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 0x80000000);
    setRegisterValue(R7, 32);
    emitInstruction16("0100000111mmmddd", R7, R0);
    setExpectedXPSRflags("NzC");
    setExpectedRegisterValue(R0, 0x80000000);
}

void test_rorRegisterRotateBy33()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, 0x80000001);
    setRegisterValue(R3, 33);
    emitInstruction16("0100000111mmmddd", R3, R2);
    setExpectedXPSRflags("NzC");
    setExpectedRegisterValue(R2, 0xC0000000);
}

void test_rorRegisterRotateWithMaximumShiftOf255()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, 0x80000000);
    setRegisterValue(R3, 255);
    emitInstruction16("0100000111mmmddd", R3, R2);
    setExpectedXPSRflags("nzc");
    setExpectedRegisterValue(R2, 0x00000001);
}

void test_rorRegisterRotateWithShiftOf256_ShouldBeTreatedAs0Shift_CarryUnmodified()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 0x80000000);
    setRegisterValue(R7, 256);
    emitInstruction16("0100000111mmmddd", R7, R0);
    setExpectedXPSRflags("Nz");
    setExpectedRegisterValue(R0, 0x80000000);
}

void test_rorRegisterRotate0by16()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 0);
    setRegisterValue(R7, 16);
    emitInstruction16("0100000111mmmddd", R7, R0);
    setExpectedXPSRflags("nZc");
    setExpectedRegisterValue(R0, 0);
}
