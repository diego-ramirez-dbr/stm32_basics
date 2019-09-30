# stm32_basics
Code for various projects done using the stm32L1 Discovery board. 

Prior to using the board most of my programming has been done using IDEs and not really understanding much about compilers, linkers, assemblers, etc. With this board I am trying to make my environment as transparent as possible, with as few black boxes as possible between me writing code and code going on the board, and as versatile as possible.

# Toolchain
My toolchain is the following:
* Debugger: GDB
* Compiler: GCC
* Assembler/Linker: Binutils
* C Library: Newlib
* Build Automation: Make
* Programmer Software: OpenOCD
