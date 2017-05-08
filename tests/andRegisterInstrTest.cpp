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

/* AND - Register
   Encoding: 010000 0000 Rm:3 Rdn:3 */
/* NOTE: APSR_C state is maintained by this instruction. */
void test_andRegisterUseLowestRegisterForBothArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    emitInstruction16("0100000000mmmddd", R0, R0);
    setExpectedXPSRflags("nZc");
    // Use a couple of tests to explicitly set/clear carry to verify both states are maintained.
    setExpectedRegisterValue(R0, 0);
}

void test_andRegisterUseHighestRegisterForBothArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    emitInstruction16("0100000000mmmddd", R7, R7);
    setExpectedXPSRflags("nzC");
}

void test_andRegisterAndR3andR7()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0100000000mmmddd", R3, R7);
    setExpectedXPSRflags("nz");
    setExpectedRegisterValue(R7, 0x33333333);
}

void test_andRegisterUseAndToJustKeepNegativeSignBit()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R1, -1);
    setRegisterValue(R6, 0x80000000);
    emitInstruction16("0100000000mmmddd", R6, R1);
    setExpectedXPSRflags("Nz");
    setExpectedRegisterValue(R1, 0x80000000);
}

void test_andRegisterHaveAndResultNotBeSameAsEitherSource()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, 0x12345678);
    setRegisterValue(R5, 0xF0F0F0F0);
    emitInstruction16("0100000000mmmddd", R5, R2);
    setExpectedXPSRflags("nz");
    setExpectedRegisterValue(R2, 0x10305070);
}
