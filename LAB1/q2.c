#include <stdio.h>
#include <stdlib.h>

int main () {

	char infile[128];
	printf("Enter input filename: ");
	scanf(" %s", infile);

	FILE *input = fopen(infile, "r");

	char outfile[128];
	snprintf(outfile, 128, "mod_%s", infile);

	FILE *output = fopen(outfile, "w+");

	char ch;
	do {
		ch = getc(input); 
		if (ch == '#') { 
			while (ch != '\n') { 
				ch = getc(input);
			}
			 ch = getc(input);
		}
		putc(ch, output);
	} while (ch != EOF);

	fclose(input);
	fclose(output);

	return 0;

}

