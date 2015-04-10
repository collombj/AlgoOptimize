#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Compression.h"
#include "Utils.h"

int main(int argc, char *argv[]) {
	initDictionary();

	char txt[256] = "deux et deux, quatre\nquatre et quatre, huit";

	compress(txt);

	printf("Compression : %s\n", getOutput());

	freeDictionnary();

	return 0;
}