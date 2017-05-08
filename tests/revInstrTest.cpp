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

/* REV
   Encoding: 1011 1010 00 Rm:3 Rd:3 */
void test_revRevR0toR7()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R0, 0x12345678);
    emitInstruction16("1011101000mmmddd", R0, R7);
    setExpectedRegisterValue(R7, 0x78563412);
}

void test_revRevR7toR0()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R7, 0x12345678);
    emitInstruction16("1011101000mmmddd", R7, R0);
    setExpectedRegisterValue(R0, 0x78563412);
}
