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

/* CMP - Register - Encoding T1
   Encoding: 010000 1010 Rm:3 Rn:3 */
void test_cmpRegisterT1UseLowestRegisterForAllArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0100001010mmmnnn", R0, R0);
    setExpectedXPSRflags("nZCv");
}

void test_cmpRegisterT1UseHigestRegisterForAllArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0100001010mmmnnn", R7, R7);
    setExpectedXPSRflags("nZCv");
}

void test_cmpRegisterT1RnLargerThanRm()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0100001010mmmnnn", R1, R2);
    setExpectedXPSRflags("nzCv");
}

void test_cmpRegisterT1RnSmallerThanRm()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R1, 1);
    emitInstruction16("0100001010mmmnnn", R1, R0);
    setExpectedXPSRflags("Nzcv");
}

void test_cmpRegisterT1ForceNegativeOverflow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, 0x80000000U);
    setRegisterValue(R1, 1U);
    emitInstruction16("0100001010mmmnnn", R1, R2);
    setExpectedXPSRflags("nzCV");
}

void test_cmpRegisterT1ForcePositiveOverflow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R2, 0x7FFFFFFFU);
    setRegisterValue(R1, -1U);
    emitInstruction16("0100001010mmmnnn", R1, R2);
    setExpectedXPSRflags("NzcV");
}

/* CMP - Register - Encoding T2
   Encoding: 010001 01 N:1 Rm:4 Rn:3
   NOTE: At least one register must be high register, R8 - R14. */
void test_cmpRegisterT2CompareLowestRegisterToHighestRegister()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(LR, 0xEEEEEEEE);
    emitInstruction16("01000101nmmmmnnn", R0, LR);
    setExpectedXPSRflags("nzcv");
}

void test_cmpRegisterT2CompareHighestRegisterToLowestRegister()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(LR, 0xEEEEEEEE);
    emitInstruction16("01000101nmmmmnnn", LR, R0);
    setExpectedXPSRflags("NzCv");
}

void test_cmpRegisterT2CompareR8ToItself()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("01000101nmmmmnnn", R8, R8);
    setExpectedXPSRflags("nZCv");
}

void test_cmpRegisterT2ForceNegativeOverflow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R11, 0x80000000U);
    setRegisterValue(R12, 1U);
    emitInstruction16("01000101nmmmmnnn", R11, R12);
    setExpectedXPSRflags("nzCV");
}

void test_cmpRegisterT2ForcePositiveOverflow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R11, 0x7FFFFFFFU);
    setRegisterValue(R12, -1U);
    emitInstruction16("01000101nmmmmnnn", R11, R12);
    setExpectedXPSRflags("NzcV");
}
