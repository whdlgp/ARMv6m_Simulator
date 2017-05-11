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

/* SUB - Immediate - Encoding T1
   Encoding: 000 11 1 1 Imm:3 Rn:3 Rd:3 */
void test_subImmediateT1UseLowestRegisterOnly_SmallestImmediate()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0001111iiinnnddd", 0, R0, R0);
    setExpectedXPSRflags("nZCv");
    setExpectedRegisterValue(R0, 0U);
}

void test_subImmediateT1UseHigestRegisterOnly_LargestImmediate()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0001111iiinnnddd", 7, R7, R7);
    setExpectedXPSRflags("nzCv");
    setExpectedRegisterValue(R7, 0x77777777U - 7U);
}

void test_subImmediateT1UseDifferentRegistersForEachArg()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0001111iiinnnddd", 3, R0, R2);
    setExpectedXPSRflags("Nzcv");
    setExpectedRegisterValue(R2, 0U - 3U);
}

void test_subImmediateT1ForceOverflowPastLargestNegativeInteger()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R1, 0x80000000);
    emitInstruction16("0001111iiinnnddd", 1, R1, R6);
    setExpectedXPSRflags("nzCV");
    setExpectedRegisterValue(R6, 0x80000000U - 1U);
}

/* SUB - Immediate - Encoding T2
   Encoding: 001 11 Rdn:3 Imm:8 */
void test_subImmediateT2LowestRegisterSmallestImmediate()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("00111dddiiiiiiii", R0, 0);
    setExpectedXPSRflags("nZCv");
    setExpectedRegisterValue(R0, 0U);
}

void test_subImmediateT2HigestRegister_LargestImmediate()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("00111dddiiiiiiii", R7, 255);
    setExpectedXPSRflags("nzCv");
    setExpectedRegisterValue(R7, 0x77777777U - 255U);
}

void test_subImmediateT2Subtract127FromR0CausesNoCarryToIndicateBorrowAndNegativeResult()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("00111dddiiiiiiii", R0, 127);
    setExpectedXPSRflags("Nzcv");
    setExpectedRegisterValue(R0, 0U - 127U);
}

void test_subImmediateT2ForceOverflowPastLargestNegativeInteger()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R3, 0x80000000);
    emitInstruction16("00111dddiiiiiiii", R3, 1);
    setExpectedXPSRflags("nzCV");
    setExpectedRegisterValue(R3, 0x80000000U - 1U);
}
