# Name: Makefile
# Author: Neb Konstantin Viktorovich

BUILDDIR = Build
OUTNAME = ssfw

DEVICE = atmega8
CLOCK = 16000000
COMPILER = avr-g++
#ARGS = -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)
ARGS = -Wall -Os -mmcu=$(DEVICE)

SRCC := $(wildcard *.cpp)
OBJECTS := $(patsubst %.cpp,%.o,$(SRCC))
SRCOBJ := $(addprefix $(BUILDDIR)/, $(OBJECTS))

.PHONY: all clean

.cpp.o:
	@$(COMPILER) $(ARGS) -c $< -o $(BUILDDIR)/$@
	@echo "Compile $< --> $(BUILDDIR)/$@"

all: $(OBJECTS)
	@$(COMPILER) $(ARGS) $(SRCOBJ) -o $(BUILDDIR)/$(OUTNAME).elf
	@rm -f $(BUILDDIR)/$(OUTNAME).hex
	@avr-objcopy -j .text -j .data -O ihex $(BUILDDIR)/$(OUTNAME).elf $(BUILDDIR)/$(OUTNAME).hex
	@avr-size --format=avr --mcu=$(DEVICE) $(BUILDDIR)/$(OUTNAME).elf
	@echo "Build is Ok $(BUILDDIR)/$(OUTNAME).hex"

clean:
	@rm -f $(BUILDDIR)/*
	@echo "All Clean"

#flash:	all
#	$(AVRDUDE) -U flash:w:main.hex:i

#fuse:
#	$(AVRDUDE) $(FUSES)
