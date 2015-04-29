#include <stdio.h>
#include <string.h>

#include "Compression.h"
#include "File.h"
#include "Utils.h"


int main(int argc, char* argv[]) {
	bool compress = false;

	/* Arguments invalide */
	if(argc != 4) {
		getHelp();
		return 1;
	}

	/* Vérification des paramètres */
	if(strcmp(argv[1], "-c") == 0) {
		compress = true;
	} else if (strcmp(argv[1], "-d") == 0) {
		compress = false;
	} else {
		getHelp();
		return 1;
	}

	/* Initialisation */
	if(!open(argv[2], argv[3])) {
		return 1;²
	}
	initList();

	/* Compression ou décompression */
	if(compress) {
		printf("Compress is running ...\n");
		parseText();
		printf("SUCCESS\n");
	} else {
		printf("Uncompress is running ...\n");
		parseBinary();
		printf("SUCCESS\n");
	}

	/* Libération des fichiers */
	freeDictionnary();		/* Libération du dictionnaire */
	close();				/* Fermeture de l'entrée et de la sortie */

	return 0;
}