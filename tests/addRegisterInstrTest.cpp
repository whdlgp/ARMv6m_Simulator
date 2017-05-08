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

/* ADD - Register - Encoding T1
   Encoding: 000 11 0 0 Rm:3 Rn:3 Rd:3 */
void test_addRegisterT1UseLowestRegisterForAllArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0001100mmmnnnddd", R0, R0, R0);
    setExpectedXPSRflags("nZcv");
    setExpectedRegisterValue(R0, 0U);
}

void test_addRegisterT1UseHigestRegisterForAllArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0001100mmmnnnddd", R7, R7, R7);
    setExpectedXPSRflags("NzcV");
    setExpectedRegisterValue(R7, 0x77777777U + 0x77777777U);
}

void test_addRegisterT1UseDifferentRegistersForEachArg()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("0001100mmmnnnddd", R1, R2, R3);
    setExpectedXPSRflags("nzcv");
    setExpectedRegisterValue(R3, 0x11111111U + 0x22222222U);
}

// Force APSR flags to be set which haven't already been covered above.
void test_addRegisterT1ForceCarryWithNoOverflow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R1, -1);
    setRegisterValue(R2, 1);
    emitInstruction16("0001100mmmnnnddd", R1, R2, R0);
    setExpectedXPSRflags("nZCv");
    setExpectedRegisterValue(R0, -1 + 1);
}

void test_addRegisterT1ForceCarryAndOverflow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R1, -1);
    setRegisterValue(R2, 0x80000000U);
    emitInstruction16("0001100mmmnnnddd", R1, R2, R0);
    setExpectedXPSRflags("nzCV");
    setExpectedRegisterValue(R0, -1 + (uint32_t)0x80000000U);
}

/* ADD - Register - Encoding T2
   Encoding: 010001 00 DN:1 Rm:4 Rdn:3
   NOTE: Shouldn't modify any of the APSR flags.*/
void test_addRegisterT2UseR1ForAllArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("01000100dmmmmddd", R1, R1);
    setExpectedRegisterValue(R1, 0x11111111U + 0x11111111U);
}

void test_addRegisterT2UseLowestRegisterForAllArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("01000100dmmmmddd", R0, R0);
    setExpectedRegisterValue(R0, 0U);
}

void test_addRegisterT2UseR12ForAllArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("01000100dmmmmddd", R12, R12);
    setExpectedRegisterValue(R12, 0xCCCCCCCCU + 0xCCCCCCCCU);
}

void test_addRegisterT2UseDifferentRegistersForEachArg()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("01000100dmmmmddd", R2, R1);
    setExpectedRegisterValue(R2, 0x11111111U + 0x22222222U);
}

void test_addRegisterT2WrapAroundTo0()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R1, -1);
    setRegisterValue(R2, 1);
    emitInstruction16("01000100dmmmmddd", R2, R1);
    setExpectedRegisterValue(R2, -1 + 1);
}

void test_addRegisterT2OverflowFromLowestNegativeValue()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R10, -1);
    setRegisterValue(R11, 0x80000000U);
    emitInstruction16("01000100dmmmmddd", R11, R10);
    setExpectedRegisterValue(R11, -1 + (uint32_t)0x80000000U);
}

void test_addRegisterT2Add4ToSP()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(SP, INITIAL_SP - 4);
    setRegisterValue(R1, 4);
    emitInstruction16("01000100dmmmmddd", SP, R1);
    setExpectedRegisterValue(SP, INITIAL_SP - 4 + 4);
}

void test_addRegisterT2Subtract4FromSP()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R1, -4);
    emitInstruction16("01000100dmmmmddd", SP, R1);
    setExpectedRegisterValue(SP, INITIAL_SP - 4);
}

void test_addRegisterT2Add1ToLR()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R1, 1);
    emitInstruction16("01000100dmmmmddd", LR, R1);
    setExpectedRegisterValue(LR, INITIAL_LR + 1);
}

void test_addRegisterT2Add1ToPCWhichWillBeOddAndRoundedDown()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R1, 1);
    emitInstruction16("01000100dmmmmddd", PC, R1);
    setExpectedRegisterValue(PC, (INITIAL_PC + 4 + 1) & 0xFFFFFFFE);
}

void test_addRegisterT2Add2ToPC()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(R1, 2);
    emitInstruction16("01000100dmmmmddd", PC, R1);
    setExpectedRegisterValue(PC, (INITIAL_PC + 4 + 2) & 0xFFFFFFFE);
}
