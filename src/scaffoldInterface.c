#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "scaffoldInterface.h"
 

int main(int argc, char **argv){

	//
	scaffoldInterface* si;
	int check;


	check = initializeScaffoldInterface(argv[1], &si);

	printf("%d\n", check);

	return 0;

}

int initializeScaffoldInterface(char* url, scaffoldInterface** obj){
	
	//create memory for object
	*obj 			= malloc(sizeof(scaffoldInterface));

	//if null return error
	if((*obj) == NULL)
		return -1;

	//file operations
	(*obj)->file 	= fopen(url, "r");
	if((*obj)->file == NULL){

		//clear memory
		free((*obj));
		return -1;
	}

	//save url
	strcpy((*obj)->url,url);
	

	//populate scaffold with file data
	return _initializeScaffoldInterface(obj);
}

int _initializeScaffoldInterface(scaffoldInterface** obj){
	
	//var
	char* 		line;
	ssize_t 	len;
	bool		read;
	int 		startpos;
	int			endpos;
	int 		templen;
	char*		tempId;
	char*		tempMessage;

	//assign
	line = NULL;


	//read in the first line of code
	len = lineReader(line, (*obj)->file);

	//parse id
	read		= 0;
	startpos	= 0;
	endpos		= 0;
	for(int i = 0; i < len && !endpos; i++){

		if(line[i] == '<')
			read = 1;

		if(read && !startpos)
			startpos = i;

		if(read && line[i] == '>')
			endpos = i;
	}

	templen			= endpos - startpos;
	tempMessage 	= malloc(sizeof(char) * templen + 1);
	for(int i = 0; i < endpos; i++)
		tempMessage[i] = line[i + startpos];
	tempMessage[templen] = '\0';

	//parse message

	//parse total tests


	return 1;
}

ssize_t lineReader(char* line, FILE *f){

	//var
	char* 		newLine;
	size_t		size;
	ssize_t		totalLength;


	//assign
	newLine = NULL;
	size = 0;


	//read line
	totalLength = getline(&newLine, &size, f);


	//return data
	line = newLine;
	return totalLength;
}


void deleteScaffoldInterace(scaffoldInterface* obj){


	//close file
	//free memory
}



