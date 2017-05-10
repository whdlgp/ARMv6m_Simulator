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

/* LSL - Register (Logical Shift Left)
   Encoding: 010000 0010 Rm:3 Rdn:3 */
void test_lslRegisterShiftR7by0_MinimumShift_CarryShouldBeUnmodified()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    emitInstruction16("0100000010mmmddd", R0, R7);
    setExpectedXPSRflags("nzC");
    setExpectedRegisterValue(R7, 0x77777777U);
}

void test_lslRegisterShiftValue1by31_NegativeResult()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R3, 1);
    setRegisterValue(R4, 31);
    emitInstruction16("0100000010mmmddd", R4, R3);
    setExpectedXPSRflags("Nzc");
    setExpectedRegisterValue(R3, 1 << 31);
}

void test_lslRegisterShiftValue1by32_CarryOutFromLowestBit()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 1);
    setRegisterValue(R7, 32);
    emitInstruction16("0100000010mmmddd", R7, R0);
    setExpectedXPSRflags("nZC");
    setExpectedRegisterValue(R0, 0);
}

void test_lslRegisterShiftNegativeValueBy1_CarryOutFromHighestBit()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R4, -1);
    setRegisterValue(R3, 1);
    emitInstruction16("0100000010mmmddd", R3, R4);
    setExpectedXPSRflags("NzC");
    setExpectedRegisterValue(R4, -1 << 1);
}

void test_lslRegisterShiftValue1by33_NoCarry()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 1);
    setRegisterValue(R7, 33);
    emitInstruction16("0100000010mmmddd", R7, R0);
    setExpectedXPSRflags("nZc");
    setExpectedRegisterValue(R0, 0);
}

void test_lslRegisterShiftValuee1by255_MaximumShift()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 1);
    setRegisterValue(R7, 255);
    emitInstruction16("0100000010mmmddd", R7, R0);
    setExpectedXPSRflags("nZc");
    setExpectedRegisterValue(R0, 0);
}

void test_lslRegisterShiftValue1by256_ShouldBeTreatedAs0Shift_CarryUnmodified()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    setRegisterValue(R0, 1);
    setRegisterValue(R7, 256);
    emitInstruction16("0100000010mmmddd", R7, R0);
    setExpectedXPSRflags("nzc");
    setExpectedRegisterValue(R0, 1);
}
