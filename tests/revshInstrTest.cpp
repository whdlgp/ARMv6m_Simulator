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

/* REVSH
   Encoding: 1011 1010 11 Rm:3 Rd:3 */
void test_revshRevR0toR7()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 0x12345678);
    emitInstruction16("1011101011mmmddd", R0, R7);
    setExpectedRegisterValue(R7, 0x7856);
}

void test_revshRevR7toR0()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R7, 0x12345678);
    emitInstruction16("1011101011mmmddd", R7, R0);
    setExpectedRegisterValue(R0, 0x7856);
}

void test_revshPositiveValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R7, 0xFF7F);
    emitInstruction16("1011101011mmmddd", R7, R0);
    setExpectedRegisterValue(R0, 0x7FFF);
}

void test_revshNegativeValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R7, 0x0080);
    emitInstruction16("1011101011mmmddd", R7, R0);
    setExpectedRegisterValue(R0, 0xFFFF8000);
}
