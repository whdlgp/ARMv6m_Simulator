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

/* CMN - Register (Compare Negative)
   Encoding: 010000 1011 Rm:3 Rn:3 */
void test_cmnRegisterUseLowestRegisterForAllArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0100001011mmmnnn", R0, R0);
    setExpectedXPSRflags("nZcv");
}

void test_cmnRegisterUseHigestRegisterForAllArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0100001011mmmnnn", R7, R7);
    setExpectedXPSRflags("NzcV");
}

void test_cmnRegisterUseDifferentRegistersForEachArg()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0100001011mmmnnn", R1, R2);
    setExpectedXPSRflags("nzcv");
}

// Force APSR flags to be set which haven't already been covered above.
void test_cmnRegisterForceCarryWithNoOverflow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R1, -1);
    setRegisterValue(R2, 1);
    emitInstruction16("0100001011mmmnnn", R1, R2);
    setExpectedXPSRflags("nZCv");
}

void test_cmnRegisterForceCarryAndOverflow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R1, -1);
    setRegisterValue(R2, 0x80000000U);
    emitInstruction16("0100001011mmmnnn", R1, R2);
    setExpectedXPSRflags("nzCV");
}
