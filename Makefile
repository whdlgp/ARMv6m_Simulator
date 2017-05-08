all:
	g++ -o ARMv6m_Simulator -I./inc/ src/*

test:
	g++ -o test_ARMv6m_Simulator -I./inc/ src/Instruction.cpp src/Memory.cpp src/Register.cpp src/UserInterface.cpp tests/*
