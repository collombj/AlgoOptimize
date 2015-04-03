#ifndef _COMPRESSION_
#define _COMPRESSION_

typedef struct cel {
	char* word;
	struct cel* next;
	struct cel* prev;
} Cel;

typedef Cel* List;

typedef struct dictionary {
	List* l;
	char* out
} Dictionary;



Cel* createCel(char* word);


#endif