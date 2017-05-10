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

/* CMP - Immediate
   Encoding: 001 01 Rn:3 Imm:8 */
void test_cmpImmediateCompareLowestRegisterToEqualValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("00101nnniiiiiiii", R0, 0);
    setExpectedXPSRflags("nZCv");
}

void test_cmpImmediateCompareHighestRegisterToImmediateWhichIsSmaller()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("00101nnniiiiiiii", R7, 127);
    setExpectedXPSRflags("nzCv");
}

void test_cmpImmediateCompareRegisterToLargestImmediateWhichIsLarger()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("00101nnniiiiiiii", R0, 255);
    setExpectedXPSRflags("Nzcv");
}

void test_cmpImmediateCompareRegisterToImmediateWhichWillGenerateNegativeOverflow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R3, 0x80000000);
    emitInstruction16("00101nnniiiiiiii", R3, 1);
    setExpectedXPSRflags("nzCV");
}
