#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Compression.h"
#include "Utils.h"

int main(int argc, char *argv[]) {
	Dictionary* input = newDictionary();
	Dictionary* output = newDictionary();

	char txt[256] = "deux et deux, quatre";

	compress(input, txt);

	printf("Compression : %s\n", input->out);

	/*uncompression(output, input->out);*/

	freeDictionnary(input);
	freeDictionnary(output);

	return 0;
}