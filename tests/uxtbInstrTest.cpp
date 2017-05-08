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

/* UXTB (Unsigned ExTend Byte)
   Encoding: 1011 0010 11 Rm:3 Rd:3 */
void test_uxtbExtendLowestRegisterIntoHighestRegister_PositiveValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R7, 0x7F);
    emitInstruction16("1011001011mmmddd", R7, R0);
    setExpectedRegisterValue(R0, 0x7F);
}

void test_uxtbExtendHighestRegisterIntoLowestRegister_NegativeValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 0x80);
    emitInstruction16("1011001011mmmddd", R0, R7);
    setExpectedRegisterValue(R7, 0x80);
}

void test_uxtbOverwriteUpperBits_PositiveValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R6, 0xBADBAD7F);
    emitInstruction16("1011001011mmmddd", R6, R1);
    setExpectedRegisterValue(R1, 0x7F);
}

void test_uxtbOverwriteUpperBits_NegativeValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, 0xBADBAD80);
    emitInstruction16("1011001011mmmddd", R2, R5);
    setExpectedRegisterValue(R5, 0x80);
}
