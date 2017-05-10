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

/* Condition codes */
#define COND_EQ 0x0
#define COND_NE (COND_EQ | 1)
#define COND_CS 0x2
#define COND_CC (COND_CS | 1)
#define COND_MI 0x4
#define COND_PL (COND_MI | 1)
#define COND_VS 0x6
#define COND_VC (COND_VS | 1)
#define COND_HI 0x8
#define COND_LS (COND_HI | 1)
#define COND_GE 0xA
#define COND_LT (COND_GE | 1)
#define COND_GT 0xC
#define COND_LE (COND_GT | 1)
#define COND_AL 0xE

/* B - Encoding T1 (Conditional)
   Encoding: 1101 Cond:4 Imm:8 */
void test_bBEQ_NotTaken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearZero();
    emitInstruction16("1101cccciiiiiiii", COND_EQ, 0);
    // These tests set the APSR flags to specific value and expect them to be unmodified upon return.
    setExpectedXPSRflags("z");
}

void test_bBEQ_Taken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setZero();
    emitInstruction16("1101cccciiiiiiii", COND_EQ, 0);
    setExpectedXPSRflags("Z");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBNE_NotTaken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setZero();
    emitInstruction16("1101cccciiiiiiii", COND_NE, 0);
    setExpectedXPSRflags("Z");
}

void test_bBNE_Taken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearZero();
    emitInstruction16("1101cccciiiiiiii", COND_NE, 0);
    setExpectedXPSRflags("z");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBCS_NotTaken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    emitInstruction16("1101cccciiiiiiii", COND_CS, 0);
    setExpectedXPSRflags("c");
}

void test_bBCS_Taken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    emitInstruction16("1101cccciiiiiiii", COND_CS, 0);
    setExpectedXPSRflags("C");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBCC_NotTaken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    emitInstruction16("1101cccciiiiiiii", COND_CC, 0);
    setExpectedXPSRflags("C");
}

void test_bBCC_Taken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    emitInstruction16("1101cccciiiiiiii", COND_CC, 0);
    setExpectedXPSRflags("c");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBMI_NotTaken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearNegative();
    emitInstruction16("1101cccciiiiiiii", COND_MI, 0);
    setExpectedXPSRflags("n");
}

void test_bBMI_Taken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setNegative();
    emitInstruction16("1101cccciiiiiiii", COND_MI, 0);
    setExpectedXPSRflags("N");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBPL_NotTaken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setNegative();
    emitInstruction16("1101cccciiiiiiii", COND_PL, 0);
    setExpectedXPSRflags("N");
}

void test_bBPL_Taken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearNegative();
    emitInstruction16("1101cccciiiiiiii", COND_PL, 0);
    setExpectedXPSRflags("n");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBVS_NotTaken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearOverflow();
    emitInstruction16("1101cccciiiiiiii", COND_VS, 0);
    setExpectedXPSRflags("v");
}

void test_bBVS_Taken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setOverflow();
    emitInstruction16("1101cccciiiiiiii", COND_VS, 0);
    setExpectedXPSRflags("V");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBVC_NotTaken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setOverflow();
    emitInstruction16("1101cccciiiiiiii", COND_VC, 0);
    setExpectedXPSRflags("V");
}

void test_bBVC_Taken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearOverflow();
    emitInstruction16("1101cccciiiiiiii", COND_VC, 0);
    setExpectedXPSRflags("v");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBHI_NotTaken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry(); setZero();
    emitInstruction16("1101cccciiiiiiii", COND_HI, 0);
    setExpectedXPSRflags("cZ");
}

void test_bBHI_Taken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry(); clearZero();
    emitInstruction16("1101cccciiiiiiii", COND_HI, 0);
    setExpectedXPSRflags("Cz");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBLS_NotTaken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry(); clearZero();
    emitInstruction16("1101cccciiiiiiii", COND_LS, 0);
    setExpectedXPSRflags("Cz");
}

void test_bBLS_Taken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry(); setZero();
    emitInstruction16("1101cccciiiiiiii", COND_LS, 0);
    setExpectedXPSRflags("cZ");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBGE_NotTaken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setNegative(); clearOverflow();
    emitInstruction16("1101cccciiiiiiii", COND_GE, 0);
    setExpectedXPSRflags("Nv");
}

void test_bBGE_Taken1()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setNegative(); setOverflow();
    emitInstruction16("1101cccciiiiiiii", COND_GE, 0);
    setExpectedXPSRflags("NV");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBGE_Taken2()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearNegative(); clearOverflow();
    emitInstruction16("1101cccciiiiiiii", COND_GE, 0);
    setExpectedXPSRflags("nv");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBLT_NotTaken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setNegative(); setOverflow();
    emitInstruction16("1101cccciiiiiiii", COND_LT, 0);
    setExpectedXPSRflags("NV");
}

void test_bBLT_Taken1()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setNegative(); clearOverflow();
    emitInstruction16("1101cccciiiiiiii", COND_LT, 0);
    setExpectedXPSRflags("Nv");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBLT_Taken2()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearNegative(); setOverflow();
    emitInstruction16("1101cccciiiiiiii", COND_LT, 0);
    setExpectedXPSRflags("nV");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBGT_NotTaken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setZero(); setNegative(); setOverflow();
    emitInstruction16("1101cccciiiiiiii", COND_GT, 0);
    setExpectedXPSRflags("ZNV");
}

void test_bBGT_Taken1()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearZero(); clearNegative(); clearOverflow();
    emitInstruction16("1101cccciiiiiiii", COND_GT, 0);
    setExpectedXPSRflags("znv");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBGT_Taken2()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearZero(); setNegative(); setOverflow();
    emitInstruction16("1101cccciiiiiiii", COND_GT, 0);
    setExpectedXPSRflags("zNV");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBLE_NotTaken()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearZero(); setNegative(); setOverflow();
    emitInstruction16("1101cccciiiiiiii", COND_LE, 0);
    setExpectedXPSRflags("zNV");
}

void test_bBLE_Taken1()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setZero(); setNegative(); clearOverflow();
    emitInstruction16("1101cccciiiiiiii", COND_LE, 0);
    setExpectedXPSRflags("ZNv");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBLE_Taken2()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setZero(); clearNegative(); setOverflow();
    emitInstruction16("1101cccciiiiiiii", COND_LE, 0);
    setExpectedXPSRflags("ZnV");
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBEQ_TakenWithLargestPositiveOffset()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setZero();
    emitInstruction16("1101cccciiiiiiii", COND_EQ, 127);
    setExpectedXPSRflags("Z");
    setExpectedRegisterValue(PC, INITIAL_PC + 4 + 127 * 2);
}

void test_bBEQ_TakenWithLargesNegativeOffset()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setZero();
    emitInstruction16("1101cccciiiiiiii", COND_EQ, -128);
    setExpectedXPSRflags("Z");
    setExpectedRegisterValue(PC, INITIAL_PC + 4 - 128 * 2);
}

/* B - Encoding T2 (Unconditional)
   Encoding: 11100 Imm:11 */
void test_bBAL_ZeroOffset()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("11100iiiiiiiiiii", 0);
    setExpectedRegisterValue(PC, INITIAL_PC + 4);
}

void test_bBAL_LargestPositiveOffset()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("11100iiiiiiiiiii", 1023);
    setExpectedRegisterValue(PC, INITIAL_PC + 4 + 1023 * 2);
}

void test_bBAL_LargestNegativeOffset()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    emitInstruction16("11100iiiiiiiiiii", -1024);
    setExpectedRegisterValue(PC, INITIAL_PC + 4 - 1024 * 2);
}
