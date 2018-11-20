#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifndef scaffold_interface
#define io_str

typedef struct ScaffoldUnit{
	
	char*	id;
	char*	message;
	void*	data;
	bool	pass;
	
} scaffoldUnit;

typedef struct ScaffoldTest{
	
	char*	id;
	char*	message;
	int		pass;
	int		fail;
	double 	passrate;
	
	int 	testNum;
	scaffoldUnit* units;
	
} scaffoldTest;

typedef struct ScaffoldInterface{
	
	FILE* file;
	char*	url;
	
	char* 	id;
	char* 	message;
	int		totalTests;

	double 	totalPassrate;
	double 	averagePassrate;
	
	scaffoldTest* tests;

} scaffoldInterface;

int initializeScaffoldInterface(char* url, scaffoldInterface** obj);

void deleteScaffoldInterface(scaffoldInterface* obj);

char* printScaffoldInterface(scaffoldInterface* obj);

//utility functions
int intlen(int num);

//reading functions
ssize_t lineReader(char** line, FILE *f);

int	lineLocator(int* startpos, int* endpos, char* line);

int nextInt(int* startpos, int* endpos, char* line);

char* nextString(int* startpos, int* endpos, char* line);


#endif
