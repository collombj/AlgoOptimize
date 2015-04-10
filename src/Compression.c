#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Compression.h"
#include "Utils.h"

#define BUFFER 256

static Dictionary d;

void initDictionary() {
	d.l = NULL;
	d.size = 0;
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

bool addWord(char* word) {
	List ptr      = NULL;
	int  pos	  = 1;
	char tmp[BUFFER];

	/* Liste Vide */
	if(d.l == NULL) {
		d.l = createCel(word);

		if(d.l == NULL) {
			fprintf(stderr, "Compression: Allocation Error\n");
			return false;
		} else {
			sprintf(tmp, "%d %d %s ", 0, (int)strlen(word), word);
			addWordToOutput(tmp);
			return true;
		}
	}

	/* Itérateur */
	ptr = d.l;

	/* Mot en premier */
	if(strcmp(ptr->word, word) == 0) {
		sprintf(tmp, "%d ", pos);
		addWordToOutput(tmp);
		return true;
	}

	/* Parcours de la liste */
	while(ptr->next != NULL) {
		if(strcmp(ptr->word, word) == 0) {
			sprintf(tmp, "%d ", pos);
			addWordToOutput(tmp);
			moveToBeginning(ptr);
			return true;
		}
		
		pos++;
		ptr = ptr->next;
	}

	/* En dernier */
	if(strcmp(ptr->word, word) == 0) {
		sprintf(tmp, "%d ", pos);
		addWordToOutput(tmp);
		moveToBeginning(ptr);
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
		sprintf(tmp, "%d %d %s ", 0, (int)strlen(word), word);
		addWordToOutput(tmp);
		return true;
	}
}

void moveToBeginning(Cel* move) {
	if(move == NULL || d.l == NULL) {
		return;
	}

	if(move->next != NULL) {
		move->next->prev = move->prev;
	}

	if(move->prev != NULL) {
		move->prev->next = move->next;
	}

	move->prev = NULL;
	move->next = d.l;
	d.l->prev = move;
	d.l = move;
}

void compress(char* txt) {
	int i, size = strlen(txt);
	int p_odd = -1, p_word = -1;
	char word[BUFFER], odd[BUFFER];

	for(i = 0 ; i < size ; i++) {
		/* Caractères spéciaux*/
		if(
			txt[i] <= 47 ||
			(txt[i] >= 58 && txt[i] <= 64) ||
			(txt[i] >= 91 && txt[i] <= 96) ||
			(txt[i] >= 123 && txt[i] <= 126)
		) {
			/* Remplacement de l'espace */
			if(txt[i] == ' ') {
				txt[i] = '_';
			}

			/* Debut des caractères spéciaux */
			if(p_odd == -1 && p_word != -1) {
				strncpy(word, txt + p_word, i-p_word);
				word[i-p_word] = '\0';
				addWord(word);
			}
			if(p_odd == -1) {
				p_odd = i;
				p_word = -1;
			}
		} else {
			/* Debut des mots */
			if(p_word == -1 && p_odd != -1) {
				strncpy(odd, txt + p_odd, i-p_odd);
				odd[i-p_odd] = '\0';
				addWord(odd);
			}
			if(p_word == -1) {
				p_word = i;
				p_odd = -1;
			}
		}
	}

	if(p_odd != -1) {
		strncpy(odd, txt + p_odd, i-p_odd);
		odd[i-p_odd] = '\0';
		addWord(odd);
	} else {
		strncpy(word, txt + p_word, i-p_word);
		word[i-p_word] = '\0';
		addWord(word);
	}
}

void freeDictionnary() {
	List tmp = NULL;

	while(d.l != NULL) {
		tmp = d.l->next;

		free(d.l->word);
		free(d.l);

		d.l = tmp;
	}
}

void addWordToOutput(char* word) {
	strcat(d.out, word);
	d.size += strlen(word);
}

char* getOutput() {
	return d.out;
}