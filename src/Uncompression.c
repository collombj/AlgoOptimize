#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Compression.h"
#include "Utils.h"
#include "Compression.h"

#define TAILLE 129


/*==================================== Lecture ====================================*/
int read(FILE *entree, Dictionary *dic){
  char mot[TAILLE];
  int res;

  if(entree == NULL)
    return 0;

  while(fscanf(entree, "%s \n", mot) != NULL)
  {
    fscanf(entree, "%s \n", mot);

    res = insereren(dic, mot);

    if(res == 0)
      return 0;
  }

  fclose(entree);
  return 1;
}

/*==================================== Ecriture ====================================*/
void saveDictionary(FILE *sortie, Dictionary dic){

  if(sortie == NULL)
    perror("Error in opening file");
  else
  {
    while( lex != NULL)
    {
      fprintf(sortie, "%s %d\n", lex->mot, lex->occurrence);
      lex = lex->suivant;
    }

    fclose(sortie);
  }
}




0 deux 0 et 1 0 quatre 3 3 2 0 huit