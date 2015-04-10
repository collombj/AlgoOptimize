#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Utils.h"

bool reallocString(char** input, int size) {
	char* new = (char*)realloc(*input, sizeof(char)*(size+1));

	if(new == NULL) {
		fprintf(stderr, "Utils: String allocation Error\n");
		return false;
	} else {
		*input = new;
		return true;
	}
}