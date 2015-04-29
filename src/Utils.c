#include <stdio.h>

#include "Utils.h"


void getHelp() {
	printf("#################################################\n");
	printf("# ESIPE                              Algorithme #\n");
	printf("#                                               #\n");
	printf("#           Algoritme de Compression            #\n");
	printf("#                                               #\n");
	printf("# FORET Gael                    COLLOMB Jérémie #\n");
	printf("# Version 1.0                                   #\n");
	printf("#################################################\n");
	

	printf("Usage:\n");
	printf("Compress [-c|-d] input output\n");
	printf("\t -c is to compress the input file to the output file.\n");
	printf("\t -d is to uncompress the input file into the output file.\n\n");
}