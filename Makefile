TOOLCHAIN := /opt/xpack/riscv-none-elf-gcc/bin/riscv-none-elf
GCC       := $(TOOLCHAIN)-gcc
GDB       := $(TOOLCHAIN)-gdb
OBJCOPY   := $(TOOLCHAIN)-objcopy
OBJDUMP   := $(TOOLCHAIN)-objdump
SIZE      := $(TOOLCHAIN)-size
NM        := $(TOOLCHAIN)-nm
DEMANGLE  := $(TOOLCHAIN)-c++filt
ULTOOL    := esputil
Q         ?= @

OBJDIR    := obj
BINDIR    := bin
DEPDIR    := dep

SRCEND    ?= c
EXECFILE  ?= t5os
SRCFILES  := $(shell find . -name "*.$(SRCEND)")
OBJECTS   := $(notdir $(SRCFILES:.$(SRCEND)=.o))
DEPENDS   := $(patsubst %.o,$(DEPDIR)/%.d,$(OBJECTS))

OPTFLAG   ?= -Os
BASEFLAGS := -W -Wall -Wextra -Werror -Wundef -Wshadow
BASEFLAGS += -Wdouble-promotion -fno-common -Wconversion
BASEFLAGS += -march=rv32imc_zicsr -mabi=ilp32
BASEFLAGS += -ffunction-sections -fdata-sections -I.
GCCFLAGS  := $(BASEFLAGS) $(OPTFLAG)
LDFLAGS   := $(BASEFLAGS) -Tlink.ld -nostdlib -nostartfiles -Wl,--gc-sections $(EXTRA_LINKFLAGS)
NMFLAGS   := --numeric-sort --print-size
OBJPRE = $(addprefix $(OBJDIR)/, $(OBJECTS))

VPATH = $(sort $(dir $(SRCFILES)))

.PHONY: all clean text info dump flash monitor

all: $(BINDIR)/$(EXECFILE).bin

$(DEPDIR)/%.d: %.$(SRCEND)
	@mkdir -p $(@D)
	@echo "DEP	$<"
	$(Q) $(GCC) $(GCCFLAGS) -MM -MT $(OBJDIR)/$*.o -MF $@ $<

$(OBJDIR)/%.o: %.$(SRCEND)
	@mkdir -p $(@D)
	@echo "CC	$<"
	$(Q) $(GCC) $(GCCFLAGS) $(INCLUDE) -c $< -o $@

$(BINDIR)/$(EXECFILE).elf: $(OBJPRE)
	@mkdir -p $(@D)
	@echo "LD	$@"
	$(Q) $(GCC) -o $@ $^ $(LDFLAGS)

text: bin

bin: $(BINDIR)/$(EXECFILE).bin

$(BINDIR)/%.bin: $(BINDIR)/%.elf
	@echo "COPY	$@"
	$(Q) $(ULTOOL) mkbin $< $@

dump: $(BINDIR)/$(EXECFILE).lst

$(BINDIR)/%.lst: $(BINDIR)/$(EXECFILE).elf
	@echo "DUMP	$@"
	$(Q) $(OBJDUMP) -h -S $< > $@

info: $(BINDIR)/$(EXECFILE).elf
	@echo "INF	$<"
	$(Q) $(SIZE) -A -t $(BINDIR)/$(EXECFILE).elf > $(BINDIR)/$(EXECFILE)_size.txt
	$(Q) $(NM) $(NMFLAGS) $(BINDIR)/$(EXECFILE).elf > $(BINDIR)/$(EXECFILE)_nm.txt
	$(Q) $(NM) $(NMFLAGS) $(BINDIR)/$(EXECFILE).elf | $(DEMANGLE) > $(BINDIR)/$(EXECFILE)_cppfilt.txt

clean:
	@echo "CLEAN"
	$(Q) $(RM) -r $(BINDIR)
	$(Q) $(RM) -r $(DEPDIR)
	$(Q) $(RM) -r $(OBJDIR)

flash: $(BINDIR)/$(EXECFILE).bin
	@echo "FLAS	$<"
	$(Q) $(ULTOOL) flash 0 $<

monitor:
	@echo "MONITOR"
	$(Q) $(ULTOOL) monitor

ifneq ($(MAKECMDGOALS),clean)
-include $(DEPENDS)
endif

