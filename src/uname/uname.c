/*
 *  A minimalist uname implementation.
 *  Copyright (C) 2021  Thijs van der Woude
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 *
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/utsname.h>

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
