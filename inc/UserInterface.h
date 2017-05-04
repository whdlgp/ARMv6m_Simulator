/*
 * UserInterface.h
 *
 *  Created on: 2016. 12. 10.
 *      Author: ygcho
 */

#ifndef INC_USERINTERFACE_H_
#define INC_USERINTERFACE_H_

#include "ctocpp.h"
#include "Memory.h"
#include "Register.h"
#include "Instruction.h"

enum
{
    EXCUTEONE = 1,
    EXCUTEALL,
    BREAKPOINT,
    STATEERROR,
    SHUTDOWN,
    SETREG,

    SETPOINT = 0,
    SHOWLIST,
};

class UserInterface
{
public :
    UserInterface()
    {
        breakpointCount = 0;
        memset(breakpointList, 0x0, MEM_MAXSIZE);
        verbose = false;
        regManualsetData[0] = 0;
        regManualsetData[1] = 0;
    }
    static UserInterface* getInstance() { return &interfaceInst; }

    void printPreface();
    void printEndMassage();
    void memPrint();

    int8_t receiveInput(uint8_t* state, uint8_t* showList, uint32_t* hex);
    int8_t inputStateMachine(uint8_t state, uint8_t showList, uint32_t hex);

    void setup(int argc, char** argv);
    void loop();
    void end();

    int8_t breakpointSet(uint32_t addr);
    void breakpointDelet(uint32_t index);

    int32_t getBreakpointCount();

    uint32_t breakpointRead(uint32_t index);
    int32_t breakpointSearch(uint32_t addr);
    void breakpointShow();

    void breakpointProcess(uint32_t addr);

    void RegisterManualSet();

    void excuteAll();

private :
    static UserInterface interfaceInst;

    bool verbose;

    uint32_t regManualsetData[2]; //if set register manually, receive register index and hex data here

    uint32_t breakpointCount;
    uint32_t breakpointList[MEM_MAXSIZE];
};

#endif /* INC_USERINTERFACE_H_ */
