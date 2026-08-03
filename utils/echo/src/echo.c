// SPDX-License-Identifier: AGPL-3.0-only OR GPL-2.0-or-later
/**
 * Echo utility
 *
 * This utility is defined by the POSIX standard and should adhere to its specification.
 * Note that this implementation includes also the XSI extension.
 *
 * See https://pubs.opengroup.org/onlinepubs/9799919799/utilities/echo.html.
 *
 * Copyright (c) 2026 Richard Tichý <richard@tichy.io>
 */
#include <stdbool.h>
#include <stdint.h>
#include "stdio.h"

static int parse_escaped_octal(const char **chunk_ptr) {
    int val = 0;
    int i = 0;
    for (i = 0; i < 3; i++) {
        const char c = (*chunk_ptr)[i];
        if ('0' > c || c > '7') {
            break;
        }

        val = val * 8;
        val += c - '0';
    }
    *chunk_ptr = *chunk_ptr + i;
    return val;
}

static int print_arg(const char *arg, bool *suppress_newline) {
    if (arg == NULL) {
        return 1;
    }
    const char *chunk_ptr = arg;
    uintptr_t chunk_len = 0;
    char current_char;
    bool escape_sequence = false;
    do {
        current_char = chunk_ptr[chunk_len];
        if (escape_sequence) {
            escape_sequence = false;
            fwrite(chunk_ptr, sizeof(char), chunk_len, stdout);
            chunk_ptr += chunk_len + 1;
            chunk_len = 0;
            switch (current_char) {
                case 'a':
                    printf("\a");
                    break;
                case 'b':
                    printf("\b");
                case 'c':
                    *suppress_newline = true;
                    return 0;
                case 'f':
                    printf("\f");
                    break;
                case 'n':
                    printf("\n");
                    break;
                case 'r':
                    printf("\r");
                    break;
                case 't':
                    printf("\t");
                    break;
                case 'v':
                    printf("\v");
                    break;
                case '\\':
                    printf("\\");
                    break;
                case '0':
                    const int val = parse_escaped_octal(&chunk_ptr);
                    if (val < 0 || 255 < val) {
                        return 1;
                    }
                    const char c = (char) val;
                    fwrite(&c, sizeof(char), 1, stdout);
                    break;
                case '\0':
                    return 1;
                default:
                    break;
            }
            continue;
        }
        if (current_char == '\\') {
            escape_sequence = true;
            fwrite(chunk_ptr, sizeof(char), chunk_len, stdout);
            chunk_ptr += chunk_len + 1;
            chunk_len = 0;
            continue;
        }
        chunk_len++;
    } while (current_char != '\0');
    if (0 < chunk_len) {
        fwrite(chunk_ptr, sizeof(char), chunk_len, stdout);
    }
    return 0;
}

int main(const int argc, char **argv) {
    bool suppress_newline = false;
    for (int i = 1; i < argc; i++) {
        const char *arg = argv[i];
        if (arg == NULL) {
            fprintf(stderr, "%s: argv contains null\n", argv[0]);
            return 1;
        }

        if (print_arg(arg, &suppress_newline)) {
            fprintf(stderr, "%s: failed to print arg %d\n", argv[0], i);
            return 1;
        }

        if (suppress_newline) {
            break;
        }
    }

    if (!suppress_newline) {
        printf("\n");
    }

    return 0;
}
