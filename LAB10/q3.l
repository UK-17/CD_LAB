%{
	int pos_int = 0;
	int neg_int = 0;
	int pos_flt = 0;
	int neg_flt = 0;
%}

DIGIT	[0-9]
POS_INT	[+]?{DIGIT}+
NEG_INT	[-]{DIGIT}+
POS_FLOAT	[+]?{DIGIT}+(\.{DIGIT}+)
NEG_FLOAT	[-]{DIGIT}+(\.{DIGIT}+)

%%
{POS_INT} {pos_int++;}
{NEG_INT} {neg_int++;}
{POS_FLOAT} {pos_flt++;}
{NEG_FLOAT} {neg_flt++;}
%%
int yywrap()
{
	return 1;
}
int main()
{   printf("enter the input:\n");
	yylex();
	printf("PI:%d\nNI:%d\nPF:%d\nNF:%d\n",pos_int,neg_int,pos_flt,neg_flt);
}
