/*
 * Copyright (c) 2015, Martin Jaros <xjaros32@stud.feec.vutbr.cz>
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <stdbool.h>
#include <stdint.h>
#include "driverlib/rom.h"
#include "utils/uartstdio.h"
#include "debug.h"

static uint32_t systick_counter = 0, systick_period;
void SysTickIntHandler() { systick_counter++; }

void debug_init(uint32_t port, uint32_t baudrate, uint32_t clock)
{
    ROM_SysTickPeriodSet(clock);
    ROM_SysTickEnable();
    ROM_SysTickIntEnable();
    systick_period = clock;

    UARTStdioConfig(port, baudrate, clock);
}

void debug_printf(uint32_t level, const char *file, uint32_t line, const char *msg, ...)
{
    uint32_t time_sec = systick_counter;
    uint32_t time_usec = (systick_period - ROM_SysTickValueGet()) / (systick_period / 1000000);
    UARTprintf("%02u:%02u:%02u.%06u (%s:%u) %s - ", time_sec / 3600 % 24, time_sec / 60 % 60, time_sec % 60, time_usec % 1000000,
        file, line, level == 1 ? "ERROR" : level == 2 ? "WARN" : level == 3 ? "INFO" : "TRACE");

    va_list args;
    va_start(args, msg);
    UARTvprintf(msg, args);
    UARTwrite("\n", 1);
    va_end(args);
}

