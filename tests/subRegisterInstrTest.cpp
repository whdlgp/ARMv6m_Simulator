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

/* SUB - Register
   Encoding: 000 11 0 1 Rm:3 Rn:3 Rd:3 */
void test_subRegisterUseLowestRegisterForAllArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0001101mmmnnnddd", R0, R0, R0);
    setExpectedXPSRflags("nZCv");
    setExpectedRegisterValue(R0, 0);
}

void test_subRegisterUseHigestRegisterForAllArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0001101mmmnnnddd", R7, R7, R7);
    setExpectedXPSRflags("nZCv");
    setExpectedRegisterValue(R7, 0);
}

void test_subRegisterUseDifferentRegistersForEachArg()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0001101mmmnnnddd", R1, R2, R0);
    setExpectedXPSRflags("nzCv");
    setExpectedRegisterValue(R0, 0x22222222U - 0x11111111U);
}

// Force APSR flags to be set which haven't already been covered above.
void test_subRegisterForceCarryClearToIndicateBorrowAndResultWillBeNegative()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R1, 1);
    emitInstruction16("0001101mmmnnnddd", R1, R0, R2);
    setExpectedXPSRflags("Nzcv");
    setExpectedRegisterValue(R2, 0U - 1U);
}

void test_subRegisterForceNegativeOverflow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, 0x80000000U);
    setRegisterValue(R1, 1U);
    emitInstruction16("0001101mmmnnnddd", R1, R2, R0);
    setExpectedXPSRflags("nzCV");
    setExpectedRegisterValue(R0, 0x80000000U - 1);
}

void test_subRegisterForcePositiveOverflow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, 0x7FFFFFFFU);
    setRegisterValue(R1, -1U);
    emitInstruction16("0001101mmmnnnddd", R1, R2, R0);
    setExpectedXPSRflags("NzcV");
    setExpectedRegisterValue(R0, 0x7FFFFFFFU + 1U);
}
