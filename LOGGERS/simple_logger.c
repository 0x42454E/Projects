#include <stdio.h>  /* printf scanf fputs */
#include <stdlib.h> /* size_t free 	  */
#include <string.h> /* strcmp strcpy	  */

/**
 * This C-based logger utility allows a user to interact with a text file through the terminal,
 * offering several common logging-related operations:
 *
 * Writing new lines to a file
 * Inserting lines at the beginning of the file
 * Counting the number of lines in a file
 * Deleting the file
 * Exiting gracefully
 *
 * 
 * On launch, the user is prompted to enter a file name to operate on.
 * The program then enters a loop:
 * 	Accepts user input (a command or plain text).
 *	Parses it through Compare().
 *	Dispatches it to the appropriate handler using array[] of function pointers.
 * 
 *
 * Commands: -exit, -remove, -count, and lines beginning with < are handled specially.
 * Regular input is appended to the file.
 *
 * Author: Ben
 * Date: 2024-09
 */
 
void Initiate();
void CountLines(char *string_input);
void RmFile(char *string_input);
void CheckChar(char *string_input); 
void StringInput();
int Compare(char *string_input);
void Write(char *string_input);
void WriteBeginning(char *string_input);
void Exit(char *string_input);

typedef void (*function_pointer)(char*);
typedef int (*Compare_pointer)(char*);
	
	typedef struct struc
	{
	char *string;
	Compare_pointer comparison;
	function_pointer operation;
	} command_chain;

	command_chain array[5];
	
	enum chain_result
	{
		REMOVE,
		COUNT,
		BRACKET,
		EXIT,
		WRITE,
		BREAK
	};
	
	char name_string[100];	
	enum chain_result quit_command;
		
int main()
{
	Initiate();
	
	return 0;
}

void Initiate()
{
	enum chain_result proceed;
	
	printf ("enter your file_name:\n");
	
	scanf ("%s", name_string);
	getchar();
	
	array[REMOVE].comparison = Compare;	
	array[REMOVE].operation = RmFile;
	array[COUNT].comparison = Compare;	
	array[COUNT].operation = CountLines;
	array[BRACKET].comparison = Compare;	
	array[BRACKET].operation = WriteBeginning;
	array[EXIT].comparison = Compare;	
	array[EXIT].operation = Exit;
	array[WRITE].comparison = Compare;	
	array[WRITE].operation = Write;
	
	while (1)
	{ 
		quit_command = WRITE;
		
		StringInput();
	
		proceed = array[0].comparison(array[0].string);
		
		array[proceed].operation(array[0].string); 	
		
		free(array[0].string);
		
		if (BREAK == quit_command)
		{
			break;
		}
	}	
	
	return; 
}

void StringInput() 
{
	char string_input[200];
	array[0].string = NULL;
	
		printf("Insert next line:\n");
			
		if (fgets(string_input, sizeof(string_input), stdin) != NULL)
		{
			array[0].string =(char *) malloc(200 * sizeof(char));
				
				if (NULL == array[0].string)
	       			{
	       				printf("malloc failed.\n");
	       			}
			
       			strcpy(array[0].string, string_input);		
		}
}

void Write(char *string_input)
{
	FILE *file;
	file = fopen(name_string, "a");
	
	printf("writing.. %s", string_input);
	
	if (NULL == file) 
	{
		perror("File open error");
		return;
   	}
		fputs(string_input, file);

	fclose(file);
} 

void WriteBeginning(char *string_input)
{	

	char *str;
	FILE *file;
	file = fopen(name_string, "r");

	
	if (file == NULL) 
	{
		perror("File open error");
		return;
   	}
   	
	str = (char *) malloc(200 * sizeof(char));
	
	if (fgets(str, sizeof(str), file) != NULL) 
	{
       		 printf("Read line: %s", str);
    	}
    	else
    	{
    		printf("error reading line\n");
    	}
    	
    	fclose(file);
    	
    	file = fopen(name_string, "w");
    	
    	fprintf(file, "%s\n", string_input + 1);
    	fprintf(file, "%s", str);
	
	free(str);
	fclose(file);
}

void RmFile(char *string_input) 
{
	printf("%s has inserted.\n", string_input);
	
	if (remove(name_string) != 0)
	{
		perror("Error deleting file\n");
	}
	else
	{
		printf("File successfully deleted.\n");
		quit_command = BREAK;
	}
}

void CountLines(char *string_input) 
{
	char ch;
	int lines_count;
	FILE *file;
	file = fopen(name_string, "r");
	
	printf("%s has inserted.\n", string_input);
	
	if (NULL == file)
	{
		printf("String Input Error.\n");
	}
	
	lines_count = 0;
	
	while((ch = fgetc(file))!= EOF) 
	{
	        if(ch == '\n')
		{	
			 lines_count++;
	   	}
	}
		printf("number of lines: %d\n", lines_count);
}

void CheckChar(char *string_input)
{
	
	if (string_input[0] == '<')
	{
		WriteBeginning(string_input);
	}
}

void Exit(char *string_input)
{
	printf("%s has inserted.\n", string_input);
	quit_command = BREAK;
}

int Compare(char *string_input) 
{
	enum chain_result result = WRITE;
	char exit_command[] = "-exit\n";
	char remove_command[] = "-remove\n";
	char count_command[] = "-count\n";
	
	if (strcmp(string_input, exit_command) == 0)
	{
		result = EXIT;
	}		
	else if (strcmp(string_input, remove_command) == 0)
	{
		result = REMOVE;
	}		
	else if (strcmp(string_input, count_command) == 0)
	{
		result = COUNT;
	}
	else if (*string_input == '<')
	{
		result = BRACKET;
	}
	else
	{
		result = WRITE;
	}
	
	return result;
}
