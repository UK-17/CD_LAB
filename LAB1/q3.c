#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int lc=0;

const char *keywords[21] = 
{
	"int","struct","break","else",
	"long","switch","case","enum","register",
	"typedef","char","return","for",
	"do","if","while","default",
	"sizeof","const","float","short",
};


const char delimiters[] = " .,;:!-()\n\t";

int isKeyword (char *word) {
	int i;
	for (i = 0; i < 21; ++i) {
		if (strcmp(word, keywords[i]) == 0) {
			return 1;
		}
	}
	return 0;
}

void printUpperCase (char *word) {
	int l = strlen(word);
	char z;
	int i;
	for (i = 0; i < l; ++i) {
		z = word[i];
		printf("%c", z > 96 ? z - 32 : z);
	}
	printf("\n");
}

int main (int argc, const char * argv []) {

	char infile[128];
	printf("Enter input filename: ");
	scanf(" %s", infile);

	FILE *input = fopen(infile, "r");

	char buffer[1024];
	int k;

	while (fgets(buffer, 1024, input) > 0) 
	{
        char *cp = (char *)malloc(1024 * sizeof(char));
		strcpy(cp, buffer);
		if(*cp == '\n')
			lc++;
		char *token = (char *)malloc(256 * sizeof(char));
      do {
			token = strsep(&cp, delimiters);
			if (token != NULL) {
				if (isKeyword(token)) {
					printUpperCase(token);
				}
			}

		} while (token != NULL);
	}
	printf("LC = %d",lc);

	fclose(input);

	return 0;

}
