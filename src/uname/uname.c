/*
 * uname.c
 * -------
 * A minimalist uname implementation.
 *
 * Copyright 2021 Thijs van der Woude
 * This program is licensed under the 3-clause BSD License. See the LICENSE file.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/utsname.h>

#include "../license.h"

#define PN "uname"
#define HELP "Usage: uname [option(s)]\nFunction: display system information.\nIf no option(s), -s is used.\n\n-h\thelp\n-a\tall possible options\n-m\thardware type\n-n\tnetwork node hostname\n-r\tkernel release\n-s\tkernel name\n-v\tOS version level\n"
#define OPTIONS "amnrsvh"

int main(int argc, char **argv) {
    struct utsname buffer;
    if (uname(&buffer) != 0) {
        fprintf(stderr, "%s: error: %s\n", PN, strerror(errno));
        exit(EXIT_FAILURE);
    }

    if (argc == 1) {
        argc = 2;
        argv[1] = "-s";
    }

    int opt;
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            case 'h':
                fprintf(stdout, HELP);
                fprintf(stdout, LICENSE);
				exit(EXIT_SUCCESS);
            case 'a':
                printf(
                    "%s %s %s %s %s\n",
                    buffer.sysname,
                    buffer.nodename,
                    buffer.release,
                    buffer.version,
                    buffer.machine
                );
                exit(EXIT_SUCCESS);
            case 'm':
                printf("%s ", buffer.machine);
                break;
            case 'n':
                printf("%s ", buffer.nodename);
                break;
            case 'r':
                printf("%s ", buffer.release);
                break;
            case 's':
                printf("%s ", buffer.sysname);
                break;
            case 'v':
                printf("%s ", buffer.version);
                break;
        }
    }
    printf("\n");
    exit(EXIT_SUCCESS);
}
