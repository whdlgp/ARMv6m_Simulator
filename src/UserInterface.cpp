/*
 * UserInterface.cpp
 *
 *  Created on: 2016. 12. 10.
 *      Author: ygcho
 */

#include "UserInterface.h"

UserInterface UserInterface::interfaceInst;
Memory* mem = Memory::getInstance();
Register* reg = Register::getInstance();
Instruction* ist = Instruction::getInstance();

void UserInterface::printPreface()
{
    printf("\n   -------------------------------------------------------------\n");
    printf("   Instruction Decoder\n");
    printf("   (ARM architecture version: ARMv6-M)\n");
    printf("   -------------------------------------------------------------\n");
    printf("   AUTHOR     :   YG Cho (whdlgp@gmail.com)\n");
    printf("   VERSION    :   1.0\n");
    printf("   Copyright (c) 2016 Internet Computing Lab., SeoulTech\n");
    printf("   -------------------------------------------------------------\n\n");
    printf("   How quit this program  : just type 'q' and enter. Simple! yei!-\n");
    printf("   Show break point       : just type 'b' and enter. yei!---------\n");
    printf("   Set break point        : type 'b' and hex address, like \"b 4A\"-\n");
    printf("   Step by step debug     : just type 's' and enter. Boom!--------\n");
    printf("   Run(stop at breakpoint): just type 'r' and enter. Bang!--------\n");
    printf("   Verbose                : toogle Run verbosity with 'v'---------\n");
    printf("   Finally, it will store the memory in dumpfile!----------------\n");
}

void UserInterface::printEndMassage()
{
    printf("Everything is over. check dumpfile :(\n");
}

void UserInterface::memPrint()
{
    int i;

    if((ist->inst32 != 0x00) && (ist->inst16 == 0x00))
        printf("\nCurrent instruction: %08x ", ist->inst32);
    else if((ist->inst32 == 0x00) && (ist->inst16 != 0x00))
        printf("\nCurrent instruction: %04x ", ist->inst16);
    printf("(%s)\n", ist->getInstName());

    for(i = 0; i < 4; i++)
        printf(" reg[%d ] = 0x%08x\t", i, reg->R[i]);
    printf("\n");

    for(i = 4; i < 8; i++)
        printf(" reg[%d ] = 0x%08x\t", i, reg->R[i]);
    printf("\n");

    for(i = 8; i < 10; i++)
        printf(" reg[%d ] = 0x%08x\t", i, reg->R[i]);
    for(i = 10; i < 12; i++)
        printf(" reg[%d] = 0x%08x\t", i, reg->R[i]);
    printf("\n");

    for(i = 12; i < 16; i++)
        printf(" reg[%d] = 0x%08x\t", i, reg->R[i]);
    printf("\n");

    printf(" PC\t= 0x%08x (Next instruction)\n", reg->R[PC]);
    printf(" Flags\t= %c %c %c %c \n",  reg->PSR[psrN] ? 'N' : 'n'
                                        , reg->PSR[psrZ] ? 'Z' : 'z'
                                        , reg->PSR[psrC] ? 'C' : 'c'
                                        , reg->PSR[psrV] ? 'V' : 'v');
}

int8_t UserInterface::receiveInput(uint8_t* state, uint8_t* showList, uint32_t* hex)
{
    char str[30];
    char* inputStr[3];
    uint8_t inputCnt = 0;

    int8_t ret;

    scanf(" %[^\n]", str);
    inputStr[0] = strtok(str, " ");
    if(inputStr[0])
        inputCnt++;

    while((inputStr[inputCnt] = strtok(NULL, " ")))
    {
        inputCnt++;
    }

    if((inputCnt == 1) || (inputCnt == 2))
    {
        ret = inputCnt;

        if(!strcmp(inputStr[0], "s"))
            *state = EXCUTEONE;
        else if(!strcmp(inputStr[0], "r"))
            *state = EXCUTEALL;
        else if(!strcmp(inputStr[0], "b"))
        {
            *state = BREAKPOINT;
            if(inputCnt == 2)
            {
                *showList = 0;
                sscanf(inputStr[1], "%X", hex);
            }
            else if(inputCnt == 1)
            {
                *showList = 1;
                *hex = 0;
            }
        }
        else if(!strcmp(inputStr[0], "v"))
        {
            verbose ^= true;
            printf("verbose Run output %s\n", verbose ? "on" : "off");
        }
        else if(!strcmp(inputStr[0], "q"))
        {
            *state = SHUTDOWN;
        }
        else
        {
            *state = STATEERROR;
            ret = -1;
        }
    }
    else
    {
        *state = STATEERROR;
        ret = -1;
    }

    return ret;
}

int8_t UserInterface::inputStateMachine(uint8_t state, uint8_t showList, uint32_t hex)
{
    uint8_t exitFlag = 0;

    switch (state)
    {
    case EXCUTEONE:
        //execute one instruction
        ist->decode();
        memPrint();
        break;

    case EXCUTEALL:
        //execute instructions. if breakpoint, stop
        excuteAll();
        memPrint();
        break;

    case BREAKPOINT:
        switch (showList)
        {
        case SETPOINT:
            //set breakpoint
            breakpointProcess(hex);
            break;
        case SHOWLIST:
            //show breakpoint list
            breakpointShow();
            break;
        }
        break;
    case SHUTDOWN:
        exitFlag = 1;
        break;
    }
    return exitFlag;
}

void UserInterface::setup(int argc, char** argv)
{
    if (argc != 3)
    {
        printf("How to Use : $./(compiled program) (input file name) (dump file name)\n");
        exit(1);
    }

    printPreface();
    mem->init(argv[1], argv[2]);
    reg->init();
}

void UserInterface::loop()
{
    while ((reg->R[PC]) < (mem->instFileSize))
    {
        int8_t count = 0;
        uint8_t state = 0;
        uint8_t showList = 0;
        uint32_t hex = 0;

        //Preventing infinite repetition by instruction "B."
        if(ist->infiniteLoop)
        {
            printf("\nMeaningless repetition due to PC value change detected.\n");
            printf("It may be an infinite loop at the end of the program.\n");
            printf("If the same message is repeated, it is recommended to terminate with \'q\'.\n");
            printf("(This is caused by a command such as \"B.\")\n");
        }

        printf("\nISS Command >> ");
        if((count = receiveInput(&state, &showList, &hex)) < 0)
        {
            printf("Well,,, I think YOU're something wrong, really\n");
        }

        if(inputStateMachine(state, showList, hex))
            break;
    }
}

void UserInterface::end()
{
    mem->dumpPrint();

    printEndMassage();
}

int8_t UserInterface::breakpointSet(uint32_t addr)
{
    uint32_t i;
    int8_t retval;
    if(breakpointCount == MEM_MAXSIZE)
    {
        retval = -1;
    }
    else if(breakpointSearch(addr) < 0)
    {
        for(i = 0; i < MEM_MAXSIZE; i++)
        {
            if(breakpointList[i] == 0x0)
            {
                printf("set breakpoint\n");
                breakpointList[i] = addr;
                breakpointCount++;
                break;
            }
        }
        retval = 1;
    }
    return retval;
}

void UserInterface::breakpointDelet(uint32_t index)
{
    breakpointList[index] = 0x0;
    breakpointCount--;
}

int32_t UserInterface::getBreakpointCount()
{
    return breakpointCount;
}

uint32_t UserInterface::breakpointRead(uint32_t index)
{
    return breakpointList[index];
}

int32_t UserInterface::breakpointSearch(uint32_t addr)
{
    uint32_t i;
    int32_t retval = -1;
    for(i = 0; i < MEM_MAXSIZE; i++)
    {
        if(breakpointList[i] == addr)
        {
            retval = i;
            break;
        }
        else
            retval = -1;
    }

    return retval;
}

void UserInterface::breakpointShow()
{
    uint32_t i;
    printf("\nList of the breakpoints\n");
    for(i = 0; i < MEM_MAXSIZE; i++)
    {
        if(breakpointList[i] != 0x0)
        {
            printf("0x%X\n", breakpointList[i]);
        }
    }
    printf("If you want to add or delete a breakpoint, type like \"b 8000\".\n");
}

void UserInterface::breakpointProcess(uint32_t addr)
{
    int32_t index = breakpointSearch(addr);
    if(index < 0) //make new breakpoint
    {
        breakpointSet(addr);
    }
    else
    {
        breakpointDelet(index);
    }
}

void UserInterface::excuteAll()
{
    char str[5];

    while(1)
    {
        //Preventing infinite repetition by instruction "B."
        if(ist->infiniteLoop)
        {
            ist->infiniteLoop = 0;

            printf("\nMeaningless repetition due to PC value change detected.\n");
            printf("It may be an infinite loop at the end of the program.\n");
            printf("(This is caused by a command such as \"B.\")\n");
            printf("Do you want to exit the run command?\n");
            printf("Press 'y' and enter if you want exit the run command\n");
            printf("press any key and enter If you want to continue\n>> ");
            scanf(" %[^\n]", str);
            if(!strcmp(str, "y"))
            {
                printf("Return to command state\n");
                break;
            }
            else
                printf("That would be the best choice you made.\n");
        }
        if(breakpointSearch(reg->R[PC]) < 0)
        {
            ist->decode();
            if (verbose)
                memPrint();
        }
        else
        {
            break;
        }
    }
}

