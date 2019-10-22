# stm32_basics
Code for various projects done using the stm32L1 Discovery board. 

Prior to using the board most of my programming has been done using IDEs and not really understanding much about compilers, linkers, assemblers, etc. With this board I am trying to make my environment as transparent as possible, with as few black boxes as possible between me writing code and code going on the board. I am doing this both to understand better what is going on when code is put on a board, and to be able to work with many different boards from the same environment. 

I am using Windows 10 for these projects.

# Toolchain
My toolchain is the following:
* Compiler: GCC
* Assembler/Linker: Binutils
* C Library: Newlib
* Debugger Software: GDB
* Programmer Software: OpenOCD
* Debugger/Programmer: ST-Link/V2
* Build Automation: Make

GCC, Binutils, Newlib, and GDB I got directly from ARM in the GNU Arm toolchain:

https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm

I installed make and OpenOCD using a package manager for Windows called Chocolatey:

https://chocolatey.org/

After installation all you have to do is give the following commands to command prompt/powershell:

chocolatey install make
chocolatey install openocd

