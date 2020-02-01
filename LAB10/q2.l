%{
	int characters = 0;
	int words = 0;
	int lines = 0;
%}

%%
[a-zA-Z]+	{ words++; characters +=strlen(yytext);}
\n	{ characters++; lines++; }
.	{ characters++; }
%%
int yywrap()
{
	return 1;
}
int main(int argc, char** argv)
{   printf("Enter The input:\n");
	yylex();
	printf("Lines:%d\nWords:%d\nCharacters:%d\n",lines,words,characters);
}
