#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Compression.h"

Cel* createCel(char* word) {
	Cel* block = NULL;
	int size = strlen(word);

	block = (Cel*)malloc(sizeof(Cel));

	if(block == NULL) {
		fprintf(stderr, "Compression: Memory Allocation Error\n");
		return NULL;
	}

	block->word = (char*)malloc(sizeof(char) * (size+1));

	if(block->word == NULL) {
		fprintf(stderr, "Compression: Memory Allocation Error\n");
		free(block);
		return NULL;
	}

	strncpy(block->word, word, size);
	block->next = NULL;
	block->prev = NULL;

	return block;
}

