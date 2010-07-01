SRCDIR=src
BINDIR=build
OUTDIR=out
GCC=i686-elf-gcc.exe
LINKER=i686-elf-ld.exe
TARGET=kernel
IMG=floppy.img
GRUB=grub/stage1 grub/stage2 grub/pad

#./${BINDIR}/loader.o \#
OBJS += \
./${BINDIR}/asm/gdt.o \
./${BINDIR}/hw/io.o \
./${BINDIR}/hw/memory.o \
./${BINDIR}/hw/screen.o \
./${BINDIR}/utils/string.o \
./${BINDIR}/boot.o \
./${BINDIR}/kernel.o


A_FLAGS=-f elf
C_FLAGS=-c -Wall -Wextra -nostdlib -nostartfiles -nodefaultlibs
T_FLAG=-T ${SRCDIR}/link.ld

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
	
link: ${OBJS}
	@echo 'Linking files'
	@echo 'Invoking: Cygwin Linker'
	${LINKER} ${T_FLAG} -o ${OUTDIR}/${TARGET} ${OBJS}
	@echo 'done.'
	@echo ' '
	
img: link
	@echo 'Making floppy image'
	#@./initrd.sh ${OUTDIR}/pad_kernel
	#cat  ${GRUB} ${OUTDIR}/${TARGET} ${OUTDIR}/pad_kernel initrd.img > ${OUTDIR}/${IMG}
	cat  ${GRUB} ${OUTDIR}/${TARGET} > ${OUTDIR}/${IMG}
	@echo 'Kernel blocks'
	@du out/kernel -b --block-size=512 | cut -c 1-3
	#@echo 'Initrd blocks'
	#@du initrd.img -b --block-size=512 | cut -c 1-3
	@echo 'done.'
	@echo ' '
	
clean:
	@echo 'Cleaning...' 
	rm -f -r ${BINDIR} ${OUTDIR}
	mkdir ${BINDIR}
	mkdir ${BINDIR}/asm
	mkdir ${BINDIR}/hw
	mkdir ${BINDIR}/utils
	mkdir ${OUTDIR}
	@echo 'done.'
	@echo ' '