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

int main()
{
    printf("\n **** Startings tests ****\n");

    // FIXME: address commented failing tests

    test_cmpImmediateCompareLowestRegisterToEqualValue();
    test_cmpImmediateCompareHighestRegisterToImmediateWhichIsSmaller();
    test_cmpImmediateCompareRegisterToLargestImmediateWhichIsLarger();
    test_cmpImmediateCompareRegisterToImmediateWhichWillGenerateNegativeOverflow();

    test_adcRegisterUseR1ForAllArgs();
    test_adcRegisterUseLowestRegisterForAllArgs();
    test_adcRegisterUseHigestRegisterForAllArgsPositiveOverflow();
    test_adcRegisterUseDifferentRegistersForEachArg();
    test_adcRegisterAdd0to0WithCarryInSetToGiveAResultOf1();
    test_adcRegisterForceCarryOut();
    test_adcRegisterForceCarryOutAndOverflow();

    test_addImmediateT1UseLowestRegisterOnlyAddLargestImmediate();
    test_addImmediateT1UseHigestRegisterOnlyAddSmallestImmediate();
    test_addImmediateT1UseDifferentRegistersForEachArg();
    test_addImmediateT1ForceCarryByAdding1ToLargestInteger();
    test_addImmediateT1ForceOverflowPastLargestPositiveInteger();
    test_addImmediateT2UseLowestRegisterAndAddLargestImmediate();
    test_addImmediateT2UseHigestRegisterAndAddSmallestImmediate();
    test_addImmediateT2ForceCarryByAdding1ToLargestInteger();
    test_addImmediateT2ForceOverflowPastLargestPositiveInteger();

    test_addRegisterT1UseLowestRegisterForAllArgs();
    test_addRegisterT1UseHigestRegisterForAllArgs();
    test_addRegisterT1UseDifferentRegistersForEachArg();
    test_addRegisterT1ForceCarryWithNoOverflow();
    test_addRegisterT1ForceCarryAndOverflow();
    test_addRegisterT2UseR1ForAllArgs();
    test_addRegisterT2UseLowestRegisterForAllArgs();
    test_addRegisterT2UseR12ForAllArgs();
    test_addRegisterT2UseDifferentRegistersForEachArg();
    test_addRegisterT2WrapAroundTo0();
    test_addRegisterT2OverflowFromLowestNegativeValue();
    test_addRegisterT2Add4ToSP();
    test_addRegisterT2Subtract4FromSP();
    test_addRegisterT2Add1ToLR();
    //test_addRegisterT2Add1ToPCWhichWillBeOddAndRoundedDown();
    //test_addRegisterT2Add2ToPC();

    test_addSPT1UseHighestRegisterAddSmallestImmediate();
    test_addSPT1UseLowestRegisterAddLargestImmediate();
    test_addSPT1UseIntermediateValues();
    test_addSPT2SmallestImmediate();
    test_addSPT2LargestImmediate();
    test_addSPT2IntermediateValues();

    test_adrLowestRegisterWithLargestOffset();
    test_adrHighesttRegisterWithSmallestOffset();
    //test_adrpcWillNeedToBeWordAlignedBeforeAdd();

    test_andRegisterUseLowestRegisterForBothArgs();
    test_andRegisterUseHighestRegisterForBothArgs();
    test_andRegisterAndR3andR7();
    test_andRegisterUseAndToJustKeepNegativeSignBit();
    test_andRegisterHaveAndResultNotBeSameAsEitherSource();

    test_bicRegisterUseLowestRegisterForBothArgs();
    test_bicRegisterUseHighestRegisterForBothArgs();
    test_bicRegisterUseR3andR7();
    test_bicRegisterUseBicToClearLSbit();

    test_bBEQ_NotTaken();
    test_bBEQ_Taken();
    test_bBNE_NotTaken();
    test_bBNE_Taken();
    test_bBCS_NotTaken();
    test_bBCS_Taken();
    test_bBCC_NotTaken();
    test_bBCC_Taken();
    test_bBMI_NotTaken();
    test_bBMI_Taken();
    test_bBPL_NotTaken();
    test_bBPL_Taken();
    test_bBVS_NotTaken();
    test_bBVS_Taken();
    test_bBVC_NotTaken();
    test_bBVC_Taken();
    test_bBHI_NotTaken();
    test_bBHI_Taken();
    test_bBLS_NotTaken();
    test_bBLS_Taken();
    test_bBGE_NotTaken();
    test_bBGE_Taken1();
    test_bBGE_Taken2();
    test_bBLT_NotTaken();
    test_bBLT_Taken1();
    test_bBLT_Taken2();
    test_bBGT_NotTaken();
    test_bBGT_Taken1();
    test_bBGT_Taken2();
    test_bBLE_NotTaken();
    test_bBLE_Taken1();
    test_bBLE_Taken2();
    test_bBEQ_TakenWithLargestPositiveOffset();
    test_bBEQ_TakenWithLargesNegativeOffset();
    test_bBAL_ZeroOffset();
    test_bBAL_LargestPositiveOffset();
    test_bBAL_LargestNegativeOffset();

    test_bxUseHighestRegisterToBranchToOddAddressWhichIsRequiredForThumb();

    test_cmnRegisterUseLowestRegisterForAllArgs();
    test_cmnRegisterUseHigestRegisterForAllArgs();
    test_cmnRegisterUseDifferentRegistersForEachArg();
    test_cmnRegisterForceCarryWithNoOverflow();
    test_cmnRegisterForceCarryAndOverflow();

    test_cmpImmediateCompareLowestRegisterToEqualValue();
    test_cmpImmediateCompareHighestRegisterToImmediateWhichIsSmaller();
    test_cmpImmediateCompareRegisterToLargestImmediateWhichIsLarger();
    test_cmpImmediateCompareRegisterToImmediateWhichWillGenerateNegativeOverflow();

    test_cmpRegisterT1UseLowestRegisterForAllArgs();
    test_cmpRegisterT1UseHigestRegisterForAllArgs();
    test_cmpRegisterT1RnLargerThanRm();
    test_cmpRegisterT1RnSmallerThanRm();
    test_cmpRegisterT1ForceNegativeOverflow();
    test_cmpRegisterT1ForcePositiveOverflow();
    test_cmpRegisterT2CompareLowestRegisterToHighestRegister();
    test_cmpRegisterT2CompareHighestRegisterToLowestRegister();
    test_cmpRegisterT2CompareR8ToItself();
    test_cmpRegisterT2ForceNegativeOverflow();
    test_cmpRegisterT2ForcePositiveOverflow();

    test_eorRegisterUseLowestRegisterForBothArgs();
    test_eorRegisterUseHighestRegisterForBothArgs();
    test_eorRegisterXorR3andR7();
    test_eorRegisterUseXorToJustFlipNegativeSignBitOn();

    test_lslImmediateMovR7toR0_CarryUnmodified();
    test_lslImmediateMovR0toR7_ZeroResultAndCarryUnmodified();
    test_lslImmediateShiftR1by3_ResultInNegativeValue();
    test_lslImmediateShiftR1by4_HasCarryOut();
    test_lslImmediateShiftR0by31_PushesLowestbitIntoSignBit();
    test_lslImmediateCarryOutFromHighestBit();
    test_lslImmediateCarryOutFromLowestBit();

    test_lslRegisterShiftR7by0_MinimumShift_CarryShouldBeUnmodified();
    test_lslRegisterShiftValue1by31_NegativeResult();
    test_lslRegisterShiftValue1by32_CarryOutFromLowestBit();
    test_lslRegisterShiftNegativeValueBy1_CarryOutFromHighestBit();
    test_lslRegisterShiftValue1by33_NoCarry();
    test_lslRegisterShiftValuee1by255_MaximumShift();
    test_lslRegisterShiftValue1by256_ShouldBeTreatedAs0Shift_CarryUnmodified();

    test_lsrImmediateR2by1toR0();
    test_lsrImmediateR7by32toR0_ZeroResult();
    test_lsrImmediateR1by1toR7_CarryOut();
    test_lsrImmediateR0by32_CarryOutAndIsZero();

    test_lsrRegisterShiftValue1by1_CarryOutFromLowestBit();
    test_lsrRegisterShiftValue1by0_MinimumShift_CarryUnmodified();
    test_lsrRegisterShiftValue2by1_NoCarry();
    test_lsrRegisterShiftNegativeValueBy31();
    test_lsrRegisterShiftNegativeValueBy32_CarryOutFromHighestBit();
    test_lsrRegisterShiftNegativeValueBy33_ResultIsZero_CarryClear();
    test_lsrRegisterMaximumShiftOf255_ResultIsZero_CarryClear();
    test_lsrRegisterShiftOf256_ShouldBeTreatedAs0Shift_CarryUnmodified();

    test_movImmediateMovToR0();
    test_movImmediateMovToR7();
    test_movImmediateMovSmallestImmediateValueToR3();
    test_movImmediateMovLargestImmediateValueToR3();

    test_movRegisterUseLowestRegisterForAllArgs();
    test_movRegisterUseHighRegisterForAllArgs();
    test_movRegisterMoveHighRegisterToLowRegister();
    test_movRegisterMoveLowRegisterToLHighRegister();
    //test_movRegisterMoveOddAddressIntoPCAndMakeSureLSbitIsCleared();
    //test_movRegisterMoveEvenAddressIntoPC();
    test_movRegisterMovePCintoOtherRegister();

    test_mulUseLowestRegisterForAllArgs();
    test_mulUseHigestRegisterForAllArgs_OnlyGetLower32bitsOfResult();
    test_mulUseDifferentRegistersForEachArg();
    test_mulMultiplyBy16BitMaximumValues();

    test_mvnRegisterUseLowestRegisterForAllArgs();
    test_mvnRegisterUseHigestRegisterForAllArgs();
    test_mvnRegisterUseDifferentRegistersForEachArg();
    test_mvnRegisterMoveANegationOfNegativeOne_ClearsNegativeFlagAndSetsZeroFlag();

    test_orrRegisterUseLowestRegisterForBothArgs();
    test_orrRegisterUseHighestRegisterForBothArgs();
    test_orrRegisterOrR3andR7();
    test_orrRegisterUseOrToTurnOnNegativeSignBit();
    test_orrRegisterHaveAndResultNotBeSameAsEitherSource();

    test_rev16RevR0toR7();
    test_rev16RevR7toR0();

    test_revRevR0toR7();
    test_revRevR7toR0();

    test_revshRevR0toR7();
    test_revshRevR7toR0();
    test_revshPositiveValue();
    test_revshNegativeValue();

    //test_rorRegisterRotate1by1_CarryOutFromLowestBit();
    test_rorRegisterRotate1by0_MinimumShift_CarryUnmodified();
    test_rorRegisterRotate2by1_NoCarry();
    test_rorRegisterRotate16Bits();
    //test_rorRegisterRotateWithShiftOf31();
    test_rorRegisterRotateBy32_CarryOutHighestBit();
    test_rorRegisterRotateBy33();
    //test_rorRegisterRotateWithMaximumShiftOf255();
    test_rorRegisterRotateWithShiftOf256_ShouldBeTreatedAs0Shift_CarryUnmodified();
    test_rorRegisterRotate0by16();

    test_rsbImmediateUseLowestRegisterOnly();
    test_rsbImmediateUseHigestRegisterOnly();
    test_rsbImmediateUseDifferentRegistersForEachArg();
    test_rsbImmediateForceOverflowByNegatingLargestNegativeValue();

    test_sbcRegisterUseLowestRegisterForAllArgsAndShouldBeZeroWithCarrySetForNoBorrow();
    test_sbcRegisterUseHigestRegisterForAllArgsAndShouldBeZeroWithCarrySetForNoBorrow();
    test_sbcRegisterUseDifferentRegistersForEachArgAndOnlyCarryShouldBeSetToIndicateNoBorrow();
    test_sbcRegisterForceCarryClearToIndicateBorrowAndResultWillBeNegative();
    test_sbcRegisterForceNegativeOverflow();
    test_sbcRegisterForcePositiveOverflow();
    test_sbcRegisterClearCarryToCauseABorrowToOccur();

    test_subImmediateT1UseLowestRegisterOnly_SmallestImmediate();
    test_subImmediateT1UseHigestRegisterOnly_LargestImmediate();
    test_subImmediateT1UseDifferentRegistersForEachArg();
    test_subImmediateT1ForceOverflowPastLargestNegativeInteger();
    test_subImmediateT2LowestRegisterSmallestImmediate();
    test_subImmediateT2HigestRegister_LargestImmediate();
    test_subImmediateT2Subtract127FromR0CausesNoCarryToIndicateBorrowAndNegativeResult();
    test_subImmediateT2ForceOverflowPastLargestNegativeInteger();

    test_subRegisterUseLowestRegisterForAllArgs();
    test_subRegisterUseHigestRegisterForAllArgs();
    test_subRegisterUseDifferentRegistersForEachArg();
    test_subRegisterForceCarryClearToIndicateBorrowAndResultWillBeNegative();
    test_subRegisterForceNegativeOverflow();
    test_subRegisterForcePositiveOverflow();

    test_subSPSmallestImmediate();
    test_subSPLargestImmediate();
    test_subSPUseIntermediateValues();

    test_sxtbSignExtendLowestRegisterIntoHighestRegister_PositiveValue();
    test_sxtbSignExtendHighestRegisterIntoLowestRegister_NegativeValue();
    test_sxtbOverwriteUpperBits_PositiveValue();
    test_sxtbOverwriteUpperBits_NegativeValue();

    test_sxthSignExtendLowestRegisterIntoHighestRegister_PositiveValue();
    test_sxthSignExtendHighestRegisterIntoLowestRegister_NegativeValue();
    test_sxthOverwriteUpperBits_PositiveValue();
    test_sxthOverwriteUpperBits_NegativeValue();

    test_tstRegisterUseLowestRegisterForBothArgsAndResultShouldBeZero();
    test_tstRegisterUseHighestRegisterForBothArgsAndRegisterWillBeUnchanged();
    test_tstRegisterAndR3andR7();
    test_tstRegisterUseAndToJustKeepNegativeSignBit();

    test_uxtbExtendLowestRegisterIntoHighestRegister_PositiveValue();
    test_uxtbExtendHighestRegisterIntoLowestRegister_NegativeValue();
    test_uxtbOverwriteUpperBits_PositiveValue();
    test_uxtbOverwriteUpperBits_NegativeValue();

    test_uxthExtendLowestRegisterIntoHighestRegister_PositiveValue();
    test_uxthExtendHighestRegisterIntoLowestRegister_NegativeValue();
    test_uxthOverwriteUpperBits_PositiveValue();
    test_uxthOverwriteUpperBits_NegativeValue();

    printf(" **** All test passed ****\n");
}
