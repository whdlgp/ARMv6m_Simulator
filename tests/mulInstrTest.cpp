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

/* MUL
   Encoding: 010000 1101 Rn:3 Rdm:3 */
void test_mulUseLowestRegisterForAllArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0100001101nnnddd", R0, R0);
    setExpectedXPSRflags("nZ");
    setExpectedRegisterValue(R0, 0U);
}

void test_mulUseHigestRegisterForAllArgs_OnlyGetLower32bitsOfResult()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0100001101nnnddd", R7, R7);
    setExpectedXPSRflags("Nz");
    setExpectedRegisterValue(R7, 0x77777777U * 0x77777777U);
}

void test_mulUseDifferentRegistersForEachArg()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R1, 0xA5A5);
    setRegisterValue(R2, 2);
    emitInstruction16("0100001101nnnddd", R1, R2);
    setExpectedXPSRflags("nz");
    setExpectedRegisterValue(R2, 0xA5A5U << 1U);
}

void test_mulMultiplyBy16BitMaximumValues()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R1, 0xFFFF);
    setRegisterValue(R2, 0xFFFF);
    emitInstruction16("0100001101nnnddd", R1, R2);
    setExpectedXPSRflags("Nz");
    setExpectedRegisterValue(R2, (uint32_t)0xFFFF * 0xFFFF);
}
