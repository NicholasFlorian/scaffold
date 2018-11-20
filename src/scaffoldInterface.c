#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "scaffoldInterface.h"


int main(int argc, char **argv){

	//var
	scaffoldInterface* si;
	int sicheck;
	char* temp;


	//create scaffold interface
	sicheck = initializeScaffoldInterface(argv[1], &si);
	printf("%d\n", sicheck);

	//test print
	temp = printScaffoldInterface(si);
	printf("%s\n", temp);
	free(temp);

	//free scaffold interface
	deleteScaffoldInterface(si);

	return 0;

}

int initializeScaffoldInterface(char* url, scaffoldInterface** obj){

	//var
	int urllen;
	char* 		line;
	ssize_t 	len;
	int 		startpos;
	int 		endpos;


	//create memory for object
	*obj = malloc(sizeof(scaffoldInterface));

	//if null return error
	if((*obj) == NULL)
		return -1;


	//file operationss
	(*obj)->file 	= fopen(url, "r");
	if((*obj)->file == NULL){

		//clear memory
		free((*obj));
		return -1;
	}


	//save url
	urllen 		= strlen(url);
	(*obj)->url = malloc(sizeof(char) * urllen);
	strcpy((*obj)->url,url);



	//assign
	line = NULL;

	//read in the first line of code
	len = lineReader(&line, (*obj)->file);


	//initial conditions
	startpos = 0;
	endpos	= 0;


	//get data from file
	(*obj)->id			= nextString(&startpos, &endpos, line);
	(*obj)->message 	= nextString(&startpos, &endpos, line);
	(*obj)->totalTests	= nextInt(&startpos, &endpos, line);

	//set 0
	(*obj)->totalPassrate = 0;
	(*obj)->averagePassrate = 0;


	//manage memory
	free(line);

	return 1;
}

void deleteScaffoldInterface(scaffoldInterface* obj){

	//close and free file
	fclose(obj->file);

	//free strings
	free(obj->url);
	free(obj->id);
	free(obj->message);

	free(obj);

}

char* printScaffoldInterface(scaffoldInterface* obj){

	//var
	char* 	tempstr;
	int		len;
	int 	fin;
	char*	main;
	char* 	url;
	char* 	id;
	char* 	message;
	char*	totalTests;
	//char*	totalPassrate;
	//char*	averagePassrate;
	char*	footer;


	//malloc and build string
	main 			= malloc(sizeof(char) * 20);
	main			= "Scaffold Interface{";

	url 			= malloc(sizeof(char) * 6);
	url 			= "url: ";

	id				= malloc(sizeof(char) * 7);
	id				= "; id: ";

	message			= malloc(sizeof(char) * 12);
	message			= "; message: ";

	totalTests		= malloc(sizeof(char) * 15);
	totalTests 		= "; totalTests: ";

	//totalPassrate 	= malloc(sizeof(char) * 18);
	//totalPassrate	= "; totalPassrate: ";

	//averagePassrate = malloc(sizeof(char) * 20);
	//averagePassrate = "; averagePassrate: ";

	footer			= malloc(sizeof(char) * 3);
	footer			= ";}";


	//calculate size.
	len = 0;

	len+=strlen(main);

	len+=strlen(url);
	len+=strlen(obj->url);

	len+=strlen(id);
	len+=strlen(obj->id);

	len+=strlen(message);
	len+=strlen(obj->message);

	len+=strlen(totalTests);
	len+=intlen(obj->totalTests);

	len+=strlen(footer);
	len++;

	//assemble final string
	tempstr = malloc(sizeof(char) * (len));

	fin = sprintf(
			tempstr,
			"%s%s%s%s%s%s%s%s%d%s",
			main,
			url,
			obj->url,
			id,
			obj->id,
			message,
			obj->message,
			totalTests,
			obj->totalTests,
			footer);

	//free(main);
	//free(url);
	//free(id);
	//free(message);
	//free(totalTests);
	//free(footer);

	return tempstr;
}

//utility functions
int intlen(int num){

	//var
	int count;


	//assign
	count = 0;

	//negative check
	if(num < 0)
		count++;

	while(num != 0){

		num/=10;
		count++;
	}

	return count;
}

//reading functions
ssize_t lineReader(char** line, FILE *f){

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
	*line = newLine;
	return totalLength;
}

int	lineLocator(int* startpos, int* endpos, char* line){

	//var
	bool		read;
	int			len;
	int 		templen;

	//assign;
	read		= 0;
	*startpos	= *endpos;
	*endpos		= 0;
	len 		= strlen(line);

	for(int i = *startpos; i < len && !(*endpos); i++){

		if(line[i] == '<'){

			read = 1;
			*startpos = i+1;
		}

		if(read && line[i] == '>')
			*endpos = i;
	}

	templen	= *endpos - *startpos;


	return templen;

}

int nextInt(int* startpos, int* endpos, char* line){

	//var
	char* 	tempstr;
	int 	tempint;


	//save the string
	tempstr = nextString(startpos, endpos, line);

	//convert
	tempint = atof(tempstr);

	//free old string
	free(tempstr);


	//return value
	return tempint;

}

char* nextString(int* startpos, int* endpos, char* line){

	//var
	char* tempstr;
	int templen;

	//find string location
	templen = lineLocator(startpos, endpos, line);

	//define memory
	tempstr	= malloc(sizeof(char) * templen + 1);

	//copy string
	for(int i = 0; i < templen; i++)
		tempstr[i] = line[i + *startpos];
	tempstr[templen] = '\0';

	return tempstr;

}





