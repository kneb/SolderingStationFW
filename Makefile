# Name: Makefile
# Author: Neb Konstantin Viktorovich

BUILDDIR = Build
OUTNAME = ssfw

DEVICE = atmega8
CLOCK = 16000000
COMPILER = avr-g++
ARGS = -Wall -Os -DF_CPU=$(CLOCK) -mmcu=$(DEVICE)

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


#	$(COMPILE) -c $< -o $@

#.S.o:
#	$(COMPILE) -x assembler-with-cpp -c $< -o $@
# "-x assembler-with-cpp" should not be necessary since this is the default
# file type for the .S (with capital S) extension. However, upper case
# characters are not always preserved on Windows. To ensure WinAVR
# compatibility define the file type manually.

#.cpp.s:
#	$(COMPILE) -S $< -o $@

#flash:	all
#	$(AVRDUDE) -U flash:w:main.hex:i

#fuse:
#	$(AVRDUDE) $(FUSES)

# Xcode uses the Makefile targets "", "clean" and "install"
#install: flash fuse

# if you use a bootloader, change the command below appropriately:
#load: all
#	bootloadHID main.hex



# file targets:
#m#ain.elf: $(OBJECTS)
#	$(COMPILE) -o main.elf $(OBJECTS)

#main.hex: main.elf
#	rm -f main.hex
#	avr-objcopy -j .text -j .data -O ihex main.elf main.hex
#	avr-size --format=avr --mcu=$(DEVICE) main.elf
# If you have an EEPROM section, you must also create a hex file for the
# EEPROM and add it to the "flash" target.

# Targets for code debugging and analysis:
#disasm:	main.elf
#	avr-objdump -d main.elf

#cpp:
#	$(COMPILE) -E main.c
