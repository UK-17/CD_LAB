#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
FILE *fp;
char c, buf[10];
int rc=0,cc=0;
char keys[][20]= {"int", "char", "if", "else", "while", "void", "for", "return"};
int keycount=8;
struct token
{
	char ln[100];
	int row,col;
	int type;
};
typedef struct token* Tok;

//FILE *output=fopen("Out.txt","w");


Tok getNextToken()
{
	int i=0;
	Tok x=(Tok)malloc(sizeof(struct token));
	c=fgetc(fp);
	x->type=-1;
	if(c=='\n')
	{
		rc++;
		cc=0;
	}
	else if(c==' ')
	{
		while(c==' ')
			c=fgetc(fp);
		fseek(fp,-1,SEEK_CUR);
	}
	else if(c=='/')
	{
		c=getc(fp);
			if(c=='/')
			{
				while(c!='\n')
					c=getc(fp);
				if(c=='\n')
				{
					rc++;
					cc=0;
				}
				fseek(fp,-1,SEEK_CUR);

			}
			else if(c=='*')
			{
				
				do
				{
					while(c!='*')
					{
						
						c=getc(fp);
						if(c=='\n')
				{
					rc++;
					cc=0;
				}

					}
					c=getc(fp);
				}while(c!='/');
			}
	}
	else if(c=='#')
		{
			c=getc(fp);cc++;
			while(c!='\n')
				{c=getc(fp);
					cc++;}
					rc++;
					cc=0;
			//c=getc(fp);
			//cc++;
		}
	else if(c=='=')
		{
			x->ln[i++]=c;
			c=fgetc(fp);
			cc++;
			if(c=='=')
			{
				x->ln[i++]=c;
				x->ln[i]='\0';
				// printf("\nRelational op: %s",buf);
				x->type=0;
			}
			else
			{
				x->ln[i]='\0';
				//printf("\nAssignment op: %s",buf);
				x->type=1;
				fseek(fp,-1,SEEK_CUR);
				cc--;
			}
		}
		else if(c=='<'||c=='>')
		{
			  	x->ln[i++]=c;
				c=fgetc(fp);
				cc++;
				if(c=='=')
				{
					x->ln[i++]=c;
					x->ln[i]='\0';
				x->type=0;
				}
				else{
				x->ln[i]='\0';
				x->type=0;
				fseek(fp,-1,SEEK_CUR);
				cc--;
			}
		}
		else if(c=='+'||c=='-'||c=='/'||c=='*'||c=='%')
		{
			x->ln[i++]=c;
			c=fgetc(fp);
			cc++;
			if(c=='=')
			{
				x->ln[i++]=c;
				x->ln[i]='\0';
				x->type=9;
			}
			else if(c=='+'||c=='-')
			{
				x->ln[i++]=c;
				x->ln[i]='\0';
				x->type=10;
			}
			else
			{x->ln[i]='\0';
			x->type=2;
			fseek(fp,-1,SEEK_CUR);
				cc--;}

		}
		else if(c=='('||c==')'||c=='{'||c=='}'||c=='['||c==']'||c==';'||c=='?'||c==':'||c==','||c=='$')
		{
			x->ln[i++]=c;
			x->ln[i]='\0';
			x->type=3;
		}
		else if(c=='&'||c=='|'||c=='!')
		{
			x->ln[i++]=c;
			c=fgetc(fp);
			cc++;
			if(c=='=')
			{
				x->ln[i++]=c;
				x->ln[i]='\0';
				x->type=0;
			}
			else if(c=='&'||c=='|')
			{
				x->ln[i++]=c;
				x->ln[i]='\0';
				x->type=4;
			}
			else
			{
				x->ln[i]='\0';
				x->type=4;
				fseek(fp,-1,SEEK_CUR);
				cc--;
			
			}
		}
		else if(isdigit(c))
		{
			x->ln[i++]=c;
			c=fgetc(fp);
			cc++;
			while(isdigit(c))
			{
				x->ln[i++]=c;
				c=fgetc(fp);
				cc++;
			}
			x->ln[i]='\0';
				x->type=5;
				fseek(fp,-1,SEEK_CUR);
				cc--;

		}
		else if(isalpha(c))
		{
			x->ln[i++]=c;
			c=fgetc(fp);
			cc++;
			while(isalpha(c))
			{
				x->ln[i++]=c;
				c=fgetc(fp);
				cc++;
			}
			int flag=0;
			for(int j=0;j<keycount;j++)
			{
				if(strcmp(x->ln,keys[j])==0)
				{
					x->ln[i]='\0';
				x->type=6;
				flag=1;
				}
			}
			if(flag==0)
			{
				x->ln[i]='\0';
				x->type=7;
			}
			fseek(fp,-1,SEEK_CUR);
			cc--;
		}
		else if(c=='\"')
		{
			x->ln[i++]=c;
			c=fgetc(fp);
			cc++;
			while(c!='\"')
			{
				x->ln[i++]=c;
				c=fgetc(fp);
				cc++;
			}
			x->ln[i++]=c;
			x->ln[i]='\0';
				x->type=8;

		}
		x->row=rc;
		x->col=cc-i;

		return x;


}
