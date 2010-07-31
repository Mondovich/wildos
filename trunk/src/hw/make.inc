DIRS += hw/cpu hw/io hw/memory hw/video

include $(SRCDIR)/hw/cpu/make.inc
include $(SRCDIR)/hw/io/make.inc
include $(SRCDIR)/hw/memory/make.inc
include $(SRCDIR)/hw/video/make.inc

OBJS += \
./${BINDIR}/hw/kheap.o \
./${BINDIR}/hw/io.o \
./${BINDIR}/hw/isr.o \
./${BINDIR}/hw/paging.o \
./${BINDIR}/hw/screen.o \
./${BINDIR}/hw/syscall.o \
./${BINDIR}/hw/task.o \
./${BINDIR}/hw/timer.o 