/**
 * 	@file Compression.c
 * 	
 * 	@author COLLOMB Jérémie <contact@collombj.com>
 * 			FORET   Gaël    <gforet@etud.u-pem.fr>
 * 			
 * 	@date 20/04/2015
 * 	
 * 	@brief Librairie de compression et de décompression.
 * 	
 * 	@details La librairie permet de compresser et de décompresser un fichier.
 * 			 La librairie offre les fonctions suivantes :
 * 			 
 * 			 - initList()       	 -- Pour initialiser la liste
 * 			 - createCel(char*) 	 -- Pour allouer une cellule en mémoire
 * 			 - compress(char)   	 -- Pour traiter un mot. Si le mot existe, on ajoute l'indice dans le texte compressé, sinon on créé une cellule en agissant dans le texte compressé.
 * 			 - moveTobeginning(Cel*) -- Pour déplacer une cellule en tête de liste.
 * 			 - freeDictionnary()     -- Pour libérer la liste.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Compression.h"
#include "Utils.h"
#include "File.h"

/**
 * @brief Variable static permettant de stocker la liste des mots.
 */
static List d;

void initList() {
	d = NULL;
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

bool compress(char* word) {
	List ptr      = NULL;
	int  pos	  = 1;

	/* Liste Vide */
	if(d == NULL) {
		d = createCel(word);

		if(d == NULL) {
			fprintf(stderr, "Compression: Allocation Error\n");
			return false;
		} else {
			convertNewWordToBinary(strlen(word), word);
			return true;
		}
	}

	/* Itérateur */
	ptr = d;

	/* Mot en premier */
	if(strcmp(ptr->word, word) == 0) {
		convertPositionToBinary(pos);
		return true;
	}

	/* Parcours de la liste */
	while(ptr->next != NULL) {
		if(strcmp(ptr->word, word) == 0) {
			convertPositionToBinary(pos);
			moveToBeginning(ptr);
			return true;
		}
		
		pos++;
		ptr = ptr->next;
	}

	/* En dernier */
	if(strcmp(ptr->word, word) == 0) {
		convertPositionToBinary(pos);
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
		convertNewWordToBinary(strlen(word), word);
		return true;
	}
}

void moveToBeginning(Cel* move) {
	if(move == NULL || d == NULL) {
		return;
	}

	if(move->next != NULL) {
		move->next->prev = move->prev;
	}

	if(move->prev != NULL) {
		move->prev->next = move->next;
	}

	move->prev = NULL;
	move->next = d;
	d->prev = move;
	d = move;
}

void freeDictionnary() {
	List tmp = NULL;

	while(d != NULL) {
		tmp = d->next;

		free(d->word);
		free(d);

		d = tmp;
	}
}



bool addWordTailList(char* word){
	List copyList = d; 
	Cel* tailCel = createCel(word);

	if(tailCel == NULL) /* contrôle */
		return false;

	if(d == NULL){ /* cas liste vide */
		d = tailCel;
		return true;
	}

	while(copyList->next != NULL){ /* boucle sur la liste */
		copyList = copyList->next;
	}

	/* ajout en fin de liste */
	tailCel->next = NULL;
	tailCel->prev = copyList;
	copyList->next = tailCel;

	return true;
}



Cel* getCelFromPos(int pos){
	int cpt = 1;
	List copyList = d; 

	while(copyList != NULL){ /* boucle sur la liste */
		if(pos == cpt){
			return copyList; /* return la cellule */
		}
		copyList = copyList->next;
		cpt++;
	}
	return NULL;
}



bool uncompressNewWord(int size, char* word){
	bool res;
  	writeBinaryFromText(word, strlen(word)); /* écriture dans le fichier de sortie */
  	res = addWordTailList(word); /* ajout en queue */

  	if(res == false) /* contrôle */
  		return false;
  	return true;
}



bool uncompressExistingWord(int pos){
	Cel* celPos;

	celPos = getCelFromPos(pos); /* on récupère la cellule à la position pos */
	if (celPos == NULL){
		return false;
	}

	writeBinaryFromText(celPos->word, strlen(celPos->word)); /* écriture dans le fichier de sortie */
	moveToBeginning(celPos); /* on déplace en tête de liste */

	return true;
}
