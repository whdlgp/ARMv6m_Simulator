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

/* MVN - Register (MOve Negative)
   Encoding: 010000 1111 Rm:3 Rd:3 */
/* NOTE: APSR_C state is maintained by this instruction. */
void test_mvnRegisterUseLowestRegisterForAllArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    // Use a couple of tests to explicitly set/clear carry to verify both states are maintained.
    emitInstruction16("0100001111mmmddd", R0, R0);
    setExpectedXPSRflags("NzC");
    setExpectedRegisterValue(R0, ~0U);
}

void test_mvnRegisterUseHigestRegisterForAllArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    emitInstruction16("0100001111mmmddd", R7, R7);
    setExpectedXPSRflags("Nzc");
    setExpectedRegisterValue(R7, ~0x77777777U);
}

void test_mvnRegisterUseDifferentRegistersForEachArg()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0100001111mmmddd", R2, R1);
    setExpectedXPSRflags("Nz");
    setExpectedRegisterValue(R1, ~0x22222222U);
}

void test_mvnRegisterMoveANegationOfNegativeOne_ClearsNegativeFlagAndSetsZeroFlag()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, -1);
    emitInstruction16("0100001111mmmddd", R2, R1);
    setExpectedXPSRflags("nZ");
    setExpectedRegisterValue(R1, 0U);
}
