/*
 * pwd.c
 * -------
 * A minimalist pwd implementation.
 *
 * Copyright 2021 Thijs van der Woude
 * This program is licensed under the 3-clause BSD License. See the LICENSE file.
 */

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define HELP "Usage: pwd [option]\nFunction: prints the current working directory\n\n-h\thelp\n-L\tlogical path, standard operation\n-P\tPWD environment variable\n"
#define OPTIONS "hLP"

int main(int argc, char **argv) {
    if (argc == 1) {
		argc = 2;
		argv[1] = "-L";
	}

    int opt;
    char buffer[65535];
    while ((opt = getopt(argc, argv, OPTIONS)) != -1) {
        switch (opt) {
            case 'P':
                getcwd(buffer, sizeof(buffer));
                fprintf(stdout, "%s\n", buffer);
                exit(EXIT_SUCCESS);
            case 'L':
                fprintf(stdout, "%s\n", getenv("PWD"));
                exit(EXIT_SUCCESS);
            case 'h':
                fprintf(stdout, HELP);
                exit(EXIT_SUCCESS);
        }
    }
}
