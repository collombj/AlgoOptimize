/**
 * 	@file Compression.h
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

#ifndef _COMPRESSION_
#define _COMPRESSION_

#include "Utils.h"

/**
 * @brief Structure représentant une celulle de liste, doublement chainée.
 * 
 * @details La structure représente une cellule doublement chainée. Celle-ci stocke un mot.
 */
typedef struct cel {
	char* word;					/**< Mot */
	struct cel* next;			/**< Cellule suivante */
	struct cel* prev;			/**< Cellule précédente */
} Cel;

/**
 * @brief Structure représentant le début de la liste chainée.
 * 
 * @details La liste représente le dictionnaire utilisé pour la compression. Par conséquent, celui-ci contient tous les mots compressés. La liste peut donc être très lourde en mémoire.
 */
typedef Cel* List;

/**
 * @brief Fonction initialisant la liste.
 * 
 * @details La fonction initialise la variable static de stockage de la liste de mot.
 * 
 * @warning Cette fonction doit être appelé avant toutes manipulations de la liste (l'intégrité des données pourraient être atteinte en cas de non respect de cette avertissement).
 */
void initList();

/**
 * @brief Fonction permettant d'allouer de la mémoie pour une cellule.
 * 
 * @details La fonction alloue de la mémoire à la cellule, et stocke le mot (word) dans celle-ci.
 * 
 * @param word Le mot devant être stocké dans la cellule
 * 
 * @return Retourne le pointeur sur la cellule allouée en mémoire.
 */
Cel* createCel(char* word);

/**
 * @brief Fonction compressant un mot
 * 
 * @details La fonction prend en charge la compression d'un  mot.
 * 			
 * 			Algorithme :
 * 			Pour chaque mot du texte (mot ou ponctuation)
 *				– Rechercher le mot dans la liste.
 *				– Si le mot existe dans la liste, on le code à l’aide de sa position dans la liste, puis on le déplace en tête de liste.
 *				– Si le mot n’est pas dans la liste, on le code par l’entier 0 suivi du mot en clair, et on ajoute ce mot en fin de liste.
 *				
 *			Format :
 *				- position -- si le mot existe déjà
 *				- position tailleDuMot mot -- si le mot n'existe pas encore
 * 
 * @param word Le mot a compresser
 * 
 * @return True si la compression est un succès, false sinon.
 */
bool compress(char* word);

/**
 * @brief Fonction permettant le déplacement d'une celulle en tête de liste
 * 
 * @details La fonction déplace la celulle (move), présente dans la liste, en tête de la liste static.
 * 
 * @param move C'est la cellule à déplacer en début de liste.
 */
void moveToBeginning(Cel* move);

/**
 * @brief Fonction permettant de libérer la liste de la mémoire.
 * 
 * @details La fonction libère chaque cellulle, ainsi que le contenu de celle-ci, pour libérer la mémoire proprement.
 */
void freeDictionnary();


#endif