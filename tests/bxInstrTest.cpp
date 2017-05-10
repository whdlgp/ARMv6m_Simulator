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

void test_bxUseHighestRegisterToBranchToOddAddressWhichIsRequiredForThumb()
{
    printf (" %s \n", __FUNCTION__);
    setInitialRegisterValues();
    setRegisterValue(LR, (INITIAL_PC + 16) | 1);
    emitInstruction16("010001110mmmm000", LR);
    setExpectedRegisterValue(PC, INITIAL_PC + 16);
}
