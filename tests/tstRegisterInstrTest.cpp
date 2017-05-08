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

/* TST - Register
   Encoding: 010000 1000 Rm:3 Rn:3 */
/* NOTE: APSR_C state is maintained by this instruction. */
void test_tstRegisterUseLowestRegisterForBothArgsAndResultShouldBeZero()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    emitInstruction16("0100001000mmmnnn", R0, R0);
    setExpectedXPSRflags("nZc");
}

void test_tstRegisterUseHighestRegisterForBothArgsAndRegisterWillBeUnchanged()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    emitInstruction16("0100001000mmmnnn", R7, R7);
    setExpectedXPSRflags("nzC");
}

void test_tstRegisterAndR3andR7()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0100001000mmmnnn", R3, R7);
    setExpectedXPSRflags("nz");
}

void test_tstRegisterUseAndToJustKeepNegativeSignBit()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, -1);
    setRegisterValue(R7, 0x80000000);
    emitInstruction16("0100001000mmmnnn", R7, R0);
    setExpectedXPSRflags("Nz");
}
