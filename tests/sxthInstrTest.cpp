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

/* SXTH (Sign ExTend Halfword)
   Encoding: 1011 0010 00 Rm:3 Rd:3 */
void test_sxthSignExtendLowestRegisterIntoHighestRegister_PositiveValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R7, 0x7FFF);
    emitInstruction16("1011001000mmmddd", R7, R0);
    setExpectedRegisterValue(R0, 0x7FFF);
}

void test_sxthSignExtendHighestRegisterIntoLowestRegister_NegativeValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 0x8000);
    emitInstruction16("1011001000mmmddd", R0, R7);
    setExpectedRegisterValue(R7, 0xFFFF8000);
}

void test_sxthOverwriteUpperBits_PositiveValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R6, 0xF00D7FFF);
    emitInstruction16("1011001000mmmddd", R6, R1);
    setExpectedRegisterValue(R1, 0x00007FFF);
}

void test_sxthOverwriteUpperBits_NegativeValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, 0xF00D8000);
    emitInstruction16("1011001000mmmddd", R2, R5);
    setExpectedRegisterValue(R5, 0xFFFF8000);
}
