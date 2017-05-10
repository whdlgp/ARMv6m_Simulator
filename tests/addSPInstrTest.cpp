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

/* ADD SP Plus Immediate - Encoding T1
   Encoding: 1010 1 Rd:3 Imm:8 */
void test_addSPT1UseHighestRegisterAddSmallestImmediate()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("10101dddiiiiiiii", R7, 0);
    setExpectedRegisterValue(R7, INITIAL_SP + 0);
}

void test_addSPT1UseLowestRegisterAddLargestImmediate()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("10101dddiiiiiiii", R0, 255);
    setExpectedRegisterValue(R0, INITIAL_SP + 255 * 4);
}

void test_addSPT1UseIntermediateValues()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("10101dddiiiiiiii", R3, 128);
    setExpectedRegisterValue(R3, INITIAL_SP + 128 * 4);
}

/* ADD SP Plus Immediate - Encoding T2
   Encoding: 1011 0000 0 Imm:7 */
void test_addSPT2SmallestImmediate()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(SP, INITIAL_PC + 1024);
    emitInstruction16("101100000iiiiiii", 0);
    setExpectedRegisterValue(SP, INITIAL_PC + 1024 + 0);
}

void test_addSPT2LargestImmediate()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(SP, INITIAL_PC + 1024);
    emitInstruction16("101100000iiiiiii", 127);
    setExpectedRegisterValue(SP, INITIAL_PC + 1024 + 127 * 4);
}

void test_addSPT2IntermediateValues()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(SP, INITIAL_PC + 1024);
    emitInstruction16("101100000iiiiiii", 64);
    setExpectedRegisterValue(SP, INITIAL_PC + 1024 + 64 * 4);
}
