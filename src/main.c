#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Compression.h"
#include "Utils.h"

int main(int argc, char *argv[]) {
	Dictionary* d = newDictionary();

	printf("%p\n", d->l);
	addWord(d, "deux");
	addWord(d, "et");
	addWord(d, "deux");
	addWord(d, "quatre");

	printf("\n");

	return 0;
}