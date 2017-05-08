# ARMv6m_Simulator
Simple Simulator of ARMv6m instructions

The ARMv6m Simulator is a simulator for testing ARMv6m instruction sets. You can use STEP execution, breakpoint, etc. in CLI environment by using bin file compiled with armv6m compiler.

## Scope Supported
### Mode
Only support Thread mode
### Supported Instruction
#### 16bit Instruction
* ADC
* ADD
* ADR
* AND
* ASR
* B
* BIC
* BLX
* BX
* CMN
* CMP
* EOR
* LDM
* LDR
* LDRH
* LDRSH
* LDRB
* LDRSB
* LSL
* LSR
* MOV
* MVN
* MUL
* NOP
* ORR
* POP
* PUSH
* REV
* REV16
* REVSH
* ROR
* RSB
* SBC
* STM
* STR
* STRH
* STRB
* SUB
* SXTB
* SXTH
* TST
* UXTB
* UXTH

#### 32bit Instruction
* BL

### Points to consider when using

* ONLY Thread Mode
* Do Not consider: Pipeline, Cycle Timing, Exceptions, Memory Map
* Just consider : R0 ~ R15, NZCV flags

### Usage
* How quit this program  : just type 'q' and enter.
* Show break point       : just type 'b' and enter.
* Set break point        : type 'b'   and hex address ("b 4A")
* Set register           : type 'R n' and hex address ("R 1 4A")
* Show memory            : type 'd'   and hex address ("d 4A")
* Step by step debug     : just type 's' and enter.
* Run(stop at breakpoint): just type 'r' and enter.
* Verbose                : toogle Run verbosity with 'v'
* Finally, it will store the memory in dumpfile!

![example image1](http://i.imgur.com/4O15uYH.png)

### Compilation and execution

* Testsuite:

```
make test
./test_ARMv6m_Simulator
```

* Simulator:

```
make
./ARMv6m_Simulator
How to Use : $./(compiled program) (input file name) (dump file name)
```

### Contact
ChoYG  
whdlgp@gmail.com
