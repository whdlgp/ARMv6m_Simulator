/*
 * main.cpp
 *
 *  Created on: 2016. 12. 9.
 *      Author: ygcho
 */

#include "UserInterface.h"

UserInterface* UI = UserInterface::getInstance();

int main(int argc, char** argv)
{
    //Routines that run only once to initialize memory and registers
    UI->setup(argc, argv);

    //A routine that receives user input and determines how to perform the instruction and executes it.
    UI->loop();

    //Routines that must be executed before the instruction simulator is terminated
    UI->end();

    return 0;
}

