/**
 * 	@file File.h
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
 * 			 	- readTextFromBinary(char*, int) 			-- Pour lire (du binaire -- fichier d'entrée) un texte de longueur définis.
 * 			 	
 * 			 - convertNewWordToBinary(int, char*)  -- Pour écrire un nouveau mot (compressé) dans le fichier.
 * 			 - convertPositionToBinary() 		   -- Pour écrire la position d'un mot déjà compressé.
 * 			 
 * 			 - parseText() -- Pour parser et compresser le fichier en entrée vers le fichier en sortie.
 * 			 - parseBinary -- Pour parser et décompresser le fichier en entrée vers  le fichier en sortie.
 */

#ifndef _FILE_
#define _FILE_

#include "Utils.h"

/**
 * @brief Taille du buffer de mot (maximum possible 255)
 */
#define BUFFER 129

/**
 * @brief Fonction permettant d'ouvrir les fichiers d'entrée/sortie.
 * 
 * @details La fonction ouvre les fichiers pour l'entrée et la sortie.
 * 
 * @warning Le fichier d'entrée (input) doit existé. Le fichier de sortie (output) est totalement réécris.
 * 
 * @param input Le fichier (ouvert en lecture) contenant la source (compressée ou non).
 * @param output Le fichier (ouvert en écriture) de destination de la décompression ou de la compression.
 * 
 * @return Si aucun problème ne survient, la fonction retourne true, false sinon.
 */
bool open(char* input, char* output);

/**
 * @brief Fonction liberrant les fichiers d'entrée et de sortie de la compression/décompression.
 * 
 * @details la fonction libère les fichiers d'entrée/sortie.
 */
void close();

/**
 * @brief Fonction écrivant (en binaire) le contenu de deux octets (short).
 * 
 * @details La fonction écrit (en binaire), dans le fichier de sortie, le contenu du paramètre (seulement les deux premiers octets).
 * 
 * @param nb Les deux premiers octets à écrire dans le fichier de sortie.
 */
void writeBinaryFromShort(short nb);

/**
 * @brief Fonction écrivant (en binaire) le contenu d'un octet (char).
 * 
 * @details La fonction écrit (en binaire), dans le fichier de sortie, le contenu du paramètre (seulement le premier octet).
 * 
 * @param c Le première octet à écrire dans le fichier de sortie.
 */
void writeBinaryFromChar(char c);

/**
 * @brief Fonction écrivant (en binaire) le texte (de longeur length) dans le fichier de sortie.
 * 
 * @details La fonction écrit (en binaire), dans le fichier de sortie, le texte de longueur length.
 * 
 * @param txt Texte à écrire dans le fichier de sortie
 * @param length Taille du texte à écrire
 */
void writeBinaryFromText(char* txt, int length);

/**
 * @brief Fonction lisant, dans le fichier d'entrée, du binaire (deux octets) et le convertissant en short.
 * 
 * @details La fonction lit, dans le fichier d'entrée, le binaire (deux octets) et le convertit en short.
 * 
 * @return Short représentant les deux octets lus dans le fichier d'entrée.
 */
short readShortFromBinary();

/**
 * @brief Fonction lisant, dans le fichier d'entrée, du binaire (un octet) et le convertissant en char.
 * 
 * @details La fonction lit, dans le fichier d'entrée, le binaire (un octet) et le convertit en char.
 * 
 * @return Char représentant l'octet lu dans le fichier d'entrée.
 */
char readCharFromBinary();

/**
 * @brief Fonction lisant un texte, dans le fichier d'entrée, codé en binaire et le convertissant en texte ASCII.
 * 
 * @details La fonction lit length octets (en binaire) pour créer un texte ASCII. Ce texte est stocké directement dans le paramètre txt.
 * 
 * @warning La fonction modifie le paramètre txt.
 * 
 * @param txt C'est la variable qui hébergera le texte lu par la fonction
 * @param length C'est la longeur du texte que doit lire la fonction (nombre d'octets = nombre de caractères).
 */
void readTextFromBinary(char* txt, int length);

/**
 * @brief Fonction permettant de saisir automatiquement du texte (en binaire) dans le fichier de sortie.
 * 
 * @details La fonction écrit le formatage d'un nouveau mot, en binaire, dans le fichier de sortie.
 * 			La fonction formatte automatiquement le texte de la manière suivante :
 * 				- 0    size  word     -- Formatage mais sans les espaces
 * 				- char short text     -- Représentation du type encodée en binaire
 * 				- 1    2     1*size	  -- Taille, en octet utilisé par le codage
 * 
 * @param size La taille du mot qui va être écrit en binaire
 * @param word Le mot qui va être écrit en binaire
 */
void convertNewWordToBinary(int size, char* word);

/**
 * @brief Fonction permettant de saisir automatiquement le texte associé à un mot existant déjà en mémoire.
 * 
 * @details La fonction écit la position du mot (déjà présent en mémoire) dans le fichier de sortie. La position est codée sur un short (2 octets).
 * 
 * @param pos La position du mot déjà présent en mémoire.
 */
void convertPositionToBinary(int pos);

/**
 * @brief Fonction parsant et compressant le fichier en entrée vers le fichier en sortie.
 * 
 * @details la fonction parse et compresse le contenu du fichier en entrée vers le fichier de sortie. Le parsage est réalisé en séparant les mots et les caractères spéciaux.
 */
void parseText();

/**
 * @brief Fonction parsant et décompressant le fichier en entrée vers le fichier en sortie.
 * 
 * @details la fonction parse et décompresse le contenu du fichier en entrée vers le fichier de sortie. Le parsage est réalisé en séparant les mots et les caractères spéciaux.
 */
void parseBinary();
#endif