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

#ifndef DEBUG_H
#define DEBUG_H

#include <stddef.h>
#include <stdint.h>

#if DEBUG_LEVEL > 0
#define ERROR(msg, ...) debug_printf(1, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#else
#define ERROR(msg, ...)
#endif

#if DEBUG_LEVEL > 1
#define WARN(msg, ...)  debug_printf(2, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#else
#define WARN(msg, ...)
#endif

#if DEBUG_LEVEL > 2
#define INFO(msg, ...)  debug_printf(3, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#else
#define INFO(msg, ...)
#endif

#if DEBUG_LEVEL > 3
#define TRACE(msg, ...) debug_printf(4, __FILE__, __LINE__, msg, ##__VA_ARGS__)
#else
#define TRACE(msg, ...)
#endif

void debug_init(uint32_t port, uint32_t baudrate, uint32_t clock);
void debug_printf(uint32_t level, const char *file, uint32_t line, const char *msg, ...);
char* debug_hexify(char *dst, const void *src, size_t n);

#endif /* DEBUG_H */
