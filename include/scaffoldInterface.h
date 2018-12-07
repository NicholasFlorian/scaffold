#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#ifndef scaffold_interface
#define io_str

typedef struct ScaffoldUnit{
	
	char*	id;
	char*	message;

	bool	pass;
	
} scaffoldUnit;

typedef struct ScaffoldTest{
	
	char*	id;
	char*	message;
	int 	totalUnits;

	int		pass;
	int		fail;
	double 	passrate;
	

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


//ScaffoldInterface
int initializeScaffoldInterface(char* url, scaffoldInterface** obj);

void deleteScaffoldInterface(scaffoldInterface* obj);

char* printScaffoldInterface(scaffoldInterface* obj);

//scaffoldTest
int initializeScaffoldTest(scaffoldInterface* si, scaffoldTest** obj);

void deleteScaffoldTest(scaffoldTest* obj);

char* printScaffoldTest(scaffoldTest* obj);

//utility functions
int intlen(int num);

int doublelen(double num, char** formatted);

//reading functions
void lineReader(char** line, FILE *f);

int	lineLocator(int* startpos, int* endpos, char* line);

int nextInt(int* startpos, int* endpos, char* line);

char* nextString(int* startpos, int* endpos, char* line);


#endif
