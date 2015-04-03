#ifndef _COMPRESSION_
#define _COMPRESSION_

#include "Utils.h"

typedef struct cel {
	char* word;
	struct cel* next;
	struct cel* prev;
} Cel;

typedef Cel* List;

typedef struct dictionary {
	List l;
	char* out;
} Dictionary;


Dictionary* newDictionary();
Cel* createCel(char* word);
bool addWord(Dictionary* d, char* word);


#endif