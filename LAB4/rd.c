#include<stdio.h>
#include<ctype.h>
#include "lex.c" 
#include<string.h>


Tok lookahead;
int i=0;

void declarations();
void data_type();
void identifier_list();
void B();
void statement_list();
void statement();
void assign_stat();
void expn();
void simple_expn();
void eprime();
void seprime();
void term();
void factor();
void tprime();
void addop();
void mulop();
void relop();
Tok gtN()
{
	Tok x=getNextToken();
	//printf("gTN%s\n",x->ln);
	while(x->type==-1)
	{
		x=getNextToken();
		//printf("gTN1%d\n",x->type);
	}
	return x;
}
void program()
{
	printf("Program->%s\n",lookahead->ln);
	if(strcmp(lookahead->ln,"main")==0)
	{
		lookahead=gtN();
		if(strcmp(lookahead->ln,"(")==0)
		{
			lookahead=gtN();
			if(strcmp(lookahead->ln,")")==0)
			{
				lookahead=gtN();
				if(strcmp(lookahead->ln,"{")==0)
				{
					lookahead=gtN();
					declarations();
					statement_list();
					if(strcmp(lookahead->ln,"}")==0)
					{
						lookahead=gtN();
						return;
					}
				}
				else
				{
					printf("Error1: {},line:%d col:%d",rc,cc);
					printf("\n");
					exit(0);
				}
			}
			else
				{
					printf("Error2:missing ')',line:%d col:%d",rc,cc);
					printf("\n");
					exit(0);
				}
		}
		else
		{
			printf("Error3: missing '(', line:%d col:%d",rc,cc);
			printf("\n");
			exit(0);
		}
	}
	else
	{
		printf("Error4: missing main, line:%d col:%d",rc,cc);
		printf("\n");
		exit(0);
	}
}
void declarations()
{
	printf("Declaration->%s\n",lookahead->ln);
	if(strcmp(lookahead->ln,"int")==0 || strcmp(lookahead->ln,"char")==0)
			{
				data_type();
				identifier_list();
				//lookahead=gtN();
				if(strcmp(lookahead->ln,";")==0)
				{
					lookahead=gtN();
					declarations();
				}
			}

}
void data_type()
{
	printf("Data Type->%s\n",lookahead->ln);
	if(strcmp(lookahead->ln,"int")==0 || strcmp(lookahead->ln,"char")==0)
	{
		lookahead=gtN();
		return;
	}
	else
	{
		printf("Error5: expected 'int' or 'char',,line:%d col:%d",rc,cc);
					printf("\n");
		exit(0);
	}
}
void identifier_list()
{
	
	//lookahead=gtN();
	printf("Identifier List->%s\n",lookahead->ln);
	if(lookahead->type==7)
	{
		lookahead=gtN();
		B();
	}
	else
	{
		printf("Error6: missing identifier,line:%d col:%d",rc,cc);
					printf("\n");
		exit(0);
	}

}
void B()
{
	printf("Delimiter->%s\n",lookahead->ln);
	if(strcmp(lookahead->ln,",")==0)
	{
		lookahead=gtN();
		identifier_list();
	}
	else if(strcmp(lookahead->ln,"[")==0)
	{
		lookahead=gtN();
		if(lookahead->type==5)
		{
			lookahead=gtN();
			if(strcmp(lookahead->ln,"]")==0)
			{
				lookahead=gtN();
				if(strcmp(lookahead->ln,",")==0)
				{
					lookahead=gtN();
					identifier_list();
				}
			}
			else
			{
				printf("Error7: expected [],line:%d col:%d",rc,cc);
					printf("\n");
				exit(0);
			}
		}
		else
		{
			printf("Error8: expected ',',line:%d col:%d",rc,cc);
					printf("\n");
			exit(0);
		}
		

	}
	else
		return;
}
void statement_list()
{
	
	//lookahead=gtN();
	printf("Statement List->%s\n",lookahead->ln);
	if(lookahead->type==7)
	{
		statement();
		lookahead=gtN();
		statement_list();
	}
	
}
void statement()
{
	printf("Statement->%s\n",lookahead->ln);
	assign_stat();
	//lookahead=gtN();
	if(strcmp(lookahead->ln,";")==0)
	{
		return;
	}
	else
		{
			printf("Error9: missing ';',line:%d col:%d",rc,cc);
					printf("\n");
			exit(0);
		}
}
void assign_stat()
{
	printf("AssignStat->%s\n",lookahead->ln);
	if(lookahead->type==7)
	{
		lookahead=gtN();
		if(strcmp(lookahead->ln,"=")==0)
		{
			lookahead=gtN();
			expn();
		}
		else if(lookahead->type=9)
		{
			lookahead=gtN();
			expn();
		}
		else
		{
			printf("Error10: expected '=',line:%d col:%d",rc,cc);
					printf("\n");
			exit(0);
		}
	}
	else
	{
		printf("Error11");
		exit(0);
	}

}
void expn()
{
	printf("Expression->%s\n",lookahead->ln);
	simple_expn();
	//lookahead=gtN();
	eprime();

}

void simple_expn()
{
	printf("SimpleExp->%s\n",lookahead->ln);
	term();
	//lookahead=gtN();
	seprime();
}

void eprime()
{
	printf("EPrime->%s\n",lookahead->ln);
	if(lookahead->type==0)
	{
	relop();
	//lookahead=gtN();
	seprime();
	}
	else return;

}
void seprime()
{
	printf("SEPrime%s\n",lookahead->ln);
	if(strcmp(lookahead->ln,"+")==0 || strcmp(lookahead->ln,"-")==0)
	{
		addop();
		lookahead=gtN();
		term();
		//printf("EXTRA%s\n",lookahead->ln);
		//lookahead=gtN();
		seprime();
	}
	else
		return;
}
void term()
{
	printf("Term->%s\n",lookahead->ln);
	factor();
	lookahead=gtN();
	tprime();
}
void factor()
{
	printf("Factor->%s\n",lookahead->ln);
	if(lookahead->type==7||lookahead->type==5)
	{
		return;
	}
	else
	{
		printf("Error12");
		exit(0);
	}
}
void tprime()
{
	printf("TPrime->%s\n",lookahead->ln);
	if(strcmp(lookahead->ln,"*")==0 || strcmp(lookahead->ln,"/")==0||strcmp(lookahead->ln,"%")==0)
	{
		mulop();
		lookahead=gtN();
		factor();
		lookahead=gtN();
		tprime();
	}
	else
		return;
}


void addop()
{
	printf("Add->%s\n",lookahead->ln);
	if(strcmp(lookahead->ln,"+")==0 || strcmp(lookahead->ln,"-")==0)
		return;
	else
	{
		printf("Error13:expected '+',line:%d col:%d",rc,cc);
					printf("\n");
		exit(0);
	}
}
void mulop()
{
	printf("Mul->%s\n",lookahead->ln);
	if(strcmp(lookahead->ln,"*")==0 || strcmp(lookahead->ln,"/")==0||strcmp(lookahead->ln,"%")==0)
	{ return; }
	else
	{
		printf("Error14: expected '*',line:%d col:%d",rc,cc);
					printf("\n");
		exit(0);
	}

}
void relop()
{
	printf("R->%s\n",lookahead->ln);
	if(lookahead->type==0)
	{
		return;
	}
	else
	{
		printf("Error15");
		exit(0);
	}

}


int main()
{
	fp=fopen("input.c","r");
	// c=fgetc(fp);
	lookahead=gtN();

	program();

	if(strcmp(lookahead->ln,"$")==0)
		printf("\n\t*** S U C C E S S F U L L ***\n");
	else
		printf("E R R O R\n");

	return 0;
}
