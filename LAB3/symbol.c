#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct entry
{
	int index ; // index of the entry
	char name[50];
	char type[4];
	int size ;
	char scope ;
	int noa ; // no of arguments
	char returntype[50];
	int argument; // index of the argument of the function in the table
};


int search(struct entry arr[50], int size, char* check){
	for(int i = 0; i < size; i++){
		if(strcmp(check, arr->name) == 0) return 1;
	}

	return 0;
}

void display(struct entry arr[50] , int size)
{
	printf("Index\tName\tType\t\tSize\tScope\tNumArgs\tArgInd\tReturn\n");
	for(int i = 0 ;i<=size;i++)
	{

		printf("%d\t%s\t%s\t\t%d\t%c\t%d\t%d\t%s\n",arr[i].index, arr[i].name, arr[i].type, arr[i].size, arr[i].scope, arr[i].noa, arr[i].argument, arr[i].returntype);
		
		printf("\n\n");

	}
}

int variableAlreadyExists(char *buf, struct entry arr[50], int tablesize)
{
	for(int i=0;i<tablesize;i++)
	{
		if(strcmp(buf,arr[i].name)==0)
			return 1;
	}
	return 0;
}

void printkey(char* buf){
	printf("<");
	printf("%s", buf);
	printf(">");
}

void printId(char* buf, struct entry arr[50], int tablesize){
	for(int i = 0; i < tablesize; i++){
		if(strcmp(buf, arr[i].name) == 0){
			printf("<id,%d>", arr[i].index);
		}
	}
}

void printOutput(struct entry arr[50], int tablesize){
	FILE *fa;
	char keyword[9][50]={"int","double","long","short","float","char","void", "if", "else"};
	int i = 0;
	char buf[50], keybuf[50];
	int icheck = 0;
	int ca, cb;
	fa = fopen("testcase.c", "r");
	ca = getc(fa);
	int prevWasKey = 0;
	int isId = 0;
	int isKey = 0;
	while(ca != EOF){
		if(ca == (int)'"'){
				ca = getc(fa);
				//printf("%c", ca);
				while(ca != (int)'"'){
					//printf("%c", ca);
					ca = getc(fa);
				}
		}

		if((ca>=(int)'a' && ca<=(int)'z') || (ca>=(int)'A' && ca<=(int)'Z'))// either a keyword or an identifier
			{
				memset(buf,'\0',sizeof(buf) * sizeof(char));
				int keywordOrIdentifier = 0 ;
				//int res = 0 ;
				

				buf[0]=ca ; int pos = 1;
				cb = getc(fa);
				//printf("%c ", ca);

				while((cb>=(int)'a' && cb<=(int)'z') || (cb>=(int)'A' && cb<=(int)'Z') || (cb>=(int)'0' && cb<=(int)'9'))
				{
					//check = 1 ;
					buf[pos++]=cb ;
					cb = getc(fa);
					//printf("%c ", cb);
				}

				buf[pos]='\0';
				//printf("Currently, word in buffer = %s\n", buf);

				for(i = 0; i<9 ; i++)
				{
					if(strcmp(buf,keyword[i])==0)
					{
						keywordOrIdentifier = 1 ;//keyword has been found
						isKey = 1;
						printkey(buf);
						prevWasKey = 1;
						//res = i ;
						break ;
					}
				}




				if(keywordOrIdentifier==0)// keyword not found . Identifier has been found
				{

					isId = 0;
					icheck = 1 ;
					
					if(prevWasKey == 1){
						printId(buf, arr, tablesize);
					}

				}
				else// keyword has been found
				{
					icheck = 0 ;
					//lastkeywordindex = i ;
					strcpy(keybuf,buf) ; // now keybuf contains
					// keyword has been found
				}
				
				
					ca = cb;
					continue ;
			

		}

		if(ca=='(' || ca == ')' || ca == '}' || ca == '{' || ca == ';' || ca == '*' ||ca == '=' || ca == '-')
		{
			printf("<%c>", ca);
		}

		else if(ca == '\n') printf("\n");

		ca = getc(fa);
	}

}	

int main()
{
	FILE * fa , *fb ;
	int tablesize = 0 ; // no of entries in the symbol table
	struct entry arr[50];
	char keyword[9][50]={"int","double","long","short","float","char","void", "if", "else"};
	int size[7]={4,8,8,2,4,1,0};
	int ca , cb ;
	int i ;
	fa = fopen("testcase.c","r");
	ca = getc(fa);
	char buf[50];
	char na[3]="NA";
	char keybuf[50]; // will contain the last keyword found
	int icheck = 0 ; // this is set to 1 if an identifier has been found
	//int currindex = 0 ; //used to keep track of symbol table index of function which has been found
	int lastkeywordindex = 0 ; // keep track of index of last keyword in the keyword array
	int lastfuncindex = 0 ; // keep track of index of last function
	int insidefuncparam = 0 ; // if set we are inside function parameter list
	int funcbodystart = 0 ; // if set we are inside the function body
	while(ca!=EOF)
	{
		if(icheck==1 && ca!=' ' && ca!='\n' &&  ca!='(' && insidefuncparam==0 && funcbodystart==0)
		{
			// global variable found 

			struct entry * item = malloc(sizeof(struct entry));
			item->index = tablesize ;
			tablesize ++ ;
			strcpy(item->name,buf);
			strcpy(item->type,keybuf);
			item->size = size[lastkeywordindex];
			item->scope = 'G';
			item->noa = 0 ;
			item->argument = -1 ;
			strcpy(item->returntype,na);
			arr[item->index] = (*item) ;
			icheck=0;
		}

		if(ca == (int)'"'){
			ca = getc(fa);
			//printf("%c", ca);
			while(ca != (int)'"'){
				//printf("%c", ca);
				ca = getc(fa);
			}
		}

		if((ca>=(int)'a' && ca<=(int)'z') || (ca>=(int)'A' && ca<=(int)'Z'))// either a keyword or an identifier
		{
			memset(buf,'\0',sizeof(buf) * sizeof(char));
			int keywordOrIdentifier = 0 ;
			//int res = 0 ;
			

			buf[0]=ca ; int pos = 1;
			cb = getc(fa);
			//printf("%c ", ca);

			while((cb>=(int)'a' && cb<=(int)'z') || (cb>=(int)'A' && cb<=(int)'Z') || (cb>=(int)'0' && cb<=(int)'9'))
			{
				//check = 1 ;
				buf[pos++]=cb ;
				cb = getc(fa);
				//printf("%c ", cb);
			}

			buf[pos]='\0';
			//printf("Currently, word in buffer = %s\n", buf);

			for(i = 0 ;i<9;i++)
			{
				if(strcmp(buf,keyword[i])==0)
				{
					keywordOrIdentifier = 1 ;//keyword has been found
					//printkey(buf);
					//res = i ;
					break ;
				}
			}




			if(keywordOrIdentifier==0)// keyword not found . Identifier has been found
			{

				
				icheck = 1 ;
				if(funcbodystart==0 && insidefuncparam==0)//outside function body and outside function params
				{
				}
				else if((insidefuncparam==0 && funcbodystart==1) || (insidefuncparam==1 && funcbodystart==0) )//a variable either in the body of a function or a parameter of the function
				{
					// local variable has been found

					if(variableAlreadyExists(buf, arr, tablesize))//dont insert this variable into symbol table if it already exists there
					{
						icheck = 0 ;
						ca = getc(fa);
						continue;
					}


					struct entry * item = malloc(sizeof(struct entry));
					item->index = tablesize ;
					tablesize ++;
					strcpy(item->name,buf);//name of the variable
					strcpy(item->type,keybuf);//name of the data type that was found just before this variable was found
					item->size = size[lastkeywordindex];
					item->scope = 'L';
					item->noa = 0 ;
					item->argument = -1 ;
					strcpy(item->returntype,na);





					arr[item->index] = (*item) ;// as arr[tablesize-1]


					if(insidefuncparam==1)// if it is a parameter of the function
					{
						arr[lastfuncindex].argument = item->index;
						arr[lastfuncindex].noa = 1 ;
					}
					icheck = 0;
				}
				

			}
			else// keyword has been found
			{
				icheck = 0 ;
				lastkeywordindex = i ;
				strcpy(keybuf,buf) ; // now keybuf contains
				// keyword has been found
			}
			
			
				ca = cb;
				continue ;
			

		}
		else if(ca==' ')
		{

		}
		else if(ca=='(' && icheck==1)
		{
			// a fn has been found . The value in buffer is the name of the function
			struct entry * item = malloc(sizeof(struct entry));
			item->index = tablesize ;
			tablesize ++ ;

			strcpy(item->name,buf);
			char type[]="FUNC";
			strcpy(item->type,type);
			item->scope = 'G' ;
			item->argument = -1 ;
			strcpy(item->returntype,keyword[lastkeywordindex]);
			insidefuncparam = 1 ;
			lastfuncindex = item->index ;

			arr[item->index] = (*item) ;
			icheck = 0 ;

		}
		else if(ca==')' && insidefuncparam==1)
		{
			insidefuncparam = 0 ;
		}
		else if(ca=='{')
		{
			funcbodystart = 1 ;
		}
		else if(ca=='}')
		{
			funcbodystart = 0 ;
		}




		ca = getc(fa);

		//printf("%c ", ca);
	}
	display(arr,tablesize-1);
	
	printOutput(arr, tablesize-1);
}
