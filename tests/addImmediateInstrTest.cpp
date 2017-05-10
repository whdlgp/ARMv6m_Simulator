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

/* ADD - Immediate - Encoding T1
   Encoding: 000 11 1 0 Imm:3 Rn:3 Rd:3 */
void test_addImmediateT1UseLowestRegisterOnlyAddLargestImmediate()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0001110iiinnnddd", 7, R0, R0);
    setExpectedXPSRflags("nzcv");
    setExpectedRegisterValue(R0, 0U + 7U);
}

void test_addImmediateT1UseHigestRegisterOnlyAddSmallestImmediate()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0001110iiinnnddd", 0, R7, R7);
    setExpectedXPSRflags("nzcv");
    setExpectedRegisterValue(R7, 0x77777777U + 0U);
}

void test_addImmediateT1UseDifferentRegistersForEachArg()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0001110iiinnnddd", 3, R7, R0);
    setExpectedXPSRflags("nzcv");
    setExpectedRegisterValue(R0, 0x77777777U + 3U);
}

void test_addImmediateT1ForceCarryByAdding1ToLargestInteger()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R6, 0xFFFFFFFFU);
    emitInstruction16("0001110iiinnnddd", 1, R6, R1);
    setExpectedXPSRflags("nZCv");
    setExpectedRegisterValue(R1, 0);
}

void test_addImmediateT1ForceOverflowPastLargestPositiveInteger()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, 0x7FFFFFFFU);
    emitInstruction16("0001110iiinnnddd", 1, R2, R5);
    setExpectedXPSRflags("NzcV");
    setExpectedRegisterValue(R5, 0x7FFFFFFFU + 1);
}

void test_addImmediateT2UseLowestRegisterAndAddLargestImmediate()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("00110dddiiiiiiii", R0, 255);
    setExpectedXPSRflags("nzcv");
    setExpectedRegisterValue(R0, 0U + 255U);
}

void test_addImmediateT2UseHigestRegisterAndAddSmallestImmediate()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("00110dddiiiiiiii", R7, 0);
    setExpectedXPSRflags("nzcv");
    setExpectedRegisterValue(R7, 0x77777777U + 0U);
}

void test_addImmediateT2ForceCarryByAdding1ToLargestInteger()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R3, 0xFFFFFFFFU);
    emitInstruction16("00110dddiiiiiiii", R3, 1);
    setExpectedXPSRflags("nZCv");
    setExpectedRegisterValue(R3, 0);
}

void test_addImmediateT2ForceOverflowPastLargestPositiveInteger()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R3, 0x7FFFFFFFU);
    emitInstruction16("00110dddiiiiiiii", R3, 1);
    setExpectedXPSRflags("NzcV");
    setExpectedRegisterValue(R3, 0x7FFFFFFFU + 1);
}
