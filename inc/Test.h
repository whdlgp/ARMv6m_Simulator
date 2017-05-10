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

#include "ctocpp.h"

#define R0  0
#define R1  1
#define R2  2
#define R3  3
#define R4  4
#define R5  5
#define R6  6
#define R7  7
#define R8  8
#define R9  9
#define R10 10
#define R11 11
#define R12 12
#define SP  13
#define LR  14
#define PC  15

#define INITIAL_SP 0x00000000
#define INITIAL_PC 0x00000000
#define INITIAL_LR 0x00000000

void clearCarry();
void clearNegative();
void clearOverflow();
void clearZero();
void emitInstruction16(const char* pEncoding, ...);
void emitInstruction16Varg(const char* pEncoding, va_list valist);
void setCarry();
void setExpectedRegisterValue(int index, uint32_t expectedValue);
void setExpectedXPSRflags(const char* pExpectedFlags);
void setInitialRegisterValues();
void setNegative();
void setOverflow();
void setRegisterValue(int index, uint32_t value);
void setZero();
void test_adcRegisterAdd0to0WithCarryInSetToGiveAResultOf1();
void test_adcRegisterForceCarryOut();
void test_adcRegisterForceCarryOutAndOverflow();
void test_adcRegisterUseDifferentRegistersForEachArg();
void test_adcRegisterUseHigestRegisterForAllArgsPositiveOverflow();
void test_adcRegisterUseLowestRegisterForAllArgs();
void test_adcRegisterUseR1ForAllArgs();
void test_addImmediateT1ForceCarryByAdding1ToLargestInteger();
void test_addImmediateT1ForceOverflowPastLargestPositiveInteger();
void test_addImmediateT1UseDifferentRegistersForEachArg();
void test_addImmediateT1UseHigestRegisterOnlyAddSmallestImmediate();
void test_addImmediateT1UseLowestRegisterOnlyAddLargestImmediate();
void test_addImmediateT2ForceCarryByAdding1ToLargestInteger();
void test_addImmediateT2ForceOverflowPastLargestPositiveInteger();
void test_addImmediateT2UseHigestRegisterAndAddSmallestImmediate();
void test_addImmediateT2UseLowestRegisterAndAddLargestImmediate();
void test_addRegisterT1ForceCarryAndOverflow();
void test_addRegisterT1ForceCarryWithNoOverflow();
void test_addRegisterT1UseDifferentRegistersForEachArg();
void test_addRegisterT1UseHigestRegisterForAllArgs();
void test_addRegisterT1UseLowestRegisterForAllArgs();
void test_addRegisterT2Add1ToLR();
void test_addRegisterT2Add1ToPCWhichWillBeOddAndRoundedDown();
void test_addRegisterT2Add2ToPC();
void test_addRegisterT2Add4ToSP();
void test_addRegisterT2OverflowFromLowestNegativeValue();
void test_addRegisterT2Subtract4FromSP();
void test_addRegisterT2UseDifferentRegistersForEachArg();
void test_addRegisterT2UseLowestRegisterForAllArgs();
void test_addRegisterT2UseR12ForAllArgs();
void test_addRegisterT2UseR1ForAllArgs();
void test_addRegisterT2WrapAroundTo0();
void test_addSPT1UseHighestRegisterAddSmallestImmediate();
void test_addSPT1UseIntermediateValues();
void test_addSPT1UseLowestRegisterAddLargestImmediate();
void test_addSPT2IntermediateValues();
void test_addSPT2LargestImmediate();
void test_addSPT2SmallestImmediate();
void test_adrHighesttRegisterWithSmallestOffset();
void test_adrLowestRegisterWithLargestOffset();
void test_adrpcWillNeedToBeWordAlignedBeforeAdd();
void test_andRegisterAndR3andR7();
void test_andRegisterHaveAndResultNotBeSameAsEitherSource();
void test_andRegisterUseAndToJustKeepNegativeSignBit();
void test_andRegisterUseHighestRegisterForBothArgs();
void test_andRegisterUseLowestRegisterForBothArgs();
void test_bBAL_LargestNegativeOffset();
void test_bBAL_LargestPositiveOffset();
void test_bBAL_ZeroOffset();
void test_bBCC_NotTaken();
void test_bBCC_Taken();
void test_bBCS_NotTaken();
void test_bBCS_Taken();
void test_bBEQ_NotTaken();
void test_bBEQ_Taken();
void test_bBEQ_TakenWithLargesNegativeOffset();
void test_bBEQ_TakenWithLargestPositiveOffset();
void test_bBGE_NotTaken();
void test_bBGE_Taken1();
void test_bBGE_Taken2();
void test_bBGT_NotTaken();
void test_bBGT_Taken1();
void test_bBGT_Taken2();
void test_bBHI_NotTaken();
void test_bBHI_Taken();
void test_bBLE_NotTaken();
void test_bBLE_Taken1();
void test_bBLE_Taken2();
void test_bBLS_NotTaken();
void test_bBLS_Taken();
void test_bBLT_NotTaken();
void test_bBLT_Taken1();
void test_bBLT_Taken2();
void test_bBMI_NotTaken();
void test_bBMI_Taken();
void test_bBNE_NotTaken();
void test_bBNE_Taken();
void test_bBPL_NotTaken();
void test_bBPL_Taken();
void test_bBVC_NotTaken();
void test_bBVC_Taken();
void test_bBVS_NotTaken();
void test_bBVS_Taken();
void test_bicRegisterUseBicToClearLSbit();
void test_bicRegisterUseHighestRegisterForBothArgs();
void test_bicRegisterUseLowestRegisterForBothArgs();
void test_bicRegisterUseR3andR7();
void test_bxUseHighestRegisterToBranchToOddAddressWhichIsRequiredForThumb();
void test_cmnRegisterForceCarryAndOverflow();
void test_cmnRegisterForceCarryWithNoOverflow();
void test_cmnRegisterUseDifferentRegistersForEachArg();
void test_cmnRegisterUseHigestRegisterForAllArgs();
void test_cmnRegisterUseLowestRegisterForAllArgs();
void test_cmpImmediateCompareHighestRegisterToImmediateWhichIsSmaller();
void test_cmpImmediateCompareLowestRegisterToEqualValue();
void test_cmpImmediateCompareRegisterToImmediateWhichWillGenerateNegativeOverflow();
void test_cmpImmediateCompareRegisterToLargestImmediateWhichIsLarger();
void test_cmpRegisterT1ForceNegativeOverflow();
void test_cmpRegisterT1ForcePositiveOverflow();
void test_cmpRegisterT1RnLargerThanRm();
void test_cmpRegisterT1RnSmallerThanRm();
void test_cmpRegisterT1UseHigestRegisterForAllArgs();
void test_cmpRegisterT1UseLowestRegisterForAllArgs();
void test_cmpRegisterT2CompareHighestRegisterToLowestRegister();
void test_cmpRegisterT2CompareLowestRegisterToHighestRegister();
void test_cmpRegisterT2CompareR8ToItself();
void test_cmpRegisterT2ForceNegativeOverflow();
void test_cmpRegisterT2ForcePositiveOverflow();
void test_eorRegisterUseHighestRegisterForBothArgs();
void test_eorRegisterUseLowestRegisterForBothArgs();
void test_eorRegisterUseXorToJustFlipNegativeSignBitOn();
void test_eorRegisterXorR3andR7();
void test_lslImmediateCarryOutFromHighestBit();
void test_lslImmediateCarryOutFromLowestBit();
void test_lslImmediateMovR0toR7_ZeroResultAndCarryUnmodified();
void test_lslImmediateMovR7toR0_CarryUnmodified();
void test_lslImmediateShiftR0by31_PushesLowestbitIntoSignBit();
void test_lslImmediateShiftR1by3_ResultInNegativeValue();
void test_lslImmediateShiftR1by4_HasCarryOut();
void test_lslRegisterShiftNegativeValueBy1_CarryOutFromHighestBit();
void test_lslRegisterShiftR7by0_MinimumShift_CarryShouldBeUnmodified();
void test_lslRegisterShiftValue1by256_ShouldBeTreatedAs0Shift_CarryUnmodified();
void test_lslRegisterShiftValue1by31_NegativeResult();
void test_lslRegisterShiftValue1by32_CarryOutFromLowestBit();
void test_lslRegisterShiftValue1by33_NoCarry();
void test_lslRegisterShiftValuee1by255_MaximumShift();
void test_lsrImmediateR0by32_CarryOutAndIsZero();
void test_lsrImmediateR1by1toR7_CarryOut();
void test_lsrImmediateR2by1toR0();
void test_lsrImmediateR7by32toR0_ZeroResult();
void test_lsrRegisterMaximumShiftOf255_ResultIsZero_CarryClear();
void test_lsrRegisterShiftNegativeValueBy31();
void test_lsrRegisterShiftNegativeValueBy32_CarryOutFromHighestBit();
void test_lsrRegisterShiftNegativeValueBy33_ResultIsZero_CarryClear();
void test_lsrRegisterShiftOf256_ShouldBeTreatedAs0Shift_CarryUnmodified();
void test_lsrRegisterShiftValue1by0_MinimumShift_CarryUnmodified();
void test_lsrRegisterShiftValue1by1_CarryOutFromLowestBit();
void test_lsrRegisterShiftValue2by1_NoCarry();
void test_movImmediateMovLargestImmediateValueToR3();
void test_movImmediateMovSmallestImmediateValueToR3();
void test_movImmediateMovToR0();
void test_movImmediateMovToR7();
void test_movRegisterMoveEvenAddressIntoPC();
void test_movRegisterMoveHighRegisterToLowRegister();
void test_movRegisterMoveLowRegisterToLHighRegister();
void test_movRegisterMoveOddAddressIntoPCAndMakeSureLSbitIsCleared();
void test_movRegisterMovePCintoOtherRegister();
void test_movRegisterUseHighRegisterForAllArgs();
void test_movRegisterUseLowestRegisterForAllArgs();
void test_mulMultiplyBy16BitMaximumValues();
void test_mulUseDifferentRegistersForEachArg();
void test_mulUseHigestRegisterForAllArgs_OnlyGetLower32bitsOfResult();
void test_mulUseLowestRegisterForAllArgs();
void test_mvnRegisterMoveANegationOfNegativeOne_ClearsNegativeFlagAndSetsZeroFlag();
void test_mvnRegisterUseDifferentRegistersForEachArg();
void test_mvnRegisterUseHigestRegisterForAllArgs();
void test_mvnRegisterUseLowestRegisterForAllArgs();
void test_orrRegisterHaveAndResultNotBeSameAsEitherSource();
void test_orrRegisterOrR3andR7();
void test_orrRegisterUseHighestRegisterForBothArgs();
void test_orrRegisterUseLowestRegisterForBothArgs();
void test_orrRegisterUseOrToTurnOnNegativeSignBit();
void test_rev16RevR0toR7();
void test_rev16RevR7toR0();
void test_revRevR0toR7();
void test_revRevR7toR0();
void test_revshNegativeValue();
void test_revshPositiveValue();
void test_revshRevR0toR7();
void test_revshRevR7toR0();
void test_rorRegisterRotate0by16();
void test_rorRegisterRotate16Bits();
void test_rorRegisterRotate1by0_MinimumShift_CarryUnmodified();
void test_rorRegisterRotate1by1_CarryOutFromLowestBit();
void test_rorRegisterRotate2by1_NoCarry();
void test_rorRegisterRotateBy32_CarryOutHighestBit();
void test_rorRegisterRotateBy33();
void test_rorRegisterRotateWithMaximumShiftOf255();
void test_rorRegisterRotateWithShiftOf256_ShouldBeTreatedAs0Shift_CarryUnmodified();
void test_rorRegisterRotateWithShiftOf31();
void test_rsbImmediateForceOverflowByNegatingLargestNegativeValue();
void test_rsbImmediateUseDifferentRegistersForEachArg();
void test_rsbImmediateUseHigestRegisterOnly();
void test_rsbImmediateUseLowestRegisterOnly();
void test_sbcRegisterClearCarryToCauseABorrowToOccur();
void test_sbcRegisterForceCarryClearToIndicateBorrowAndResultWillBeNegative();
void test_sbcRegisterForceNegativeOverflow();
void test_sbcRegisterForcePositiveOverflow();
void test_sbcRegisterUseDifferentRegistersForEachArgAndOnlyCarryShouldBeSetToIndicateNoBorrow();
void test_sbcRegisterUseHigestRegisterForAllArgsAndShouldBeZeroWithCarrySetForNoBorrow();
void test_sbcRegisterUseLowestRegisterForAllArgsAndShouldBeZeroWithCarrySetForNoBorrow();
void test_subImmediateT1ForceOverflowPastLargestNegativeInteger();
void test_subImmediateT1UseDifferentRegistersForEachArg();
void test_subImmediateT1UseHigestRegisterOnly_LargestImmediate();
void test_subImmediateT1UseLowestRegisterOnly_SmallestImmediate();
void test_subImmediateT2ForceOverflowPastLargestNegativeInteger();
void test_subImmediateT2HigestRegister_LargestImmediate();
void test_subImmediateT2LowestRegisterSmallestImmediate();
void test_subImmediateT2Subtract127FromR0CausesNoCarryToIndicateBorrowAndNegativeResult();
void test_subRegisterForceCarryClearToIndicateBorrowAndResultWillBeNegative();
void test_subRegisterForceNegativeOverflow();
void test_subRegisterForcePositiveOverflow();
void test_subRegisterUseDifferentRegistersForEachArg();
void test_subRegisterUseHigestRegisterForAllArgs();
void test_subRegisterUseLowestRegisterForAllArgs();
void test_subSPLargestImmediate();
void test_subSPSmallestImmediate();
void test_subSPUseIntermediateValues();
void test_sxtbOverwriteUpperBits_NegativeValue();
void test_sxtbOverwriteUpperBits_PositiveValue();
void test_sxtbSignExtendHighestRegisterIntoLowestRegister_NegativeValue();
void test_sxtbSignExtendLowestRegisterIntoHighestRegister_PositiveValue();
void test_sxthOverwriteUpperBits_NegativeValue();
void test_sxthOverwriteUpperBits_PositiveValue();
void test_sxthSignExtendHighestRegisterIntoLowestRegister_NegativeValue();
void test_sxthSignExtendLowestRegisterIntoHighestRegister_PositiveValue();
void test_tstRegisterAndR3andR7();
void test_tstRegisterUseAndToJustKeepNegativeSignBit();
void test_tstRegisterUseHighestRegisterForBothArgsAndRegisterWillBeUnchanged();
void test_tstRegisterUseLowestRegisterForBothArgsAndResultShouldBeZero();
void test_uxtbExtendHighestRegisterIntoLowestRegister_NegativeValue();
void test_uxtbExtendLowestRegisterIntoHighestRegister_PositiveValue();
void test_uxtbOverwriteUpperBits_NegativeValue();
void test_uxtbOverwriteUpperBits_PositiveValue();
void test_uxthExtendHighestRegisterIntoLowestRegister_NegativeValue();
void test_uxthExtendLowestRegisterIntoHighestRegister_PositiveValue();
void test_uxthOverwriteUpperBits_NegativeValue();
void test_uxthOverwriteUpperBits_PositiveValue();
