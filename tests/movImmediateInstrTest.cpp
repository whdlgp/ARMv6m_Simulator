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

/* MOV - Immediate
   Encoding: 001 00 Rd:3 Imm:8 */
/* NOTE: APSR_C state is maintained by this instruction. */
void test_movImmediateMovToR0()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    emitInstruction16("00100dddiiiiiiii", R0, 127);
    // Use a couple of tests to explicitly set/clear carry to verify both states are maintained.
    setExpectedXPSRflags("nzc");
    setExpectedRegisterValue(R0, 127);
}

void test_movImmediateMovToR7()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    emitInstruction16("00100dddiiiiiiii", R7, 127);
    setExpectedXPSRflags("nzC");
    setExpectedRegisterValue(R7, 127);
}

void test_movImmediateMovSmallestImmediateValueToR3()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("00100dddiiiiiiii", R3, 0);
    setExpectedXPSRflags("nZ");
    setExpectedRegisterValue(R3, 0);
}

void test_movImmediateMovLargestImmediateValueToR3()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("00100dddiiiiiiii", R3, 255);
    setExpectedXPSRflags("nz");
    setExpectedRegisterValue(R3, 255);
}
