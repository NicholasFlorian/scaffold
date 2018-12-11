#include <sys/types.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "scaffoldInterface.h"

//constants
#define READ_SIZE 200
#define UNUSED(x) (void)(x)


//colors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"


//temp main function
int main(int argc, char **argv){

	//var
	scaffoldInterface* si;
	int checksi;
	char* tempsi;

	scaffoldTest* st;
	int checkst;
	char* tempst;

	scaffoldUnit* su;
	int checksu;
	char* tempsu;


	//create scaffold interface
	checksi = initializeScaffoldInterface(argv[1], &si);
	printf("Scaffold: %d\n", checksi);

	//test print
	tempsi = printScaffoldInterface(si);
	printf("%s\n", tempsi);
	free(tempsi);

	//create test
	checkst = initializeScaffoldTest(si, &st);
	printf("Test: %d\n", checkst);

	//test print
	tempst = printScaffoldTest(st);
	printf("%s\n", tempst);
	free(tempst);


	//create unit
	checksu = initializeScaffoldUnit(si, &su);
	printf("Unit: %d\n", checksu);

	//test print
	tempsu = printScaffoldUnit(su);
	printf("%s\n", tempsu);


	_printStartOfInterface(si);
	_printStartOfTest(st);
	_printStartOfUnit(su);

	_printEndOfUnit(st,su,1);
	_printEndOfTest(si, st);
	_printEndOfInterface(si);

	//free scaffold interface
	deleteScaffoldInterface(si);
	deleteScaffoldTest(st);
	deleteScaffoldUnit(su);

	return 0;

}


//scaffoldInterface
int initializeScaffoldInterface(char* url, scaffoldInterface** obj){

	//var
	int 		urllen;
	char* 		line;
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
	(*obj)->url = malloc(sizeof(char) * (urllen + 1));
	strcpy((*obj)->url,url);



	//read in the first line of code
	lineReader(&line, (*obj)->file);


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
	char*	head;
	char*	footer;

	char* 	url;
	char* 	id;
	char* 	message;
	char*	totalTests;
	char*	totalPassrate;
	char*	totalPassrateVal;
	char*	averagePassrate;
	char*	averagePassrateVal;



	//assign
	UNUSED(fin);

	//malloc and build string, this memory is handled by compiler
	head			= "Scaffold Interface{";
	footer			= "}";

	url 			= "url: ";
	id				= "; id: ";
	message			= "; message: ";
	totalTests 		= "; totalTests: ";
	totalPassrate	= "; totalPassrate: ";
	averagePassrate = "; averagePassrate: ";


	//calculate size.
	len = 0;

	len+=strlen(head);
	len+=strlen(footer);

	len+=strlen(url);
	len+=strlen(obj->url);

	len+=strlen(id);
	len+=strlen(obj->id);

	len+=strlen(message);
	len+=strlen(obj->message);

	len+=strlen(totalTests);
	len+=intlen(obj->totalTests);

	len+=strlen(totalPassrate);
	len+=doublelen(obj->totalPassrate, &totalPassrateVal);

	len+=strlen(averagePassrate);
	len+=doublelen(obj->averagePassrate, &averagePassrateVal);

	len++;


	//assemble final string
	tempstr = malloc(sizeof(char) * (len));
	fin = sprintf(
			tempstr,
			"%s%s%s%s%s%s%s%s%d%s%s%s%s%s",
			head,
			url,
			obj->url,
			id,
			obj->id,
			message,
			obj->message,
			totalTests,			//int
			obj->totalTests,
			totalPassrate,
			totalPassrateVal,
			averagePassrate,
			averagePassrateVal,	//double
			footer);


	// free and return
	free(totalPassrateVal);
	free(averagePassrateVal);

	return tempstr;
}

void _printStartOfInterface(scaffoldInterface* obj){

	//	---------------------------------------------------
	//
	//		SCAFFOLD UNIT TESTER: <id>
	//		<message>
	//
	//			Reference File: 	<url>
	//			Total Tests:		<totalTests>
	//
	//	---------------------------------------------------
	//


	//print
	printf("%s-----------------------------------------------------------------------------%s\n",
			ANSI_COLOR_CYAN,
			ANSI_COLOR_RESET);

	printf("\n");

	printf("%s\tSCAFFOLD UNIT TESTER:%s %s\n",
			ANSI_COLOR_CYAN,
			ANSI_COLOR_RESET,
			obj->id);

	printf("\t%s\n", obj->message);

	printf("\n");

	printf("\t\t%sReference File:%s\t%s\n",
			ANSI_COLOR_CYAN,
			ANSI_COLOR_RESET,
			obj->url);

	printf("\t\t%sTotal Tests:%s\t%d\n",
			ANSI_COLOR_CYAN,
			ANSI_COLOR_RESET,
			obj->totalTests);

	printf("\n");

	printf("%s-----------------------------------------------------------------------------%s\n",
			ANSI_COLOR_CYAN,
			ANSI_COLOR_RESET);

	printf("\n");
}

void _printEndOfInterface(scaffoldInterface* obj){

	//		SCAFFOLD UNIT TESTER COMPLETE:
	//
	//			Total Tests:		<totalTests>
	//			Total Passrate:		<averagePassrate>
	//
	//	---------------------------------------------------
	//


	//calculate
	obj->averagePassrate = obj->totalPassrate / obj->totalTests;


	//print
	printf("%s\tSCAFFOLD UNIT TESTER COMPLETE:%s\n",
			ANSI_COLOR_CYAN,
			ANSI_COLOR_RESET);

	printf("\n");

	printf("\t\t%sTotal Tests:%s\t%d\n",
			ANSI_COLOR_CYAN,
			ANSI_COLOR_RESET,
			obj->totalTests);
	if(obj->totalPassrate > 0.5)
		printf("\t\t%sTotal Passrate:%s\t%.2lf\n",
				ANSI_COLOR_GREEN,
				ANSI_COLOR_RESET,
				obj->totalPassrate);
	else
		printf("\t\t%sTotal Passrate:%s\t%.2lf\n",
				ANSI_COLOR_RED,
				ANSI_COLOR_RESET,
				obj->totalPassrate);

	printf("\n");

	printf("%s-----------------------------------------------------------------------------%s\n",
			ANSI_COLOR_CYAN,
			ANSI_COLOR_RESET);

	printf("\n");
}


//scaffoldTest
int initializeScaffoldTest(scaffoldInterface* si, scaffoldTest** obj){

	//var
	char* 	line;
	int 	startpos;
	int 	endpos;


	//allocate memory
	*obj = malloc(sizeof(scaffoldTest));


	//read in the first line of code
	lineReader(&line, si->file);


	//initial conditions
	startpos = 0;
	endpos	= 0;

	//get data from file
	(*obj)->id			= nextString(&startpos, &endpos, line);
	(*obj)->message 	= nextString(&startpos, &endpos, line);
	(*obj)->totalUnits	= nextInt(&startpos, &endpos, line);

	//set 0
	(*obj)->pass		= 0;
	(*obj)->fail		= 0;
	(*obj)->passrate	= 0;


	//manage memory
	free(line);

	return 1;

}

void deleteScaffoldTest(scaffoldTest* obj){

	//free strings
	free(obj->id);
	free(obj->message);

	free(obj);

}

char* printScaffoldTest(scaffoldTest* obj){

	//var
	char* 	tempstr;
	int		len;
	int 	fin;
	char*	head;
	char*	footer;

	char*	id;
	char*	message;
	char*	totalUnits;
	char*	pass;
	char*	fail;
	char*	passrate;
	char*	passrateVal;


	//assign
	UNUSED(fin);

	//malloc and build string, this memory is handled by compiler
	head			= "Scaffold Test{";
	footer			= "}";

	id				= "id: ";
	message			= "; message: ";
	totalUnits 		= "; totalUnits: ";
	pass			= "; pass: ";
	fail			= "; fail: ";
	passrate		= "; passrate: ";


	//calculate size
	len = 0;

	len+=strlen(head);
	len+=strlen(footer);

	len+=strlen(id);
	len+=strlen(obj->id);

	len+=strlen(message);
	len+=strlen(obj->message);

	len+=strlen(totalUnits);
	len+=intlen(obj->totalUnits);

	len+=strlen(pass);
	len+=intlen(obj->pass);

	len+=strlen(fail);
	len+=intlen(obj->fail);

	len+=strlen(passrate);
	len+=doublelen(obj->passrate, &passrateVal);

	len++;


	//assemble final string
	tempstr = malloc(sizeof(char) * (len));
	fin = sprintf(
			tempstr,
			"%s%s%s%s%s%s%d%s%d%s%d%s%s%s",
			head,
			id,
			obj->id,
			message,
			obj->message,
			totalUnits,
			obj->totalUnits,	//int
			pass,
			obj->pass,			//int
			fail,
			obj->fail,			//int
			passrate,
			passrateVal,		//double
			footer);


	// free and return
	free(passrateVal);

	return tempstr;
}

void _printStartOfTest(scaffoldTest* obj){

	//		TEST: <id>
	//		<message>
	//
	//			Total Units:		<totalTests>
	//


	//print
	printf("%s\tTEST:%s %s\n",
			ANSI_COLOR_CYAN,
			ANSI_COLOR_RESET,
			obj->id);

	printf("\t%s\n", obj->message);

	printf("\n");

	printf("\t\t%sTotal Units:%s\t%d\n",
			ANSI_COLOR_CYAN,
			ANSI_COLOR_RESET,
			obj->totalUnits);

	printf("\n");

}

void _printEndOfTest(scaffoldInterface* si, scaffoldTest* obj){

	//	TEST COMPLETE:
	//
	//		Total Units:		<totalTests>
	//		Units Passed:		<pass>
	//		Units Failed:		<fail>
	//		Pass Rate:			<passmrate>
	//
	//	---------------------------------------------------
	//


	//var

	//calculate

	//if zero skip calculation
	if(!obj->pass)
		obj->passrate = 0;
	else
		obj->passrate = (obj->pass + obj->fail) / obj->pass;

	//store total passrate
	si->totalPassrate+=obj->passrate;


	//print
	printf("%s\tTEST COMPLETE:%s\n",
			ANSI_COLOR_CYAN,
			ANSI_COLOR_RESET);

	printf("\n");

	printf("\t\t%sTotal Units:%s\t%d\n",
			ANSI_COLOR_CYAN,
			ANSI_COLOR_RESET,
			obj->totalUnits);

	printf("\t\t%sUnits Passed:%s\t%d\n",
			ANSI_COLOR_CYAN,
			ANSI_COLOR_RESET,
			obj->pass);

	printf("\t\t%sUnits Failed:%s\t%d\n",
			ANSI_COLOR_CYAN,
			ANSI_COLOR_RESET,
			obj->fail);

	if(obj->passrate > 0.5)
		printf("\t\t%sPassrate:%s\t%.2lf\n",
				ANSI_COLOR_GREEN,
				ANSI_COLOR_RESET,
				obj->passrate);
	else
		printf("\t\t%sPassrate:%s\t%.2lf\n",
				ANSI_COLOR_RED,
				ANSI_COLOR_RESET,
				obj->passrate);

	printf("\n");

	printf("%s-----------------------------------------------------------------------------%s\n",
			ANSI_COLOR_CYAN,
			ANSI_COLOR_RESET);

}


//scaffoldUnit
int initializeScaffoldUnit(scaffoldInterface* si, scaffoldUnit** obj){

	//var
	char* 	line;
	int 	startpos;
	int 	endpos;


	//allocate memory
	*obj = malloc(sizeof(scaffoldUnit));


	//read in the first line of code
	lineReader(&line, si->file);


	//initial conditions
	startpos = 0;
	endpos	= 0;

	//get data from file
	(*obj)->id			= nextString(&startpos, &endpos, line);
	(*obj)->message 	= nextString(&startpos, &endpos, line);

	//set 0
	(*obj)->pass		= 0;

	//manage memory
	free(line);

	return 1;

}

void deleteScaffoldUnit(scaffoldUnit* obj){

	//free strings
	free(obj->id);
	free(obj->message);

	free(obj);

}

char* printScaffoldUnit(scaffoldUnit* obj){

	//var
	char* 	tempstr;
	int		len;
	int 	fin;
	char*	head;
	char*	footer;

	char*	id;
	char*	message;
	char*	pass;



	//assign
	UNUSED(fin);

	//malloc and build string, this memory is handled by compiler
	head			= "Scaffold Test{";
	footer			= "}";

	id				= "id: ";
	message			= "; message: ";
	pass			= "; pass: ";


	//calculate size
	len = 0;

	len+=strlen(head);
	len+=strlen(footer);

	len+=strlen(id);
	len+=strlen(obj->id);

	len+=strlen(message);
	len+=strlen(obj->message);

	len+=strlen(pass);
	len+=intlen(obj->pass);

	len++;


	//assemble final string
	tempstr = malloc(sizeof(char) * (len));
	fin = sprintf(
			tempstr,
			"%s%s%s%s%s%s%d%s",
			head,
			id,
			obj->id,
			message,
			obj->message,
			pass,
			obj->pass,			//int
			footer);

	return tempstr;

}

void _printStartOfUnit(scaffoldUnit* obj){

	//		UNIT TEST: <id>
	//			<message>


	//print
	printf("%s\t\tUNIT TEST:%s %s\n",
			ANSI_COLOR_YELLOW,
			ANSI_COLOR_RESET,
			obj->id);

	printf("\t\t\t   %s\n", obj->message);

	printf("\n");
}

void _printEndOfUnit(scaffoldTest* st, scaffoldUnit* obj, int pass){

	//			TEST PASSED / TEST FAILED
	//


	//calculate
	if(pass)
		st->pass++;
	else
		st->fail++;


	//print
	if(pass)
		printf("\t\t%sTEST PASSED%s\t\n",
				ANSI_COLOR_GREEN,
				ANSI_COLOR_RESET);
	else
		printf("\t\t%sTEST FAILED%s\t\n",
				ANSI_COLOR_RED,
				ANSI_COLOR_RESET);

	printf("\n");
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

int doublelen(double num, char** formatted){

	//var
	char 	*display;
	int		len;
	int		fin;


	//assign
	UNUSED(fin);


	//calculate whole value
	len = intlen((int) num);

	//add 3 for decimal value
	len+=4;


	//create string
	display = malloc(sizeof(char) * (len + 1));
	fin 	= sprintf(display, "%.2f", num);


	//return
	*formatted = display;
	return len;

}


//reading functions
void lineReader(char** line, FILE *f){

	//these extra steps prevent segfaults in linux

	//var
	char	tempstr[READ_SIZE];


	//assign
	*line	= malloc(sizeof(char) * READ_SIZE);

	//get data
	fgets(tempstr, sizeof(tempstr), f);

	//copy assigne over temp string
	strcpy(*line, tempstr);
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
