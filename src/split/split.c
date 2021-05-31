/*
 * split.c
 * -------
 * A minimalist split implementation.
 *
 * Copyright 2021 Thijs van der Woude
 * This program is licensed under the 3-clause BSD License. See the LICENSE file.
 */

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "../license.h"

#define PN "split"
#define HELP "Usage: split [option(s)] [file]\nFunction: splits a file into multiple files.\nIf no FILE or FILE is - standard input is read.\n\n-h\t\t\thelp\n-a suffix_length\tsomething\n-b n\t\t\tasd\n-b nk\t\t\tasd\n-b nm\t\t\tas\n-l line_count\t\tasd\n"

#define OPTIONS "a:b:hl:"

int main(int argc, char **argv) {
    unsigned int lineCount = 1000;
	int suffixLength = 2;
	int size = 0;
	int mode = 'l';		// Standard operating mode is l, aka, split per lineCount lines
	int opt;

	while ((opt = getopt(argc, argv, OPTIONS)) != EOF) {
		switch (opt) {
			case 'h':
				fprintf(stdout, HELP);
				fprintf(stdout, LICENSE);
				exit(EXIT_SUCCESS);
			case 'a':
				suffixLength = atoi(optarg);
				break;
            case 'b':
				mode = 'b';
				
                break;
            case 'l':
				lineCount = atoi(optarg);
                break;
		}
	}

	FILE *input;

	// In case no file is specified, assume -
	// OR if the file specified is -
	if (optind != argc - 1 || strcmp(argv[optind], "-") == 0) {
		input = stdin;
	} else {
		input = fopen(argv[optind], "r");
	}

	// In case we can't open the input file
	if (input == NULL) {
		fprintf(stderr, "%s: %s: %s\n", PN, argv[optind], strerror(errno));
		exit(EXIT_FAILURE);
	}

	int ch;
	while (1) {
		if (feof(file)) {
			break;
		} else {
			// Generate suffix
			
		}
	}
	

	fclose(input);
	exit(EXIT_SUCCESS);
}
