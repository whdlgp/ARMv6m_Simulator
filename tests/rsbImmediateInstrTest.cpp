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

/* RSB - Immediate
   Encoding: 010000 1001 Rn:3 Rd:3 */
void test_rsbImmediateUseLowestRegisterOnly()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0100001001nnnddd", R0, R0);
    setExpectedXPSRflags("nZCv");
    setExpectedRegisterValue(R0, 0U);
}

void test_rsbImmediateUseHigestRegisterOnly()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0100001001nnnddd", R7, R7);
    setExpectedXPSRflags("Nzcv");
    setExpectedRegisterValue(R7, -0x77777777U);
}

void test_rsbImmediateUseDifferentRegistersForEachArg()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0100001001nnnddd", R2, R0);
    setExpectedXPSRflags("Nzcv");
    setExpectedRegisterValue(R0, -0x22222222);
}

void test_rsbImmediateForceOverflowByNegatingLargestNegativeValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 0x80000000);
    emitInstruction16("0100001001nnnddd", R0, R7);
    setExpectedXPSRflags("NzcV");
    setExpectedRegisterValue(R7, 0x80000000U);
}
