SRCDIR=src
BINDIR=build
OUTDIR=out
GCC=i686-elf-gcc.exe
LINKER=i686-elf-ld.exe
TARGET=kernel
IMG=floppy.img
GRUB=grub/stage1 grub/stage2 config/pad

OBJS += \
./${BINDIR}/loader.o \
./${BINDIR}/common.o \
./${BINDIR}/monitor.o \
./${BINDIR}/kernel.o 

A_FLAGS=-f elf
C_FLAGS=-c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs
T_FLAG=-T ${SRCDIR}/linker.ld

all:	img

${BINDIR}/%.o: ${SRCDIR}/%.asm
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin Assembler Compiler'
	nasm ${A_FLAGS} -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '
	
${BINDIR}/%.o: ${SRCDIR}/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	${GCC} -o "$@" "$<" ${C_FLAGS}
	@echo 'Finished building: $<'
	@echo ' '
	
link: clean ${OBJS}
	@echo 'Linking files'
	@echo 'Invoking: Cygwin Linker'
	${LINKER} ${T_FLAG} -o ${OUTDIR}/${TARGET} ${OBJS}
	@echo 'done.'
	@echo ' '
	
img: link
	@echo 'Making floppy image'
	cat  ${GRUB} ${OUTDIR}/${TARGET} > ${OUTDIR}/${IMG}
	@echo 'done.'
	@echo ' '
	
clean:
	@echo 'Cleaning...'
	rm -f -r ${BINDIR} ${OUTDIR}/${TARGET} ${OUTDIR}/${IMG}
	mkdir build
	@echo 'done.'
	@echo ' '