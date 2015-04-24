/**
 * 	@file File.c
 * 	
 * 	@author COLLOMB Jérémie <contact@collombj.com>
 * 			FORET   Gaël    <gforet@etud.u-pem.fr>
 * 			
 * 	@date 20/04/2015
 * 	
 * 	@brief Librairie des écritures et lectures dans des fichiers.
 * 	
 * 	@details La librairie permet de lire et écrire (en binaire et en texte clair) dans un fichier
 * 			 La librairie offre les fonctions suivantes :
 * 			 
 * 			 - open(char*, char*) -- Pour ouvrir un fichier d'entrée et un fichier de sortie.
 * 			 - close()            -- Pour fermer les fichiers d'entrée et de sortie.
 * 			 
 * 			 - ... vers binaire
 * 			 	- writeBinaryFromShort(short) 	   -- Pour écrire (en bianire -- fichier de sortie) un élément de taille 2 octets (short).
 * 			 	- writeBinaryFromChar(char)   	   -- Pour écrire (en binaire -- fichier de sortie) un élément de taille 1 octet  (char).
 * 			 	- writeBinaryFromText(char*, int)  -- Pour écrire (en binaire -- fichier de sortie) un élément de longueur définis.
 * 			 	
 * 			 - Binaire vers ...
 * 			 	- readShortFromBinary() 					-- Pour lire (du binaire -- fichier d'entrée) un élément de taille 2 octets (short).
 * 			 	- readCharFromBinary()  					-- Pour lire (du binaire -- fichier d'entrée) un élément de taille 2 octets (short).
 * 			 	- readTextFromBinary(char* txt, int length) -- Pour lire (du binaire -- fichier d'entrée) un texte de longueur définis.
 * 			 	
 * 			 - convertNewWordToBinary(int, char*)  -- Pour écrire un nouveau mot (compressé) dans le fichier.
 * 			 - convertPositionToBinary() 		   -- Pour écrire la position d'un mot déjà compressé.
 * 			 
 * 			 - ParseText() -- Pour parser et compresser le fichier en entrée vers le fichier en sortie.
 * 			 - parseBinary -- Pour parser et décompresser le fichier en entrée vers  le fichier en sortie.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "File.h"
#include "Compression.h"
#include "Utils.h"

/**
 * @brief Variable stockant le FileDesctriptor du fichier d'entrée (ouvert en lecture).
 */
static FILE* fin = NULL;

/**
 * @brief Variable stockant le FileDesctriptor du fichier de sortie (ouvert en écriture).
 */
static FILE* fout = NULL;

bool open(char* input, char* output) {
	fin = fopen(input, "rb");
	fout = fopen(output, "wb");

	if(fin == NULL) {
		fprintf(stderr, "FILE %s: Openning failed.\nThe file may be not exist, or right privilege needed.\n", input);
		return false;
	}

	if(fout == NULL) {
		fprintf(stderr, "FILE %s: Openning failed.\nThe file may be not exist, or right privilege needed.\n", output);
		fclose(fin);
		return false;
	}

	return true;
}

void close() {
	fclose(fin);
	fclose(fout);
	fin = NULL;
	fout = NULL;
}

void writeBinaryFromShort(short nb) {
	fwrite(&nb, sizeof(short), 1, fout);
}

void writeBinaryFromChar(char c) {
	fwrite(&c, sizeof(char), 1, fout);
}

void writeBinaryFromText(char* txt, int length) {
	fwrite(txt, sizeof(char), length, fout);
}



short readShortFromBinary() {
	short s;
	if(fread(&s, sizeof(short), 1, fin) == 0) {
		return -1;
	}

	return s;
}

char readCharFromBinary() {
	char c;
	if(fread(&c, sizeof(char), 1, fin) == 0) {
		return -1;
	}

	return c;
}

void readTextFromBinary(char* txt, int length) {
	if(fread(txt, sizeof(char), length, fin) == 0) {
		txt[0] = '\0';
	}
}



void convertNewWordToBinary(int size, char* word) {
	writeBinaryFromShort(0);			/* Ecriture de la position */
	writeBinaryFromChar(size);			/* Ecriture de la taille du mot */
	writeBinaryFromText(word, size);	/* Ecriture du mot */
}

void convertPositionToBinary(int pos) {
	writeBinaryFromShort(pos);			/* Ecriture de la position */
}

void parseText() {
	int i = 0;
	char word[BUFFER], c;
	bool odd = false;		/* Booléen caractérisant le fait d'être dans des caractères spéciaux, ou non */

	while((c = getc(fin)) != EOF) {
		/* Caractères composant un mot*/
		if(
			(c >= 'a' && c <= 'z') ||
			(c >= 'A' && c <= 'Z') ||
			(c >= '0' && c <= '9') ||
			strchr("çñÄÂÀÁäâàáËÊÈÉéèëêÏÎÌÍïîìíÖÔÒÓöôòóÜÛÙÚüûùúµ", c) != NULL
		) {
			/* Passage d'un groupe de caractères spéciaux à un groupe de caractères pour un mot*/
			if(odd && i > 0) {
				word[i] = '\0';
				compress(word);

				i = 0;		/* Réinitialisation du mot */
			}
			word[i] = c;
			odd = false;
		} else {
			/* Passage d'un groupe de caractères pour un mot à un groupe de caractères de caractère spéciaux*/
			if(!odd && i > 0) {
				word[i] = '\0';
				compress(word);

				i = 0;		/* Réinitialisation du mot */
			}

			word[i] = c;
			odd = true;
		}

		i++;
	}

	if(odd && i > 0) {
		word[i] = '\0';
		compress(word);
	} else if(!odd && i > 0) {
		word[i] = '\0';
		compress(word);
	}
}

void parseBinary() {
	int pos, size;
	char word[BUFFER];

	while(1) {
		pos = readShortFromBinary();	/* Récupération de la position */

		if(pos == -1) { return;	}

		/* Nouveau mot */
		if(pos == 0) {
			size = readCharFromBinary();
			if(size == -1) { return; }

			readTextFromBinary(word, size);
			word[size] = '\0';
			uncompressNewWord(size, word); /* Nouveau mot*/
		} else {
			uncompressExistingWord(pos); /* Mot connus */
		}
	}

}