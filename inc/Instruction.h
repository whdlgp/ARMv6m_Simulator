/*
 * Instruction.h
 *
 *  Created on: 2016. 12. 9.
 *      Author: ygcho
 */

#ifndef INC_INSTRUCTION_H_
#define INC_INSTRUCTION_H_

#include "ctocpp.h"

#define borrowCheckBit 0x100000000

class Instruction
{
public :
    Instruction()
    {
        inst16 = 0;
        inst32 = 0;
        infiniteLoop = 0;
    }
    static Instruction* getInstance() {return &instInst;}

    uint8_t infiniteLoop;
    uint16_t inst16;
    uint16_t inst32;

    void decode();

    void instName(const char* name);
    char* getInstName();
private :
    static Instruction instInst;

    char currentInst[20];

    uint8_t getOpcode16(uint16_t );

    uint8_t getMSB(uint32_t inst);
    uint8_t getZERO(uint32_t inst);

    uint8_t getCarry(uint64_t result);
    uint8_t getBorrow(uint64_t result);
    uint8_t getOverflow(uint32_t op1, uint32_t op2, uint32_t result);
    uint8_t bitCount(uint32_t bitString);
    int32_t signedExt(uint8_t bitNum, uint32_t data);

    uint32_t align(uint32_t op1,uint32_t op2);

    void process32(uint32_t inst);
    void process16(uint16_t inst);

    void class32bit(uint32_t inst);

    void class16bit1(uint16_t inst);    //Shift, add, sub, mov, compare
    void class16bit2(uint16_t inst);    //Data processing
    void class16bit3(uint16_t inst);    //Special data instruction, branch, exchange
    void class16bit4(uint16_t inst);    //LDR
    void class16bit5(uint16_t inst);    //load, store single data
    void class16bit6(uint16_t inst);    //generate PC-relative addr, ADR
    void class16bit7(uint16_t inst);    //generate SP-relative addr, ADD
    void class16bit8(uint16_t inst);    //Miscellaneous
    void class16bit9(uint16_t inst);    //STM, STMIA, STMEA
    void class16bit10(uint16_t inst);   //LDM, LDMIA, LDMFD
    void class16bit11(uint16_t inst);   //Conditional Branch, Supervisor call
    void class16bit12(uint16_t inst);   //Unconditional Branch, B

    void lsl_imme(uint16_t inst);
    void lsr_imme(uint16_t inst);
    void asr_imme(uint16_t inst);
    void add_register(uint16_t inst);
    void sub_register(uint16_t inst);
    void add_3bit_imme(uint16_t inst);
    void sub_3bit_imme(uint16_t inst);
    void mov_imme(uint16_t inst);
    void cmp_imme(uint16_t inst);
    void add_8bit_imme(uint16_t inst);
    void sub_8bit_imme(uint16_t inst);

    void and_register(uint16_t inst);
    void eor_register(uint16_t inst);
    void lsl_register(uint16_t inst);
    void lsr_register(uint16_t inst);
    void asr_register(uint16_t inst);
    void adc_register(uint16_t inst);
    void sbc_register(uint16_t inst);
    void ror_register(uint16_t inst);
    void tst_register(uint16_t inst);
    void rsb_imme(uint16_t inst);
    void cmp_register(uint16_t inst);
    void cmn_register(uint16_t inst);
    void orr_register(uint16_t inst);
    void mul_two_register(uint16_t inst);
    void bic_register(uint16_t inst);
    void mvn_register(uint16_t inst);

    void add_register_nonsp(uint16_t inst);
    void cmp_register_n(uint16_t inst);
    void mov_register_nons(uint16_t inst);
    void bx(uint16_t inst);
    void blx(uint16_t inst);

    void ldr_literal(uint16_t inst);

    void str_register(uint16_t inst);
    void strh_register(uint16_t inst);
    void strb_register(uint16_t inst);
    void ldrsb_register(uint16_t inst);
    void ldr_register(uint16_t inst);
    void ldrh_register(uint16_t inst);
    void ldrb_register(uint16_t inst);
    void ldrsh_register(uint16_t inst);
    void str_imme(uint16_t inst);
    void ldr_imme(uint16_t inst);
    void strb_imme(uint16_t inst);
    void ldrb_imme(uint16_t inst);
    void strh_imme(uint16_t inst);
    void ldrh_imme(uint16_t inst);
    void str_sp(uint16_t inst);
    void ldr_sp(uint16_t inst);

    void adr_pc(uint16_t inst);
    void add_sp(uint16_t inst);

    void add_to_sp(uint16_t inst);
    void sub_to_sp(uint16_t inst);
    void sxth(uint16_t inst);
    void sxtb(uint16_t inst);
    void uxth(uint16_t inst);
    void uxtb(uint16_t inst);
    void push_mult(uint16_t inst);
    void rev(uint16_t inst);
    void rev16(uint16_t inst);
    void revsh(uint16_t inst);
    void pop_mult(uint16_t inst);
    void hint(uint16_t inst);

    void stm(uint16_t inst);
    void ldm(uint16_t inst);

    void b_cond(uint16_t inst);
    void b_uncond(uint16_t inst);

    void bl(uint32_t inst);
};



#endif /* INC_INSTRUCTION_H_ */
