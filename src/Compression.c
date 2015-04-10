#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Compression.h"
#include "Utils.h"

#define BUFFER 256

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
	Cel* ptr      = NULL;
	int  pos	  = 1;
	char tmp[BUFFER];

	/* Liste Vide */
	if(d->l == NULL) {
		d->l = createCel(word);

		if(d->l == NULL) {
			fprintf(stderr, "Compression: Allocation Error\n");
			return false;
		} else {
			sprintf(tmp, "%d %d %s", 0, (int)strlen(word), word);
			if(reallocString(&(d->out), strlen(tmp))) {
				sprintf(d->out, "%s", tmp);
				return true;
			} else {
				return false;
			}
		}
	}

	ptr = (d->l);

	/* Mot en premier */
	if(strcmp(ptr->word, word) == 0) {
		sprintf(tmp, "%d", pos);
		if(reallocString(&(d->out), strlen(d->out) + strlen(tmp))) {
			sprintf(d->out, "%s %s", d->out, tmp);
			return true;
		} else {
			return false;
		}
	}

	/* Parcours de la liste */
	while(ptr->next != NULL) {
		if(strcmp(ptr->word, word) == 0) {
			sprintf(tmp, "%d", pos);
			if(reallocString(&(d->out), strlen(d->out) + strlen(tmp))) {
				sprintf(d->out, "%s %s", d->out, tmp);
				moveToBeginning(&(d->l), ptr);
				return true;
			} else {
				return false;
			}
		}
		
		pos++;
		ptr = ptr->next;
	}

	/* En dernier */
	if(strcmp(ptr->word, word) == 0) {
		sprintf(tmp, "%d", pos);
		if(reallocString(&(d->out), strlen(d->out) + strlen(tmp))) {
			sprintf(d->out, "%s %s", d->out, tmp);
			moveToBeginning(&(d->l), ptr);
			return true;
		} else {
			return false;
		}
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
		sprintf(tmp, "%d %d %s", 0, (int)strlen(word), word);
		if(reallocString(&(d->out), strlen(d->out) + strlen(tmp))) {
			sprintf(d->out, "%s %s", d->out, tmp);
			return true;
		} else {
			return false;
		}
	}
}

void moveToBeginning(List* l, Cel* move) {
	if(move == NULL || *l == NULL) {
		return;
	}

	if(move->next != NULL) {
		move->next->prev = move->prev;
	}

	if(move->prev != NULL) {
		move->prev->next = move->next;
	}

	move->prev = NULL;
	move->next = *l;
	(*l)->prev = move;
	*l = move;
}

void compress(Dictionary* d, char* txt) {
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
				addWord(d, word);
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
				printf("%s\n", odd);
				addWord(d, odd);
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
		addWord(d, odd);
	} else {
		strncpy(word, txt + p_word, i-p_word);
		word[i-p_word] = '\0';
		addWord(d, word);
	}
}

void freeDictionnary(Dictionary* d) {
	Cel* tmp = NULL;

	free(d->out);
	d->out = NULL;

	while(d->l != NULL) {
		tmp = d->l->next;

		free(d->l->word);
		free(d->l);

		d->l = tmp;
	}

	d = NULL;
}