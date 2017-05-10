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

/* ADC - Register (ADd with Carry)
   Encoding: 010000 0101 Rm:3 Rdn:3 */
void test_adcRegisterUseR1ForAllArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    emitInstruction16("0100000101mmmddd", R1, R1);
    setExpectedXPSRflags("nzcv");
    setExpectedRegisterValue(R1, 0x11111111U + 0x11111111U);
}

void test_adcRegisterUseLowestRegisterForAllArgs()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    emitInstruction16("0100000101mmmddd", R0, R0);
    setExpectedXPSRflags("nZcv");
    setExpectedRegisterValue(R0, 0U);
}

void test_adcRegisterUseHigestRegisterForAllArgsPositiveOverflow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    emitInstruction16("0100000101mmmddd", R7, R7);
    setExpectedXPSRflags("NzcV");
    setExpectedRegisterValue(R7, 0x77777777U + 0x77777777U);
}

void test_adcRegisterUseDifferentRegistersForEachArg()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    emitInstruction16("0100000101mmmddd", R1, R2);
    setExpectedXPSRflags("nzcv");
    setExpectedRegisterValue(R2, 0x11111111U + 0x22222222U);
}
void test_adcRegisterAdd0to0WithCarryInSetToGiveAResultOf1()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    emitInstruction16("0100000101mmmddd", R0, R0);
    setExpectedXPSRflags("nzcv");
    setExpectedRegisterValue(R0, 0U + 0U + 1U);
}

// Force APSR flags to be set which haven't already been covered above.
void test_adcRegisterForceCarryOut()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    setRegisterValue(R1, -1);
    setRegisterValue(R2, 1);
    emitInstruction16("0100000101mmmddd", R1, R2);
    setExpectedXPSRflags("nZCv");
    setExpectedRegisterValue(R2, -1 + 1);
}

void test_adcRegisterForceCarryOutAndOverflow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    setRegisterValue(R1, -1);
    setRegisterValue(R2, 0x80000000U);
    emitInstruction16("0100000101mmmddd", R1, R2);
    setExpectedXPSRflags("nzCV");
    setExpectedRegisterValue(R2, -1 + (uint32_t)0x80000000U);
}
