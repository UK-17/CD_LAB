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
	ch = getc(input);
	 
	 while(ch != EOF)
	 {
	 	if(ch == ' ' || ch == '\t')
	 	{
	 		while(ch == ' ' || ch == '\t')
	 			ch =getc(input);
	 		putc(' ',output);
	 	}
	 	putc(ch,output);
	 	ch = getc(input);
	 }

	
	fclose(input);
	fclose(output);

	return 0;

}
