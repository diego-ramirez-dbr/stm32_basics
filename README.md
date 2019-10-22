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

# Using the Toolchain
Most of the toolchain we've set up is for building a project from source files. Another way of saying this is interpreting source files into a format that can be loaded onto our microcontroller. As mentioned above we will use GCC for compiling, and some of the tools included in binutils for assembling/linking. I won't discuss very much what that means exactly here, but basically we are using these tools to go from source files to executable files. I found this source very helpful with regards to what is happening in the build process:

https://www.oreilly.com/library/view/programming-embedded-systems/0596009836/ch03.html

After a file that can be used to program the board is generated, we use OpenOCD to interact with the ST-LINK/V2 to program the board. All of the above ends up being a lot of commands to run everytime we want to program our board, so we use the program Make to do it all with one command.

# Make
Make automates actions that a user gives the computer. It condenses any amount of actions the user would like to take into a single command. These commands are specified in a makefile. We'll review the makefile from the led_blink project to get an understanding of makefiles and of the commands we need to run to program the board:

https://github.com/senorsandia/stm32_basics/blob/master/led_blink/src/makefile

