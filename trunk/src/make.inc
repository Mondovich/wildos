DIRS += asm boot common fs hw kernel std utils log

include $(SRCDIR)/asm/make.inc
include $(SRCDIR)/boot/make.inc
include $(SRCDIR)/common/make.inc
include $(SRCDIR)/fs/make.inc
include $(SRCDIR)/hw/make.inc
include $(SRCDIR)/kernel/make.inc
include $(SRCDIR)/log/make.inc
include $(SRCDIR)/std/make.inc
include $(SRCDIR)/utils/make.inc