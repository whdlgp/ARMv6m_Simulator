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

/* SBC - Register (SUBtract with Carry)
   Encoding: 010000 0110 Rm:3 Rdn:3 */
void test_sbcRegisterUseLowestRegisterForAllArgsAndShouldBeZeroWithCarrySetForNoBorrow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    emitInstruction16("0100000110mmmddd", R0, R0);
    setExpectedXPSRflags("nZCv");
    setExpectedRegisterValue(R0, 0);
}

void test_sbcRegisterUseHigestRegisterForAllArgsAndShouldBeZeroWithCarrySetForNoBorrow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    emitInstruction16("0100000110mmmddd", R7, R7);
    setExpectedXPSRflags("nZCv");
    setExpectedRegisterValue(R7, 0);
}

void test_sbcRegisterUseDifferentRegistersForEachArgAndOnlyCarryShouldBeSetToIndicateNoBorrow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    emitInstruction16("0100000110mmmddd", R1, R2);
    setExpectedXPSRflags("nzCv");
    setExpectedRegisterValue(R2, 0x22222222U - 0x11111111U);
}

void test_sbcRegisterForceCarryClearToIndicateBorrowAndResultWillBeNegative()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    setRegisterValue(R1, 1);
    emitInstruction16("0100000110mmmddd", R1, R0);
    setExpectedXPSRflags("Nzcv");
    setExpectedRegisterValue(R0, 0U - 1U);
}

void test_sbcRegisterForceNegativeOverflow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    setRegisterValue(R2, 0x80000000U);
    setRegisterValue(R1, 1U);
    emitInstruction16("0100000110mmmddd", R1, R2);
    setExpectedXPSRflags("nzCV");
    setExpectedRegisterValue(R2, 0x80000000U - 1);
}

void test_sbcRegisterForcePositiveOverflow()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setCarry();
    setRegisterValue(R2, 0x7FFFFFFFU);
    setRegisterValue(R1, -1U);
    emitInstruction16("0100000110mmmddd", R1, R2);
    setExpectedXPSRflags("NzcV");
    setExpectedRegisterValue(R2, (uint32_t)0x7FFFFFFF + 1);
}

void test_sbcRegisterClearCarryToCauseABorrowToOccur()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    clearCarry();
    emitInstruction16("0100000110mmmddd", R1, R2);
    setExpectedXPSRflags("nzCv");
    setExpectedRegisterValue(R2, 0x22222222U - 1U - 0x11111111U);
}
