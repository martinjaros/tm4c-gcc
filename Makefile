PART    ?= TM4C123GH6PM
TARGET  ?= TM4C123_RB1
CFLAGS  ?= -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -ffunction-sections -fdata-sections -std=c99 -g -Os -Wall -Werror
LDFLAGS ?= --gc-sections

LIBGCC  := ${shell arm-none-eabi-gcc ${CFLAGS} -print-libgcc-file-name}
LIBC    := ${shell arm-none-eabi-gcc ${CFLAGS} -print-file-name=libc.a}
LIBM    := ${shell arm-none-eabi-gcc ${CFLAGS} -print-file-name=libm.a}

.PHONY: all clean

all: output.bin output.lst

clean:
	rm -f *.d *.o output.*

output.axf: $(patsubst %.c, %.o, $(wildcard *.c))
	arm-none-eabi-ld ${LDFLAGS} -T scatter.ld --entry ResetIntHandler -Map output.map -o $@ $^ ${LIBGCC} ${LIBC} ${LIBM}

-include $(wildcard *.d)

%.o: %.c
	arm-none-eabi-gcc ${CFLAGS} -Dgcc -DPART_${PART} -DTARGET_IS_${TARGET} -DUART_BUFFERED -MD -c -o $@ $<

%.bin: %.axf
	arm-none-eabi-objcopy -O binary $< $@

%.lst: %.axf
	arm-none-eabi-objdump -h -S $< > $@
