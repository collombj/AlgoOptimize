#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Compression.h"
#include "Utils.h"

Dictionary* newDictionary() {
	Dictionary* d = (Dictionary*)malloc(sizeof(Dictionary));

	if(d == NULL) {
		fprintf(stderr, "Compression: Memory Allocation Error\n");
		return NULL;
	}

	d->l = NULL;
	d->out = NULL;

	return d;
}

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

bool addWord(Dictionary* d, char* word) {
	Cel* block    = NULL;
	Cel* ptr      = NULL;
	int  pos	  = 1;

	/* Liste Vide */
	if(d->l == NULL) {
		d->l = createCel(word);

		if(d->l == NULL) {
			fprintf(stderr, "Compression: Allocation Error\n");
			return false;
		} else {
			printf("%d %s ", 0, word);
			return true;
		}
	}

	ptr = (d->l);

	/* Mot en premier */
	if(strcmp(ptr->word, word) == 0) {
		printf("%d ", pos);
		return true;
	} else {
		pos++;
	}

	/* Parcours de la liste */
	while(ptr->next != NULL) {
		if(strcmp(ptr->word, word) == 0) {
			printf("%d ", pos);
			return true;
		}
		
		pos++;
		ptr = ptr->next;
	}

	/* En dernier */
	if(strcmp(ptr->word, word) == 0) {
		printf("%d ", pos);
		return true;
	} else {
		pos++;
	}

	/* Non dans la liste */
	ptr->next = createCel(word);

	if(ptr->next == NULL) {
		fprintf(stderr, "Compression: Allocation Error\n");
		return false;
	} else {
		ptr->next->prev = ptr;
		printf("%d %s ", 0, word);
		return true;
	}

}