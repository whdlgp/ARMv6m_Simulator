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

/* EOR - Register
   Encoding: 010000 0001 Rm:3 Rdn:3 */
/* NOTE: APSR_C state is maintained by this instruction. */
void test_eorRegisterUseLowestRegisterForBothArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    emitInstruction16("0100000001mmmddd", R0, R0);
    // Use a couple of tests to explicitly set/clear carry to verify both states are maintained.
    setExpectedXPSRflags("nZc");
    setExpectedRegisterValue(R0, 0);
}

void test_eorRegisterUseHighestRegisterForBothArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    emitInstruction16("0100000001mmmddd", R7, R7);
    setExpectedXPSRflags("nZC");
    setExpectedRegisterValue(R7, 0);
}

void test_eorRegisterXorR3andR7()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    emitInstruction16("0100000001mmmddd", R3, R7);
    setExpectedXPSRflags("nzc");
    setExpectedRegisterValue(R7, 0x33333333 ^ 0x77777777);
}

void test_eorRegisterUseXorToJustFlipNegativeSignBitOn()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    setRegisterValue(R6, 0x80000000);
    emitInstruction16("0100000001mmmddd", R6, R3);
    setExpectedXPSRflags("NzC");
    setExpectedRegisterValue(R3, 0x33333333 ^ 0x80000000);
}
