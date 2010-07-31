SRCDIR=src
BINDIR=build
OUTDIR=out
GCC=i686-elf-gcc.exe
GXX=i686-elf-g++.exe
LINKER=i686-elf-ld.exe
TARGET=kernel
IMG=floppy.img
GRUB=grub/stage1 grub/stage2 grub/pad

#OBJS += ./${BINDIR}/main.o ./${BINDIR}/kernel.o ./${BINDIR}/Prova.o ./${BINDIR}/cppspec.o 


A_FLAGS=-f elf
CC_FLAGS=-c -O4 -m32 -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs
CXX_FLAGS=-c -O4 -m32 -Wall -Wextra -nostdlib -fno-builtin -nostartfiles -nodefaultlibs -fno-exceptions -fno-rtti
T_FLAG=-T ${SRCDIR}/link.ld -nostdlib -nostartfiles -nodefaultlibs

all: img

include ${SRCDIR}/make.inc

#include src/asm/make.inc
#include src/boot/make.inc
#include src/common/make.inc
#include src/fs/make.inc
#include src/hw/make.inc
#include src/hw/cpu/make.inc
#include src/hw/io/make.inc
#include src/hw/memory/make.inc
#include src/hw/video/make.inc
#include src/kernel/make.inc
#include src/std/make.inc
#include src/utils/make.inc


${BINDIR}/%.o: ${SRCDIR}/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin Assembler Compiler'
	nasm ${A_FLAGS} -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
${BINDIR}/%.o: ${SRCDIR}/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C Compiler'
	${GCC} -o "$@" "$<" ${CC_FLAGS}
	@echo 'Finished building: $<'
	@echo ' '	
	
${BINDIR}/%.o: ${SRCDIR}/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	${GXX} -o "$@" "$<" ${CXX_FLAGS}
	@echo 'Finished building: $<'
	@echo ' '
	
link: ${OBJS}
	@echo 'Linking files'
	@echo 'Invoking: Cygwin Linker'
	${GXX} ${T_FLAG} -o ${OUTDIR}/${TARGET} ${OBJS}
	@echo 'done.'
	@echo ' '
	
img: link
	@echo 'Making floppy image'
	@./initrd.sh ${OUTDIR}/pad_kernel
	@cat  ${GRUB} ${OUTDIR}/${TARGET} ${OUTDIR}/pad_kernel initrd.img > ${OUTDIR}/${IMG}
	@echo 'Kernel blocks'
	@du out/kernel -b --block-size=512
	@echo 'Initrd blocks'
	@du initrd.img -b --block-size=512
	@echo 'done.'
	@echo ' '
	
clean:
	@echo 'Cleaning...' 
	rm -rf ${BINDIR}/* ${OUTDIR}/*
	@for dir in ${DIRS}; \
	do \
		echo mkdir -p ${BINDIR}/$$dir; \
		mkdir -p ${BINDIR}/$$dir; \
	done
	@echo 'done.'
	@echo ' '