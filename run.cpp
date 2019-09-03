#pragma once
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<vector>

BOOL SaveFile(HWND hEdit, LPSTR pszFileName);

void divide_string(char* text, const char* divisor, std::vector<char*>& char_pointer_array)
{
   char *substr = NULL;
   substr = strtok(text, divisor);
   while(substr!=NULL)
   {
	   	char_pointer_array.push_back((char*)malloc(sizeof(substr + 1)));
	    strcpy(char_pointer_array.back(), substr);
	    substr = strtok(NULL, divisor);
   }
}

char* concat(std::vector<char*> entity, const char* unitor, int from)
{
	int size = 1;
	for(char* str : entity)
		size += strlen(str) + strlen(unitor);
	char* new_str = (char*)malloc(size);
	new_str[0] = 0;
	for(int i = from; i < entity.size(); i++)
		strcat(new_str, entity[i]), strcat(new_str, unitor);
	return new_str;
}

//system is alive a lifo
void run(char* text)
{
	std::vector<char*> lines;
	divide_string(text, "\n", lines);
	for(char* line : lines)
	{
		//MessageBox(0, line,"Error!", 0);
		std::vector<char*> words;
		divide_string(line, " ", words);
		if(!strcmp(words[0], "system"))
		{
			char* command = concat(words, "  ", 1);
			system(command);
			free(command);
		}
		if(!strcmp(words[0], "create"))
		{
			char* filename = NULL, *append = concat(words, " ", 1);
			GetCurrentDirectory(0, filename), filename = (char*)realloc(filename, sizeof(filename) + sizeof(append) + 1);
			strcat(filename, append), MessageBox(0, filename,"Error!", 0);//SaveFile(GetDlgItem(hwnd, IDC_MAIN_TEXT), (LPSTR)filename);
			free(append);
			//free(filename);
		}
	}
	if(text != NULL){free(text);}
}
