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

/* SXTB (Sign ExTend Byte)
   Encoding: 1011 0010 01 Rm:3 Rd:3 */
void test_sxtbSignExtendLowestRegisterIntoHighestRegister_PositiveValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R7, 0x7F);
    emitInstruction16("1011001001mmmddd", R7, R0);
    setExpectedRegisterValue(R0, 0x7F);
}

void test_sxtbSignExtendHighestRegisterIntoLowestRegister_NegativeValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 0x80);
    emitInstruction16("1011001001mmmddd", R0, R7);
    setExpectedRegisterValue(R7, 0xFFFFFF80);
}

void test_sxtbOverwriteUpperBits_PositiveValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R6, 0xBADBAD7F);
    emitInstruction16("1011001001mmmddd", R6, R1);
    setExpectedRegisterValue(R1, 0x7F);
}

void test_sxtbOverwriteUpperBits_NegativeValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, 0xBADBAD80);
    emitInstruction16("1011001001mmmddd", R2, R5);
    setExpectedRegisterValue(R5, 0xFFFFFF80);
}
