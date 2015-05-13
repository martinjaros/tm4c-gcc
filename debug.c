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

void debug_printf(uint32_t level, const char *file, uint32_t line, const char *msg, ...)
{
    uint32_t msec = (systick_counter * ROM_SysTickPeriodGet() + ROM_SysTickValueGet()) * 1000 / ROM_SysCtlClockGet();
    UARTprintf("%.2u:%.2u:%.2u.%.3u (%s:%u) %s - ", msec / 3600000 % 24, msec / 60000 % 60, msec / 1000 % 60, msec % 1000,
        file, line, level == 1 ? "ERROR" : level == 2 ? "WARN" : level == 3 ? "INFO" : "TRACE");

    va_list args;
    va_start(args, msg);
    UARTvprintf(msg, args);
    UARTwrite("\n", 1);
    va_end(args);
}

