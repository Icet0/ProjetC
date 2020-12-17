#ifndef __HUFFMAN_H__

#include "Arbre_binaire.h"
#include "liste.h"
#include "Gestion_fichier.h"
#define __LIST_H__

#define TAILLE_MAX_CODE 1024

bool rechercher_Char(list_t* list, char c);
Item* rechercher_Item(list_t* list, char c);
list_t* calcul_freq_char(char* string);
arbre creer_Arbre_char(list_t* list);
char* table_encodage(arbre arbre);
int serialisation(arbre arbreb, char* code, char c, int i, char tmp[]);
void codage_caract(char caract, arbre arbre, Bin_file* output);
void codage(arbre arbre, Bin_file* output, char* contenu);
void decodage(arbre A, arbre arbre, Bin_file* output, Bin_file* input);
void ecriture_Dico_Header(char* dico, Bin_file* output);
char* lecture_Dico_Header(Bin_file* input);
arbre creer_Arbre_By_Dico(char* dico, int taille);
void completer_bits(Bin_file* file);
void compression(char* nameInput, char* nameOutput);
void decompression(char* nameInput, char* nameOutput);
void RUN_HUFFMAN();


#endif