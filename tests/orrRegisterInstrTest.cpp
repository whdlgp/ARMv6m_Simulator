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

/* ORR - Register
   Encoding: 010000 1100 Rm:3 Rdn:3 */
/* NOTE: APSR_C state is maintained by this instruction. */
void test_orrRegisterUseLowestRegisterForBothArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    emitInstruction16("0100001100mmmddd", R0, R0);
    // Use a couple of tests to explicitly set/clear carry to verify both states are maintained.
    setExpectedXPSRflags("nZc");
    setExpectedRegisterValue(R0, 0);
}

void test_orrRegisterUseHighestRegisterForBothArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    emitInstruction16("0100001100mmmddd", R7, R7);
    setExpectedXPSRflags("nzC");
}

void test_orrRegisterOrR3andR7()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0100001100mmmddd", R3, R7);
    setExpectedXPSRflags("nz");
    setExpectedRegisterValue(R7, 0x33333333 | 0x77777777);
}

void test_orrRegisterUseOrToTurnOnNegativeSignBit()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 0x7FFFFFFF);
    setRegisterValue(R7, 0x80000000);
    emitInstruction16("0100001100mmmddd", R7, R0);
    setExpectedXPSRflags("Nz");
    setExpectedRegisterValue(R0, 0x7FFFFFFF | 0x80000000);
}

void test_orrRegisterHaveAndResultNotBeSameAsEitherSource()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 0x12345678);
    setRegisterValue(R7, 0xF0F0F0F0);
    emitInstruction16("0100001100mmmddd", R0, R7);
    setExpectedXPSRflags("Nz");
    setExpectedRegisterValue(R7, 0xF2F4F6F8);
}
