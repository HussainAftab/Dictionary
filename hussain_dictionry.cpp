#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<windows.h>

#define SIZE 100000
#define MIN3(a, b, c) ((a) < (b) ? ((a) < (c) ? (a) : (c)) : ((b) < (c) ? (b) : (c)))


char wordlist[SIZE][100];
char meaning[SIZE][1000];
char synonym[200000][100];

void strcase(char *str);
void load_data(void);
int search_word(char *);
void search_mean(char *);
void search_synonym(char *);
void getword(char *, char *);
void edit_log(char *word);
int levenshtein(char *s1, char *s2);
void get_related_words(char *, char*);

char log[10][25];

int main()
{
	
	int a;
	char line[25]; 
	char input[25];
	char *sptr;
	int comp;
	int ln;
	int j = 0, i=0;
	char g;
	char word[25];
	char related_words[200];
	FILE *lptr;
	
	
	
	printf("Loading Data Please Wait...\n");
	load_data();
	printf("Data Loaded Successfully press any key to continue..\n");
	
	while(1)
	{
	
	printf("Enter Word:");
	gets(word);
	edit_log(word);
	
//	lptr=fopen("C:\\Users\\Suffah\\Desktop\\FAST-NU\\1st semester\\ITC\\CodeSplash\\log.txt","a");
//	fputs("$",lptr);
//	fputs(word,lptr);
//	fputs("\n",lptr);
//	fclose(lptr);

	if(search_word(word))
	{
		printf("\nword found\n");
		search_mean(word);
		search_synonym(word);
	}
	else
	{
		printf("\nword not found\n");
		get_related_words(related_words,word);
		printf("\ndid you mean: ");
		printf("%s\n",related_words);
		
	}
		printf("\n\nfor futhur search press enter");
		printf("\nfor history enter 1");
		g=getch();
		if(g=='1')
		{
			for(i=0;i<10;i++)
			{
				printf("\n%s", log[i]);
			}
		}
	
		else
		system("cls");
	}

	getch();
	return(0);
}

void load_data(void)
{
	
	int ln;
	int i=0,j=0;
	char temp[25], mline[1000];
	char *sptr;
	
	
	FILE *fnptr, *fmptr, *fsptr ;
	fnptr=fopen("wordlist.txt","r");
	fmptr=fopen("meanings.txt","r");    
	fsptr=fopen("synonyms.txt","r");
	
	
	while(!feof(fnptr))
	{
		
		fgets(wordlist[i], 100, fnptr);
		
		// Remove \n
		ln = strlen(wordlist[i]) - 1;
		if (wordlist[i][ln] == '\n')
		    wordlist[i][ln] = '\0';
		i++;
	}
	fclose(fnptr);
	
	i=0;
	while(!feof(fmptr))
	{
		   
		fgets(meaning[i], 1000, fmptr);
		
		// Remove \n
		ln = strlen(meaning[i]) - 1;
		if (meaning[i][ln] == '\n')
		    meaning[i][ln] = '\0';
		i++;
	}
	fclose(fmptr);
	
	i = 0;
	while(!feof(fsptr))
	{
		fgets(synonym[i], 100, fsptr);
		
		// Remove \n
		ln = strlen(synonym[i]) - 1;
		if (synonym[i][ln] == '\n')
		    synonym[i][ln] = '\0'; 
		   
		 
		i++;
	}
	fclose(fsptr);
}

int search_word(char *word)
{
	int i = 0;
	int comp;
	char *ptr;
	char temp[100];
	
	for(i=0;i<SIZE;i++)
	{
		strcpy(temp,wordlist[i]);
		strcase(temp);
		strcase(word);
		
		ptr = strstr(temp,word);
		if(ptr)
		{
			comp = strcmpi(temp,word);
			if(comp == 0)
			{
				return(1);
			}
		}
	}
	return(0);
	
}

void search_mean(char *word)
{
	int i=0;
	char temp[100];
	char *ptr; 
	char temp2[1000];
	int comp;

	strcpy(temp,word);
	strcase(temp);
			
	
	for(i=0;i<SIZE;i++)
	{
	
		getword(temp2,meaning[i]);
		//strcpy(temp2,meaning[i]);
		strcase(temp2);
		
		ptr=strstr(temp2,temp);
		if(ptr)
		{
			comp = strcmpi(temp2,temp);
			if(comp == 0)
			{
				printf("Meaning:");
				printf("\n%s", meaning[i]);
				break;
			}
		}

	}
}

void search_synonym(char *word)
{
	int i=0;
	char temp[100];
	char *ptr; 
	char temp2[100];
	int comp;

	strcpy(temp, word);
	strcase(temp);

	
	for(i=0;i<200000;i++)
	{
	
		getword(temp2,synonym[i]);
		//strcpy(temp2,synonym[i]);
		strcase(temp2);
		
		
		ptr=strstr(temp2,temp);
		if(ptr)
		{
			comp = strcmpi(temp2,temp);
			if(comp == 0)
			{
				printf("\n\nSynonym:");
				printf("\n%s", synonym[i+1]);
				break;
			}
		}
		
		
	}
}


void getword(char *word, char *line)
{
	int i = 0;
	int space_cnt = 0;
	
	for(i=0;i<100;i++)
	{
		if(*line != ' ')
		{
			*word = *line;
			word++;
			space_cnt = 0;
		}
		else
		{
			space_cnt++;
			if(space_cnt >= 2)
			{
				*word = '\0';
				break;
			}
		}
		line++;
		
	}
}

void strcase(char *str)
{
	int i = 0;
	int size;
	size = strlen(str);
	for(i=0;i<size;i++)
	{
		
		if(*str >= 65 && *str <= 90)
		{
			*str = *str + 32;
		}
		str++;
	}
}

void edit_log(char *word)
{
	int c;
	
	for(c=9;c>=0;c--)
	{
		strcpy(log[c+1],log[c]);
	}
	
	//log[0][0] = '-';
	strcpy(log[0],word);
	
}

int levenshtein(char *s1, char *s2) 
{
    unsigned int s1len, s2len, x, y, lastdiag, olddiag;
    s1len = strlen(s1);
    s2len = strlen(s2);
    unsigned int column[s1len+1];
    for (y = 1; y <= s1len; y++)
        column[y] = y;
    for (x = 1; x <= s2len; x++) {
        column[0] = x;
        for (y = 1, lastdiag = x-1; y <= s1len; y++) {
            olddiag = column[y];
            column[y] = MIN3(column[y] + 1, column[y-1] + 1, lastdiag + (s1[y-1] == s2[x-1] ? 0 : 1));
            lastdiag = olddiag;
        }
    }
    return(column[s1len]);
}

void get_related_words(char *output, char* input)
{
	int i = 0;
	int count = 0;
	strcpy(output,"");
	
	for(i = 0; i < SIZE; i++)
	{
		if(levenshtein(wordlist[i],input) < 2 )//&& wordlist[i][0] == *input)
		{
			count++;
			//printf("%s\n",wordlist[i]);
			strcat(output,wordlist[i]);
			strcat(output,",");
		}
	}
	printf("\n%d\n",count);
}

