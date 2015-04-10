#ifndef _COMPRESSION_
#define _COMPRESSION_

#include "Utils.h"

#define FILE_BUFFER 2048

typedef struct cel {
	char* word;					/**< Mot */
	struct cel* next;			/**< Cellule suivante */
	struct cel* prev;			/**< Cellule précédente */
} Cel;

typedef Cel* List;

typedef struct dictionary {
	List l;						/**< Liste de mot */
	char out[FILE_BUFFER];		/**< Texte de sortie -- Bufferisé */
	int size;					/**< Taille du texte en buffer */
} Dictionary;


void initDictionary();
Cel* createCel(char* word);
bool addWord(char* word);
void moveToBeginning(Cel* move);
void compress(char* txt);
void freeDictionnary();

void addWordToOutput(char* word);
char* getOutput();


#endif