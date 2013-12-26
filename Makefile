CFLAGS = -mthumb -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mfloat-abi=softfp -std=c99 \
         -ffunction-sections -fdata-sections -Os -Wall -pedantic \
         -Dgcc -DPART_TM4C123GH6PM -DTARGET_IS_BLIZZARD_RB1

LIBC := ${shell arm-none-eabi-gcc ${CFLAGS} -print-file-name=libc.a}
LIBM := ${shell arm-none-eabi-gcc ${CFLAGS} -print-file-name=libm.a}

.PHONY: all flash clean

all: bin bin/output.bin

flash: all
	@sudo lm4flash bin/output.bin

clean:
	@rm -r -f bin

bin:
	@mkdir -p bin

bin/output.bin: bin/output.axf
	@arm-none-eabi-objcopy -O binary $< $@

bin/output.axf: $(patsubst src/%.c, bin/%.o, $(wildcard src/*.c))
	@echo LD $@
	@arm-none-eabi-ld -T tm4c123.ld --entry ResetISR --gc-sections -o $@ $^ ${LIBM} ${LIBC}

bin/%.o: src/%.c
	@echo CC $<
	@arm-none-eabi-gcc ${CFLAGS} -c -MD -o $@ $<

-include $(wildcard bin/*.d)
