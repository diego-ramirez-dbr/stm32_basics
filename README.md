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

We will also need to download some board and core specific software. I got mine from this page:

https://www.st.com/en/development-tools/stm32cubemx.html#tools-software

I downloaded the package for my board from the embedded software section. This download will include all board necessary system files, a startup file, and a linker file.

# Using the Toolchain
Most of the toolchain we've set up is for building a project from source files. Another way of saying this is interpreting source files into a format that can be loaded onto our microcontroller. As mentioned above we will use GCC for compiling, and some of the tools included in binutils for assembling/linking. I won't discuss very much what that means exactly here, but basically we are using these tools to go from source files to executable files. I found this source very helpful with regards to what is happening in the build process:

https://www.oreilly.com/library/view/programming-embedded-systems/0596009836/ch03.html

After a file that can be used to program the board is generated, we use OpenOCD to interact with the ST-LINK/V2 to program the board. All of the above ends up being a lot of commands to run everytime we want to program our board, so we use the program Make to do it all with one command.

# Make
Make automates actions that a user gives the computer. It condenses any amount of actions the user would like to take into single commands. These commands are specified in a makefile. We'll review the makefile from the led_blink project to get an understanding of makefiles and of the commands we need to run to program the board:

https://github.com/senorsandia/stm32_basics/blob/master/led_blink/src/makefile

Before going into the specifics though we'll review the general structure of a makefile.

The main component in a makefile is the rule. A rule specifies a command that will call the rule, files that the rule depends on, and what the rule should do when it is called. A rule looks like the following:

target: dependencies
  commands to make target

A rule can be called by typing "make target" into the command prompt, or by another rule calling the target in its dependencies. When the rule is called, Make will check the directory it is in for the dependencies associated with the rule, and attempt to make the files from other rules if they do not exist. Make will then execute the commands in the rule. Running the command make from a directory with a makefile in it will call the first rule which shows up in the file.

The only other thing to note is that makefiles have string variables. These are defined like so:

STRING_VAR = string

And these variables are used like this:

$(STRING_VAR)

There is a lot more to Make, but this is enough for our purposes. I found the following Make review helpful:

https://www3.nd.edu/~zxu2/acms60212-40212/Makefile.pdf

And for more in depth information the GNU Make documentation is very helpful.

# Makefile Breakdown

The two major things that happen in the makefile are the C code, header files, startup file, and linker file are used to create an executable file, and the executable file is loaded onto the microcontroller. 

The creation of the executable file is done with this rule:

%.elf: $(STARTUP) $(SRCS) $(DEVICE_DIR)/stm32l152rctx_flash.ld
	$(CC) -o $@ $(CFLAGS) -D $(DEVICE) -I $(DEVICE_DIR) -I $(CMSIS_DIR) -I $(PROJ_HEADERS) -Wl,-T $(DEVICE_DIR)/stm32l152rctx_flash.ld $^
  
We'll start with the target, %.elf. The percent sign is a wildcard character, so this target matches any amount of text followed by .elf. This means that if a .elf file is included in the dependencies of a rule (i.e. the rule for programming the board) this rule will be called.
Next we have the dependencies, which are composed of the files that are needed to build the executable file including main.c, the startup file, and the linker file.
Finally we have the actual GCC command. Most of the arguments that are given to GCC are GCC flags which can be identified from this list:

https://gcc.gnu.org/onlinedocs/gcc/Option-Summary.html

We'll leave it to the reader to go over the flags and figure out what they do, but we will talk about some pieces of Make syntax included here. The first is -o $@. -o is a GCC flag that tells gcc where to put the output, and the argument passed to it is the Make syntax $@. $@ is a variable that means the name of the target of the rule, so the output of GCC will be the statement that called the rule (i.e. main.elf). The second is $^ from the end of the GCC line. GCC takes files in, and these are placed at the end of the line. The $^ variable means all of the dependencies (i.e. $(STARTUP) $(SRCS) and $(DEVICE_DIR)/stm32l152rctx_flash.ld). 

Now that we've gone over how the executable file is created we will go over how it is loaded onto the microcontroller:

program: $(PROJ_NAME).elf
			openocd -f board/$(OOCD_BOARD) \
					-c "init" -c "targets" -c "halt" \
					-c "flash write_image erase $(PROJ_NAME).elf" \
					-c "verify_image $(PROJ_NAME).elf" \
					-c "reset run" \
					-c "shutdown"

The dependency for this rule calls the %.elf rule we just went over. The commands all work together to write the .elf file to the microcontroller, this is explained on this page:

http://openocd.org/doc/html/Flash-Programming.html

And that is it, when you run the program rule it will run the %.elf rule which will create main.elf, then the program rule will load that onto the microcontroller.
