/*
 * Instruction.cpp
 *
 *  Created on: 2016. 12. 9.
 *      Author: ygcho
 */

#include "Instruction.h"
#include "Memory.h"
#include "Register.h"

#define LSL 0
#define LSR 1
#define ROR 2

Instruction Instruction::instInst;

static Memory* mem = Memory::getInstance();
static Register* reg = Register::getInstance();

void Instruction::instName(const char* name)
{
    strncpy(currentInst, name, 20);
}

char* Instruction::getInstName()
{
    return currentInst;
}

uint8_t Instruction::getOpcode16(uint16_t inst)
{
    return (inst >> 10) & 0x3F;
}

uint8_t Instruction::getMSB(uint32_t inst)
{
    return ((inst) >> 31) & 0x01;
}
uint8_t Instruction::getZERO(uint32_t inst)
{
    return (inst) ? 0x0 : 0x1;
}

uint32_t Instruction::addWithCarry(uint32_t op1, uint32_t op2, uint32_t carryInAsBit)
{
    int carryIn = carryInAsBit ? 1 : 0;
    uint64_t unsignedSum = (uint64_t)op1 + (uint64_t)op2 + (uint64_t)carryIn;
    int64_t signedSum = (int64_t)(int32_t)op1 + (int64_t)(int32_t)op2 + (int64_t)carryIn;
    uint32_t result = (uint32_t)unsignedSum;

    reg->PSR[psrC] = ((uint64_t)result == unsignedSum) ? 0 : 1;
    reg->PSR[psrV] = ((int64_t)(int32_t)result == signedSum) ? 0 : 1;

    return result;
}

uint32_t Instruction::shiftC(uint32_t value, uint8_t type, uint32_t shift, uint32_t carryIn)
{
    uint32_t result = value;
    reg->PSR[psrC] = carryIn;

    if (shift != 0)
    {
        switch (type)
        {
        case LSL:
             reg->PSR[psrC] = (shift > 32) ? 0 : value & (1 << (32 - shift));
             result = (shift > 31) ? 0 : value << shift;
             break;
        case LSR:
             reg->PSR[psrC] = (shift > 32) ? 0 : (value & (1 << (shift - 1)));
             result = (shift > 31) ? 0 : value >> shift;
             break;
        case ROR:
             uint32_t m = shift & 31U;
             result = ((m > 32) ? 0 : (value & (1 << (m - 1)))) | (((32-m) > 32) ? 0 : value & (1 << m));
             reg->PSR[psrC] = result & (1 << 31);
             break;
        }
    }

    return result;
}

uint8_t Instruction::bitCount(uint32_t bitString)
{
    uint8_t i;
    uint8_t count = 0;

    for(i = 0; i < 32; i++)
    {
        if(((bitString >> i) & 0x01) == 0x01)
        {
            count++;
        }
    }

    return count;
}

int32_t Instruction::signedExt(uint8_t bitNum, uint32_t data)
{
    uint32_t extBit = 0xffffffff;
    uint8_t highestBit = (data >> (bitNum - 2)) & 0x01;
    if(highestBit == 0x1)
    {
        return (extBit << bitNum) | data;
    }
    else
    {
        return data;
    }
}

uint32_t Instruction::align(uint32_t op1,uint32_t op2)
{
    return op2*(op1/op2);
}

void Instruction::decode()
{
    uint8_t readOP = (mem->read2Byte(reg->R[PC]) >> 11) & 0x1f;
    uint32_t currentPC = 0;

    currentPC = reg->R[PC];
    reg->R[PC] += 4; //Once the PC value is +4.
    if((readOP == 0x1D) || (readOP == 0x1E) || (readOP == 0x1F))
    {
        process32((mem->read2Byte(currentPC) << 16) | mem->read2Byte(currentPC+2));
        reg->updatePC();
    }
    else
    {
        process16(mem->read2Byte(currentPC));

        //For the 16-bit command, the next address is 2 bytes behind
        //If it is +4 as it is, it will be 4 bytes behind.
        //So let's do -2.
        reg->R[PC] -= 2;
        reg->updatePC();
    }
}

void Instruction::process32(uint32_t inst)
{
    inst32 = inst;
    inst16 = 0;

    uint8_t op1 = (inst >> 27) & 0x03;
    uint8_t op = (inst >> 15) & 0x01;

    if((op1 == 0x02) && (op == 0x01))
    {
       class32bit(inst);
    }
    else
    {
        instName("UNKNOWN");
    }
}

void Instruction::process16(uint16_t inst)
{
    inst32 = 0;
    inst16 = inst;

    uint8_t opcode = getOpcode16(inst);

    if(((opcode >> 4) & 0x03) == 0x00)
        class16bit1(inst);

    else if(opcode == 0x10)
        class16bit2(inst);

    else if(opcode == 0x11)
        class16bit3(inst);

    else if(((opcode >> 1) & 0x1f) == 0x09)
        class16bit4(inst);

    else if((((opcode >> 2) & 0x0f) == 0x05)
            ||(((opcode >> 3) & 0x07) == 0x03)
            ||(((opcode >> 3) & 0x07) == 0x04))
        class16bit5(inst);

    else if(((opcode >> 1) & 0x1f) == 0x14)
        class16bit6(inst);

    else if(((opcode >> 1) & 0x1f) == 0x15)
        class16bit7(inst);

    else if(((opcode >> 2) & 0x0f) == 0x0b)
        class16bit8(inst);

    else if(((opcode >> 1) & 0x1f) == 0x18)
        class16bit9(inst);

    else if(((opcode >> 1) & 0x1f) == 0x19)
        class16bit10(inst);

    else if(((opcode >> 2) & 0x0f) == 0x0d)
        class16bit11(inst);

    else if(((opcode >> 1) & 0x1f) == 0x1c)
        class16bit12(inst);

    else
    {
        printf("16bit instruction parse error\n");
        instName("UNKNOWN");
    }
}

void Instruction::class32bit(uint32_t inst)
{
    uint8_t op2 = (inst >> 12) & 0x07;

    if((op2 == 0x07) || (op2 == 0x05))
    {
        //BL
        instName("BL");
        bl(inst);
    }
    else
    {
        instName("UNKNOWN");
    }
}

void Instruction::class16bit1(uint16_t inst)
{
    //Shift, add, sub, mov, compare
    uint8_t opcode = (inst >> 9) & 0x1f;
    uint8_t opcode3bit = (opcode >> 2) & 0x07;

    if(opcode3bit == 0x00)
    {
        //lsl
        instName("LSL (immediate)");
        lsl_imme(inst);
    }
    else if(opcode3bit == 0x01)
    {
        //lsr
        instName("LSR (immediate)");
        lsr_imme(inst);
    }
    else if(opcode3bit == 0x02)
    {
        //asr
        instName("ASR (immediate)");
        asr_imme(inst);
    }
    else if(opcode == 0x0c)
    {
        //add register
        instName("ADD (register)");
        add_register(inst);
    }
    else if(opcode == 0x0d)
    {
        //sub register
        instName("SUB (register)");
        sub_register(inst);
    }
    else if(opcode == 0x0e)
    {
        //add 3bit imme
        instName("ADD (immediate)");
        add_3bit_imme(inst);
    }
    else if(opcode == 0x0f)
    {
        //sub 3bit imme
        instName("SUB (immediate)");
        sub_3bit_imme(inst);
    }
    else if(opcode3bit == 0x04)
    {
        //mov
        instName("MOV (immediate)");
        mov_imme(inst);
    }
    else if(opcode3bit == 0x05)
    {
        //cmp
        instName("CMP (immediate)");
        cmp_imme(inst);
    }
    else if(opcode3bit == 0x06)
    {
        //add 8bit imme
        instName("ADD (immediate)");
        add_8bit_imme(inst);
    }
    else if(opcode3bit == 0x07)
    {
        //sub 8bit imme
        instName("SUB (immediate)");
        sub_8bit_imme(inst);
    }
    else
    {
        instName("UNKNOWN");
    }
}

void Instruction::class16bit2(uint16_t inst)
{
    //Data processing

    uint8_t opcode = (inst >> 6) & 0x0f;

    switch(opcode)
    {
        case 0x0 :
            //and
            instName("AND (register)");
            and_register(inst);
            break;
        case 0x1 :
            //eor(xor)
            instName("EOR (register)");
            eor_register(inst);
            break;
        case 0x2 :
            //lsl
            instName("LSL (register)");
            lsl_register(inst);
            break;
        case 0x3 :
            //lsr
            instName("LSR (register)");
            lsr_register(inst);
            break;
        case 0x4 :
            //asr
            instName("ASR (register)");
            asr_register(inst);
            break;
        case 0x5 :
            //adc
            instName("ADC (register)");
            adc_register(inst);
            break;
        case 0x6 :
            //sbc
            instName("SBC (register)");
            sbc_register(inst);
            break;
        case 0x7 :
            //ror
            instName("ROR (register)");
            ror_register(inst);
            break;
        case 0x8 :
            //tst
            instName("TST (register)");
            tst_register(inst);
            break;
        case 0x9 :
            //rsb
            instName("RSB (immediate)");
            rsb_imme(inst);
            break;
        case 0xa :
            //cmp
            instName("CMP (register)");
            cmp_register(inst);
            break;
        case 0xb :
            //cmn
            instName("CMN (register)");
            cmn_register(inst);
            break;
        case 0xc :
            //orr
            instName("ORR (register)");
            orr_register(inst);
            break;
        case 0xd :
            //mul
            instName("MUL (register)");
            mul_two_register(inst);
            break;
        case 0xe :
            //bic
            instName("BIC (register)");
            bic_register(inst);
            break;
        case 0xf :
            //mvn
            instName("MVN (register)");
            mvn_register(inst);
            break;
        default :
            instName("UNKNOWN");
            break;
    }
}

void Instruction::class16bit3(uint16_t inst)
{
    //Special data instruction, branch, exchange

    uint8_t opcode = (inst >> 6) & 0x0f;

    if(((opcode >> 2) & 0x03) == 0x00)
    {
        //add register
        instName("ADD (register)");
        add_register_nonsp(inst);
    }
    else if(opcode == 0x04)
    {
        //알 수 없음
        instName("UNKNOWN");
    }
    else if((opcode == 0x05) || (((opcode >> 1) & 0x07) == 0x03))
    {
        //compare register
        instName("CMP (register)");
        cmp_register_n(inst);
    }
    else if(((opcode >> 2) & 0x03) == 0x02)
    {
        //move register
        instName("MOV (register)");
        mov_register_nons(inst);
    }
    else if(((opcode >> 1) & 0x07) == 0x06)
    {
        //Branch, exchange (BX)
        instName("BX");
        bx(inst);
    }
    else if(((opcode >> 1) & 0x07) == 0x07)
    {
        //Branch, link, exchange (BLX)
        instName("BLX");
        blx(inst);
    }
    else
    {
        instName("UNKNOWN");
    }
}

void Instruction::class16bit4(uint16_t inst)
{
    //LDR literal
    instName("LDR (literal)");
    ldr_literal(inst);
}

void Instruction::class16bit5(uint16_t inst)
{
    //load, store single data

    uint8_t opA = (inst >> 12) & 0x0f;
    uint8_t opB = (inst >> 9) & 0x07;
    uint8_t opB1bit = (opB >> 2) & 0x01;

    if(opA == 0x05)
    {
        switch(opB)
        {
            case 0x0:
                //STR
                instName("STR (register)");
                str_register(inst);
                break;
            case 0x1:
                //STRH
                instName("STRH (register)");
                strh_register(inst);
                break;
            case 0x2:
                //STRB
                instName("STRB (register)");
                strb_register(inst);
                break;
            case 0x3:
                //LDRSB
                instName("LDRSB (register)");
                ldrsb_register(inst);
                break;
            case 0x4:
                //LDR
                instName("LDR (register)");
                ldr_register(inst);
                break;
            case 0x5:
                //LDRH
                instName("LDRH (register)");
                ldrh_register(inst);
                break;
            case 0x6:
                //LDRB
                instName("LDRB (register)");
                ldrb_register(inst);
                break;
            case 0x7:
                //LDRSH
                instName("LDRSH (register)");
                ldrsh_register(inst);
                break;
            default :
                instName("UNKNOWN");
                break;
        }
    }
    else if(opA == 0x06)
    {
        if(opB1bit == 0x0)
        {
            //STR imme
            instName("STR (immediate)");
            str_imme(inst);
        }
        else if(opB1bit == 0x1)
        {
            //LDR imme
            instName("LDR (immediate)");
            ldr_imme(inst);
        }
        else
        {
            instName("UNKNOWN");
        }
    }
    else if(opA == 0x07)
    {
        if(opB1bit == 0x0)
        {
            //STRB imme
            instName("STRB (immediate)");
            strb_imme(inst);
        }
        else if(opB1bit == 0x1)
        {
            //LDRB imme
            instName("LDRB (immediate)");
            ldrb_imme(inst);
        }
        else
        {
            instName("UNKNOWN");
        }
    }
    else if(opA == 0x08)
    {
        if(opB1bit == 0x0)
        {
            //STRH
            instName("STRH (immediate)");
            strh_imme(inst);
        }
        else if(opB1bit == 0x1)
        {
            //LDRH
            instName("LDRH (immediate)");
            ldrh_imme(inst);
        }
        else
        {
            instName("UNKNOWN");
        }
    }
    else if(opA == 0x09)
    {
        if(opB1bit == 0x0)
        {
            //STR sp-relative
            instName("STR (SP-relative)");
            str_sp(inst);
        }
        else if(opB1bit == 0x1)
        {
            //LDR sp-relative
            instName("LDR (SP-relative)");
            ldr_sp(inst);
        }
        else
        {
            instName("UNKNOWN");
        }
    }
    else
    {
        instName("UNKNOWN");
    }
}

void Instruction::class16bit6(uint16_t inst)
{
    //generate PC-relative addr, ADR
    instName("ADR (PC-relative)");
    adr_pc(inst);
}

void Instruction::class16bit7(uint16_t inst)
{
    //generate SP-relative addr, ADD
    instName("ADD (SP-relative)");
    add_sp(inst);
}

void Instruction::class16bit8(uint16_t inst)
{
    //Miscellaneous

    uint8_t opcode7 = (inst >> 5) & 0x7f;
    uint8_t opcode6 = (opcode7 >> 1) & 0x3f;
    uint8_t opcode5 = (opcode7 >> 2) & 0x1f;
    uint8_t opcode4 = (opcode7 >> 3) & 0x0f;
    uint8_t opcode3 = (opcode7 >> 4) & 0x07;

    if(opcode5 == 0x00)
    {
        //add imme to sp
        instName("ADD (SP-relative)");
        add_to_sp(inst);
    }
    else if(opcode5 == 0x01)
    {
        //sub imme to sp
        instName("SUB (SP-relative)");
        sub_to_sp(inst);
    }
    else if(opcode6 == 0x08)
    {
        //signed ext halfword
        instName("SXTH");
        sxth(inst);
    }
    else if(opcode6 == 0x09)
    {
        //signed ext byte
        instName("SXTB");
        sxtb(inst);
    }
    else if(opcode6 == 0x0a)
    {
        //unsigned ext halfword
        instName("UXTH");
        uxth(inst);
    }
    else if(opcode6 == 0x0b)
    {
        //unsigned ext byte
        instName("UXTB");
        uxtb(inst);
    }
    else if(opcode3 == 0x02)
    {
        //push multiple register
        instName("PUSH (multi)");
        push_mult(inst);
    }
    else if(opcode7 == 0x33)
    {
        //CPS
        instName("CPS");
        //fukup
    }
    else if(opcode6 == 0x28)
    {
        //REV
        instName("REV");
        rev(inst);
    }
    else if(opcode6 == 0x29)
    {
        //REV16
        instName("REV16");
        rev16(inst);
    }
    else if(opcode6 == 0x2b)
    {
        //REVSH
        instName("REVSH");
        revsh(inst);
    }
    else if(opcode3 == 0x06)
    {
        //POP multiple register
        instName("POP (multi)");
        pop_mult(inst);
    }
    else if(opcode4 == 0x0e)
    {
        //BKPT break point
        instName("BKTP");
        //fukup
    }
    else if(opcode4 == 0x0f)
    {
        //hint
        instName("HINT");
        hint(inst);
    }
    else
    {
        instName("UNKNOWN");
    }
}

void Instruction::class16bit9(uint16_t inst)
{
    //STM, STMIA, STMEA
    instName("STM");
    stm(inst);
}

void Instruction::class16bit10(uint16_t inst)
{
    //LDM, LDMIA, LDMFD
    instName("LDM");
    ldm(inst);
}

void Instruction::class16bit11(uint16_t inst)
{
    //Conditional Branch, Supervisor call

    uint8_t opcode4 = (inst >> 8) & 0x0f;
    uint8_t opcode3 = (opcode4 >> 1) & 0x07;

    if(opcode3 != 0x07)
    {
        //Conditional B
        instName("B (conditional)");
        b_cond(inst);
    }
    else
    {
        if(opcode4 == 0x0e)
        {
            //UDF
            instName("UDF");
            //fukup
        }
        else if(opcode4 == 0x0f)
        {
            //SVC
            instName("SVC");
            //fukup
        }
        else
        {
            instName("UNKNOWN");
        }
    }
}

void Instruction::class16bit12(uint16_t inst)
{
    //Unconditional Branch, B
    instName("B (unconditional)");
    b_uncond(inst);
}

void Instruction::lsl_imme(uint16_t inst)
{
    uint8_t rd = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;
    uint8_t imme = (inst >> 6) & 0x1f;

    reg->R[rd] = shiftC(reg->R[rm], LSL, imme, reg->PSR[psrC]);

    reg->PSR[psrN] = (reg->R[rd] >> 31) & 0x01;
    reg->PSR[psrZ] = reg->R[rd] ? 0x0 : 0x1;
}

void Instruction::lsr_imme(uint16_t inst)
{
    uint8_t rd = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;
    uint8_t imme = (inst >> 6) & 0x1f;

    imme = (imme == 0) ? 32 : imme;

    reg->R[rd] = shiftC(reg->R[rm], LSR, imme, reg->PSR[psrC]);

    reg->PSR[psrN] = (reg->R[rd] >> 31) & 0x01;
    reg->PSR[psrZ] = reg->R[rd] ? 0x0 : 0x1;
}

void Instruction::asr_imme(uint16_t inst)
{
    uint8_t i;
    uint8_t msb;

    uint8_t rd = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;
    uint8_t imme = (inst >> 6) & 0x1f;

    msb = reg->R[rd] & 0x80000000;
    for(i = 1; i <= imme; i++)
    {
        reg->R[rd] = reg->R[rm] >> 1;
        reg->R[rd] |= msb;
    }

    reg->PSR[psrN] = (reg->R[rd] >> 31) & 0x01;
    reg->PSR[psrZ] = reg->R[rd] ? 0x0 : 0x1;
    reg->PSR[psrC] = (reg->R[rm] >> (imme-1)) & 0x01;
}

void Instruction::add_register(uint16_t inst)
{
    uint8_t rd = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t rm = (inst >> 6) & 0x07;

    reg->R[rd] = addWithCarry(reg->R[rn], reg->R[rm], 0);

    reg->PSR[psrN] = getMSB(reg->R[rd]);
    reg->PSR[psrZ] = getZERO(reg->R[rd]);
}

void Instruction::sub_register(uint16_t inst)
{
    uint8_t rd = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t rm = (inst >> 6) & 0x07;

    reg->R[rd] = addWithCarry(reg->R[rn], ~reg->R[rm], 1);

    reg->PSR[psrN] = getMSB(reg->R[rd]);
    reg->PSR[psrZ] = getZERO(reg->R[rd]);
}

void Instruction::add_3bit_imme(uint16_t inst)
{
    uint8_t rd = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t imm3 = (inst >> 6) & 0x07;

    reg->R[rd] = addWithCarry(reg->R[rn], imm3, 0);

    reg->PSR[psrN] = getMSB(reg->R[rd]);
    reg->PSR[psrZ] = getZERO(reg->R[rd]);
}

void Instruction::sub_3bit_imme(uint16_t inst)
{
    uint8_t rd = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t imm3 = (inst >> 6) & 0x07;
    uint64_t result = 0x0;

    reg->R[rd] = addWithCarry(reg->R[rn], ~imm3, 1);

    reg->PSR[psrN] = getMSB(reg->R[rd]);
    reg->PSR[psrZ] = getZERO(reg->R[rd]);
}

void Instruction::mov_imme(uint16_t inst)
{
    uint8_t imm8 = inst & 0xff;
    uint8_t rd = (inst >> 8) & 0x07;

    reg->R[rd] = imm8;

    reg->PSR[psrN] = getMSB(reg->R[rd]);
    reg->PSR[psrZ] = getZERO(reg->R[rd]);
}

void Instruction::cmp_imme(uint16_t inst)
{
    uint8_t imm8 = inst & 0xff;
    uint8_t rn = (inst >> 8) & 0x07;
    uint64_t result = 0x0;

    result = addWithCarry(reg->R[rn], ~imm8, 1) & 0xffffffff;

    reg->PSR[psrN] = getMSB(result);
    reg->PSR[psrZ] = getZERO(result);
}

void Instruction::add_8bit_imme(uint16_t inst)
{
    uint8_t imm8 = inst & 0xff;
    uint8_t rdn = (inst >> 8) & 0x07;
    uint64_t result = 0x0;
    uint32_t rdnTemp = reg->R[rdn];

    reg->R[rdn] = addWithCarry(rdnTemp, imm8, 0);

    reg->PSR[psrN] = getMSB(reg->R[rdn]);
    reg->PSR[psrZ] = getZERO(reg->R[rdn]);
}

void Instruction::sub_8bit_imme(uint16_t inst)
{
    uint8_t imm8 = inst & 0xff;
    uint8_t rdn = (inst >> 8) & 0x07;
    uint64_t result = 0x0;
    uint32_t rdnTemp = reg->R[rdn];

    reg->R[rdn] = addWithCarry(rdnTemp, ~imm8, 1);

    reg->PSR[psrN] = getMSB(reg->R[rdn]);
    reg->PSR[psrZ] = getZERO(reg->R[rdn]);
}

void Instruction::and_register(uint16_t inst)
{
    uint8_t rdn = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;

    reg->R[rdn] = reg->R[rm] & reg->R[rdn];

    reg->PSR[psrN] = getMSB(reg->R[rdn]);
    reg->PSR[psrZ] = getZERO(reg->R[rdn]);
}

void Instruction::eor_register(uint16_t inst)
{
    uint8_t rdn = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;

    reg->R[rdn] = reg->R[rm] ^ reg->R[rdn];

    reg->PSR[psrN] = getMSB(reg->R[rdn]);
    reg->PSR[psrZ] = getZERO(reg->R[rdn]);
}

void Instruction::lsl_register(uint16_t inst)
{
    uint8_t rdn = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;
    uint8_t shift = reg->R[rm] & 0xff;

    reg->R[rdn] = shiftC(reg->R[rdn], LSL, shift, reg->PSR[psrC]);

    reg->PSR[psrN] = (reg->R[rdn] >> 31) & 0x01;
    reg->PSR[psrZ] = reg->R[rdn] ? 0x0 : 0x1;
}

void Instruction::lsr_register(uint16_t inst)
{
    uint8_t rdn = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;
    uint8_t shift = reg->R[rm] & 0xff;

    reg->R[rdn] = shiftC(reg->R[rdn], LSR, shift, reg->PSR[psrC]);

    reg->PSR[psrN] = (reg->R[rdn] >> 31) & 0x01;
    reg->PSR[psrZ] = reg->R[rdn] ? 0x0 : 0x1;
}

void Instruction::asr_register(uint16_t inst)
{
    uint8_t i;
    uint8_t msb;

    uint8_t rdn = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;
    uint32_t rdnTemp = reg->R[rdn];

    msb = reg->R[rdn] & 0x80000000;
    for(i = 1; i <= reg->R[rm]; i++)
    {
        reg->R[rdn] = reg->R[rdn] >> 1;
        reg->R[rdn] |= msb;
    }

    reg->PSR[psrN] = (reg->R[rdn] >> 31) & 0x01;
    reg->PSR[psrZ] = reg->R[rdn] ? 0x0 : 0x1;
    reg->PSR[psrC] = (rdnTemp >> (reg->R[rm]-1)) & 0x01;
}

void Instruction::adc_register(uint16_t inst)
{
    uint8_t rdn = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;
    uint32_t rdnTemp = reg->R[rdn];

    reg->R[rdn] = addWithCarry(rdnTemp, reg->R[rm], reg->PSR[psrC]);

    reg->PSR[psrN] = getMSB(reg->R[rdn]);
    reg->PSR[psrZ] = getZERO(reg->R[rdn]);
}

void Instruction::sbc_register(uint16_t inst)
{
    uint8_t rdn = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;
    uint32_t rdnTemp = reg->R[rdn];

    reg->R[rdn] = addWithCarry(rdnTemp, ~reg->R[rm], reg->PSR[psrC]);

    reg->PSR[psrN] = getMSB(reg->R[rdn]);
    reg->PSR[psrZ] = getZERO(reg->R[rdn]);
}

void Instruction::ror_register(uint16_t inst)
{
    uint8_t rdn = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;
    uint8_t shift = reg->R[rm] & 0xff;

    reg->R[rdn] = shiftC(reg->R[rdn], ROR, shift, reg->PSR[psrC]);

    reg->PSR[psrN] = getMSB(reg->R[rdn]);
    reg->PSR[psrZ] = getZERO(reg->R[rdn]);
}

void Instruction::tst_register(uint16_t inst)
{
    uint8_t rn = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;
    uint32_t result = 0x0;

    result = reg->R[rm] & reg->R[rn];

    reg->PSR[psrN] = getMSB(result);
    reg->PSR[psrZ] = getZERO(result);
}

void Instruction::rsb_imme(uint16_t inst)
{
    uint8_t rd = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint64_t result = 0x0;

    reg->R[rd] = addWithCarry(~reg->R[rn], 0, 1);

    reg->PSR[psrN] = getMSB(reg->R[rd]);
    reg->PSR[psrZ] = getZERO(reg->R[rd]);
}

void Instruction::cmp_register(uint16_t inst)
{
    uint8_t rn = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;
    uint64_t result = 0x0;

    result = addWithCarry(reg->R[rn], ~reg->R[rm], 1);

    reg->PSR[psrN] = getMSB(result);
    reg->PSR[psrZ] = getZERO(result);
}

void Instruction::cmn_register(uint16_t inst)
{
    uint8_t rn = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;
    uint32_t result = 0x0;

    result = addWithCarry(reg->R[rn], reg->R[rm], 0);

    reg->PSR[psrN] = getMSB(result);
    reg->PSR[psrZ] = getZERO(result);
}

void Instruction::orr_register(uint16_t inst)
{
    uint8_t rdn = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;

    reg->R[rdn] = reg->R[rm] | reg->R[rdn];

    reg->PSR[psrN] = getMSB(reg->R[rdn]);
    reg->PSR[psrZ] = getZERO(reg->R[rdn]);
}

void Instruction::mul_two_register(uint16_t inst)
{
    uint8_t rdm = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;

    reg->R[rdm] = reg->R[rn] * reg->R[rdm];

    reg->PSR[psrN] = getMSB(reg->R[rdm]);
    reg->PSR[psrZ] = getZERO(reg->R[rdm]);
}

void Instruction::bic_register(uint16_t inst)
{
    uint8_t rdn = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;

    reg->R[rdn] = reg->R[rdn] & (~reg->R[rm]);

    reg->PSR[psrN] = getMSB(reg->R[rdn]);
    reg->PSR[psrZ] = getZERO(reg->R[rdn]);
}

void Instruction::mvn_register(uint16_t inst)
{
    uint8_t rd = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;

    reg->R[rd] = ~reg->R[rm];

    reg->PSR[psrN] = getMSB(reg->R[rd]);
    reg->PSR[psrZ] = getZERO(reg->R[rd]);
}

void Instruction::add_register_nonsp(uint16_t inst)
{
    uint8_t rdn = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x0f;
    uint8_t dn = (inst >> 7) & 0x01;
    uint8_t dnrdn = (dn << 3) | rdn;

    reg->R[dnrdn] = addWithCarry(reg->R[dnrdn], reg->R[rm], 0);

    reg->PSR[psrN] = getMSB(reg->R[dnrdn]);
    reg->PSR[psrZ] = getZERO(reg->R[dnrdn]);
}

void Instruction::cmp_register_n(uint16_t inst)
{
    uint8_t rn = ((inst & (1 << 7)) >> 4) | (inst & 0x7);
    uint8_t rm = (inst & (0xf << 3)) >> 3;
    uint64_t result = 0x0;

    result = addWithCarry(reg->R[rn], ~reg->R[rm], 1);

    reg->PSR[psrN] = getMSB(result);
    reg->PSR[psrZ] = getZERO(result);
}

void Instruction::mov_register_nons(uint16_t inst)
{
    uint8_t rd = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x0f;
    uint8_t d = (inst >> 7) & 0x01;
    uint8_t drd = (d << 3) | rd & 0xf;

    reg->R[drd] = reg->R[rm];
}

void Instruction::bx(uint16_t inst)
{
    uint8_t rm = (inst >> 3) & 0x0f;

    reg->throwPC(reg->R[rm]);
}

void Instruction::blx(uint16_t inst)
{
    uint8_t rm = (inst >> 3) & 0x0f;

    reg->R[LR] = ((reg->R[PC] - 2) & 0xfffffffe) | 0x01;

    reg->throwPC(reg->R[rm]);
}

void Instruction::ldr_literal(uint16_t inst)
{
    uint8_t imm8 = inst & 0xff;
    uint8_t rt = (inst >> 8) & 0x07;
    uint32_t base = align(reg->R[PC],4);

    reg->R[rt] = mem->read4Byte(base + (imm8 << 2));
}

void Instruction::str_register(uint16_t inst)
{
    uint8_t rt = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t rm = (inst >> 6) & 0x07;

    uint32_t addr = reg->R[rn] + reg->R[rm];

    mem->write4Byte(addr, reg->R[rt]);
}

void Instruction::strh_register(uint16_t inst)
{
    uint8_t rt = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t rm = (inst >> 6) & 0x07;

    uint32_t addr = reg->R[rn] + reg->R[rm];

    mem->write2Byte(addr, reg->R[rt] & 0xffff);
}

void Instruction::strb_register(uint16_t inst)
{
    uint8_t rt = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t rm = (inst >> 6) & 0x07;

    uint32_t addr = reg->R[rn] + reg->R[rm];

    mem->writeByte(addr, reg->R[rt] & 0xff);
}

void Instruction::ldrsb_register(uint16_t inst)
{
    uint8_t rt = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t rm = (inst >> 6) & 0x07;
    int32_t signeddata;

    uint32_t addr = reg->R[rn] + reg->R[rm];

    signeddata = (int8_t)(mem->readByte(addr));

    reg->R[rt] = (uint32_t)signeddata;
}

void Instruction::ldr_register(uint16_t inst)
{
    uint8_t rt = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t rm = (inst >> 6) & 0x07;

    uint32_t addr = reg->R[rn] + reg->R[rm];

    reg->R[rt] = mem->read4Byte(addr);
}

void Instruction::ldrh_register(uint16_t inst)
{
    uint8_t rt = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t rm = (inst >> 6) & 0x07;

    uint32_t addr = reg->R[rn] + reg->R[rm];

    reg->R[rt] = mem->read2Byte(addr);
}

void Instruction::ldrb_register(uint16_t inst)
{
    uint8_t rt = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t rm = (inst >> 6) & 0x07;

    uint32_t addr = reg->R[rn] + reg->R[rm];

    reg->R[rt] = mem->readByte(addr);
}

void Instruction::ldrsh_register(uint16_t inst)
{
    uint8_t rt = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t rm = (inst >> 6) & 0x07;
    uint32_t signeddata;
    uint32_t addr = reg->R[rn] + reg->R[rm];

    signeddata = (int16_t)(mem->read2Byte(addr));
    reg->R[rt] = (uint32_t)signeddata;
}

void Instruction::str_imme(uint16_t inst)
{
    uint8_t rt = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t imm5 = (inst >> 6) & 0x1f;
    uint32_t addr = reg->R[rn] + (imm5 << 2);

    mem->write4Byte(addr, reg->R[rt]);
}

void Instruction::ldr_imme(uint16_t inst)
{
    uint8_t rt = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t imm5 = (inst >> 6) & 0x1f;
    uint32_t addr = reg->R[rn] + (imm5 << 2);

    reg->R[rt] = mem->read4Byte(addr);
}

void Instruction::strb_imme(uint16_t inst)
{
    uint8_t rt = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t imm5 = (inst >> 6) & 0x1f;
    uint32_t addr = reg->R[rn] + imm5;

    mem->writeByte(addr, reg->R[rt] & 0xff);
}

void Instruction::ldrb_imme(uint16_t inst)
{
    uint8_t rt = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t imm5 = (inst >> 6) & 0x1f;
    uint32_t addr = reg->R[rn] + imm5;

    reg->R[rt] = mem->readByte(addr);
}

void Instruction::strh_imme(uint16_t inst)
{
    uint8_t rt = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t imm5 = (inst >> 6) & 0x1f;
    uint32_t addr = reg->R[rn] + (imm5 << 1);

    mem->write2Byte(addr, reg->R[rt] & 0xffff);
}

void Instruction::ldrh_imme(uint16_t inst)
{
    uint8_t rt = inst & 0x07;
    uint8_t rn = (inst >> 3) & 0x07;
    uint8_t imm5 = (inst >> 6) & 0x1f;
    uint32_t addr = reg->R[rn] + (imm5 << 1);

    reg->R[rt] = mem->read2Byte(addr);
}

void Instruction::str_sp(uint16_t inst)
{
    uint8_t imm8 = inst & 0xff;
    uint8_t rt = (inst >> 8) & 0x07;
    uint32_t addr = reg->R[SP] + (imm8 << 2);

    mem->write4Byte(addr, reg->R[rt]);
}

void Instruction::ldr_sp(uint16_t inst)
{
    uint8_t imm8 = inst & 0xff;
    uint8_t rt = (inst >> 8) & 0x07;
    uint32_t addr = reg->R[SP] + (imm8 << 2);

    reg->R[rt] = mem->read4Byte(addr);
}

void Instruction::adr_pc(uint16_t inst)
{
    uint8_t imm8 = inst & 0xff;
    uint8_t rd = (inst >> 8) & 0x07;

    reg->R[rd] = align(reg->R[PC],4) + (imm8 << 2);
}

void Instruction::add_sp(uint16_t inst)
{
    uint8_t imm8 = inst & 0xff;
    uint8_t rd = (inst >> 8) & 0x07;

    reg->R[rd] = reg->R[SP] + (imm8 << 2);
}

void Instruction::add_to_sp(uint16_t inst)
{
    uint8_t imm7 = inst & 0x7f;

    reg->R[SP] = reg->R[SP] + (imm7 << 2);
}

void Instruction::sub_to_sp(uint16_t inst)
{
    uint8_t imm7 = inst & 0x7f;

    reg->R[SP] = reg->R[SP] - (imm7 << 2);
}

void Instruction::sxth(uint16_t inst)
{
    uint8_t rd = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;
    int32_t signeddata;

    signeddata = (int16_t)(reg->R[rm] & 0xffff);

    reg->R[rd] = signeddata;
}

void Instruction::sxtb(uint16_t inst)
{
    uint8_t rd = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;
    int32_t signeddata;

    signeddata = (int8_t)(reg->R[rm] & 0xff);

    reg->R[rd] = signeddata;
}

void Instruction::uxth(uint16_t inst)
{
    uint8_t rd = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;

    reg->R[rd] = reg->R[rm] & 0xffff;
}

void Instruction::uxtb(uint16_t inst)
{
    uint8_t rd = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;

    reg->R[rd] = reg->R[rm] & 0xff;
}

void Instruction::push_mult(uint16_t inst)
{
    uint16_t register_list = inst & 0xff;
    uint16_t m = (inst >> 8) & 0x01;

    uint16_t stack_data_list = (m << 14) | register_list;
    uint32_t addr = reg->R[SP] - 4*bitCount(stack_data_list);

    uint8_t i;
    for(i = 0; i < 15; i++)
    {
        if(((stack_data_list >> i) & 0x01) == 0x01)
        {
            mem->write4Byte(addr, reg->R[i]);
            addr += 4;
        }
    }

    reg->R[SP] = reg->R[SP] - 4*bitCount(stack_data_list);
}

void Instruction::rev(uint16_t inst)
{
    uint8_t rd = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;

    uint32_t result = 0;
    uint8_t rmbyte[4];
    rmbyte[0] = (reg->R[rm] & 0xff);
    rmbyte[1] = ((reg->R[rm] >> 8) & 0xff);
    rmbyte[2] = ((reg->R[rm] >> 16) & 0xff);
    rmbyte[3] = ((reg->R[rm] >> 24) & 0xff);

    result = (rmbyte[0] << 24)
             | (rmbyte[1] << 16)
             | (rmbyte[2] << 8)
             | rmbyte[3];

    reg->R[rd] = result;
}

void Instruction::rev16(uint16_t inst)
{
    uint8_t rd = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;

    uint32_t result = 0;
    uint8_t rmbyte[4];
    rmbyte[0] = (reg->R[rm] & 0xff);
    rmbyte[1] = ((reg->R[rm] >> 8) & 0xff);
    rmbyte[2] = ((reg->R[rm] >> 16) & 0xff);
    rmbyte[3] = ((reg->R[rm] >> 24) & 0xff);

    result = (rmbyte[2] << 24)
             | (rmbyte[3] << 16)
             | (rmbyte[0] << 8)
             | rmbyte[1];

    reg->R[rd] = result;
}

void Instruction::revsh(uint16_t inst)
{
    uint8_t rd = inst & 0x07;
    uint8_t rm = (inst >> 3) & 0x07;

    int32_t signeddata = 0;
    uint32_t unsigneddata = 0;
    uint8_t rmbyte[2];
    rmbyte[0] = (reg->R[rm] & 0xff);
    rmbyte[1] = ((reg->R[rm] >> 8) & 0xff);

    signeddata = (int8_t)rmbyte[0];
    unsigneddata = (uint32_t)signeddata;

    reg->R[rd] = (unsigneddata << 8) | rmbyte[1];
}

void Instruction::pop_mult(uint16_t inst)
{
    uint8_t register_list = inst & 0xff;
    uint8_t p = (inst >> 8) & 0x01;

    uint32_t addr = reg->R[SP];
    uint8_t i;

    for(i = 0; i < 8; i++)
    {
        if(((register_list >> i) & 0x01) == 0x01)
        {
            reg->R[i] = mem->read4Byte(addr);
            addr += 4;
        }
    }

    if(p == 0x01)
    {
        reg->throwPC(mem->read4Byte(addr));
    }

    reg->R[SP] = reg->R[SP] + 4*(bitCount(register_list) + bitCount(p));
}

void Instruction::hint(uint16_t inst)
{
    //fukup
}

void Instruction::stm(uint16_t inst)
{
    uint8_t register_list = inst & 0xff;
    uint8_t rn = (inst >> 8) & 0x07;

    uint32_t addr = reg->R[rn];

    uint8_t i;
    for(i = 0; i < 8; i ++)
    {
        if(((register_list >> i) & 0x01) == 0x01)
        {
            mem->write4Byte(addr, reg->R[i]);
            addr += 4;
        }
    }

    reg->R[rn] = reg->R[rn] + 4*bitCount(register_list);
}

void Instruction::ldm(uint16_t inst)
{
    uint16_t register_list = inst & 0xff;
    uint8_t rn = (inst >> 8) & 0x07;

    uint32_t addr = reg->R[rn];

    uint8_t i;
    for(i = 0; i < 8; i++)
    {
        if(((register_list >> i) & 0x01) == 0x01)
        {
            reg->R[i] = mem->read4Byte(addr);
            addr += 4;
        }
    }

    if(((register_list >> rn) & 0x01) == 0)
        reg->R[rn] = reg->R[rn] + 4*bitCount(register_list);
}

void Instruction::b_cond(uint16_t inst)
{
    uint8_t imm8 = inst & 0xff;
    uint8_t cond = (inst >> 8) & 0x0f;

    uint32_t data = imm8 << 1;
    int32_t imm32 = (((int32_t)imm8) << 24) >> 23;

    if(reg->checkCond(cond))
    {
        reg->throwPC(reg->R[PC] + imm32);
    }
}

void Instruction::b_uncond(uint16_t inst)
{
    uint16_t imm11 = inst & 0x7ff;
    uint32_t data = imm11 << 1;

    int32_t imm32 = (((int32_t)imm11) << 21) >> 20;
    uint32_t addr = reg->R[PC] + imm32;

    reg->throwPC(addr);

    //무한반복 명령어가 들어왔을 경우
    if(addr == (reg->R[PC] - 4))
        infiniteLoop = 1;
}

void Instruction::bl(uint32_t inst)
{
    uint16_t imm11 = inst & 0x7ff;
    uint8_t j2 = (inst >> 11) & 0x01;
    uint8_t j1 = (inst >> 13) & 0x01;
    uint16_t imm10 = (inst >> 16) & 0x3ff;
    uint8_t s = (inst >> 26) & 0x01;

    uint8_t i1 = (~(j1 ^ s)) & 0x01;
    uint8_t i2 = (~(j2 ^ s)) & 0x01;
    uint32_t data = ((s << 24)
                    | (i1 << 23)
                    | (i2 << 22)
                    | (imm10 << 12)
                    | (imm11 << 1));
    int32_t imm32;
    imm32 = signedExt(25, data);

    reg->R[LR] = (reg->R[PC] & 0xfffffffe) | 0x01;

    reg->throwPC(reg->R[PC] + imm32);
}
