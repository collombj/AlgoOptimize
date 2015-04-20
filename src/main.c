#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Compression.h"
#include "Utils.h"
#include "File.h"

int main(int argc, char *argv[]) {
	open("data/output.bin", "data/uncrypted.txt");				/* Ouverture de l'entrée et de la sortie */
	initList();			/* Initialisation de la liste de mot */


	/*parseText();*/
	parseBinary();

	freeDictionnary();		/* Libération du dictionnaire */
	close();				/* Fermeture de l'entrée et de la sortie */

	return 0;
}