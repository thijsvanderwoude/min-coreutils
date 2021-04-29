/*
 * A minimalist cat implementation.
 * Copyright (c) 2021 Thijs van der Woude
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#define PN "cat"
#define HELP "Usage: cat [option(s)] [file(s)]\nFunction: concatenates file(s) to standard output.\n\nIf no FILE(S) OR if FILE is - read standard input.\n\n-h\thelp\n-u\twrite byte by byte (ignored, standard operation)\n"
#define OPTION_H "-h"
#define OPTION_U "-u"

int main(int argc, char **argv) {
	const char *optionList[] = {OPTION_H, OPTION_U};
	int optionListLength = sizeof(optionList) / sizeof(optionList[0]);

	char *fileList[65535];	// fileList is terminated by NULLs automatically
	int fileCounter = 0;
	FILE *file;

	switch (argc) {
		case 1:
			fileList[0] = "-";
			break;
		default:
			// Loop through argv to separate anything in option list from files
			for (int i = 1; i < argc; i++) {
				if (argv[i][0] == '-' && strlen(argv[i]) > 1) {
					// It is an option
					switch (argv[i][1]) {
						case 'h':
							fprintf(stdout, HELP);
							exit(EXIT_SUCCESS);
						case 'u':
							break;
						default:
							fprintf(stderr, "%s: unknown option %s\nsee: %s -h\n", PN, argv[i], PN);
							exit(EXIT_FAILURE);
					}
				} else if (file = fopen(argv[i], "r")) {
					// It is a file and we can open it
					fileList[fileCounter] = argv[i];
					fileCounter++;
					fclose(file);
				} else if (argv[i][0] == '-' && strlen(argv[i]) == 1) {
					// It is -
					fileList[fileCounter] = argv[i];
					fileCounter++;
				} else {
					// We could not open the input file
					fprintf(stderr, "%s: %s: %s\n", PN, argv[i], strerror(errno));
					exit(EXIT_FAILURE);
				}
			}
			break;
	}
	
	int standardOut = fileno(stdout);
	char buffer[65535];
	int wr;
	
	for (int i = 0; fileList[i] != NULL; i++) {
		if (fileList[i][0] == '-') {
			file = stdin;
		} else {
			file = fopen(fileList[i], "r");
		}

		while(1) {
			buffer[0] = fgetc(file);
			if (feof(file)) {
				break;
			}
			wr = write(standardOut, buffer, 1);
		}
		fclose(file);
	}

	exit(EXIT_SUCCESS);
}
