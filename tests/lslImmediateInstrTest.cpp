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
#define IMM_0  0
#define IMM_1  1
#define IMM_3  3
#define IMM_4  4
#define IMM_31 31

/* LSL - Immediate (Logical Shift Left)
   Encoding: 000 00 imm:5 Rm:3 Rd:3 */
void test_lslImmediateMovR7toR0_CarryUnmodified()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    emitInstruction16("00000iiiiimmmddd", IMM_0, R7, R0);
    setExpectedXPSRflags("nzc");
    setExpectedRegisterValue(R0, 0x77777777U);
}

void test_lslImmediateMovR0toR7_ZeroResultAndCarryUnmodified()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    emitInstruction16("00000iiiiimmmddd", IMM_0, R0, R7);
    setExpectedXPSRflags("nZC");
    setExpectedRegisterValue(R7, 0x0);
}

void test_lslImmediateShiftR1by3_ResultInNegativeValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("00000iiiiimmmddd", IMM_3, R1, R0);
    setExpectedXPSRflags("Nzc");
    setExpectedRegisterValue(R0, 0x11111111U << 3);
}

void test_lslImmediateShiftR1by4_HasCarryOut()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("00000iiiiimmmddd", IMM_4, R1, R0);
    setExpectedXPSRflags("nzC");
    setExpectedRegisterValue(R0, 0x11111111U << 4);
}

void test_lslImmediateShiftR0by31_PushesLowestbitIntoSignBit()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 1U);
    emitInstruction16("00000iiiiimmmddd", IMM_31, R0, R0);
    setExpectedXPSRflags("Nzc");
    setExpectedRegisterValue(R0, 1U << 31);
}

void test_lslImmediateCarryOutFromHighestBit()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 0xA0000000U);
    emitInstruction16("00000iiiiimmmddd", IMM_1, R0, R0);
    setExpectedXPSRflags("nzC");
    setExpectedRegisterValue(R0, 0xA0000000U << 1);
}

void test_lslImmediateCarryOutFromLowestBit()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 0x2U);
    emitInstruction16("00000iiiiimmmddd", IMM_31, R0, R0);
    setExpectedXPSRflags("nZC");
    setExpectedRegisterValue(R0, 0x2U << 31);
}
