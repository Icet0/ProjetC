#pragma once
#ifndef __HUFFMAN_H__

#include "Arbre_binaire.h"
#include "liste.h"
#include "Gestion_fichier.h"
#define __LIST_H__

#define TAILLE_MAX_CODE 1024


//int serialisation(arbre arbreb, char* code, char c, int i);
//int serialisation(arbre arbreb, char* code, char c, int i, Bin_file* output);
int serialisation(arbre arbreb, char* code, char c, int i, Bin_file* output, char* tmp);
arbre deserialisation(char* s, int* i);
bool rechercher_Char(list_t* list, char c);
Item* rechercher_Item(list_t* list, char c);
list_t* calcul_freq_char(char* string);
arbre creer_Arbre_char(list_t* list);
void TEST_HUFFMAN();


void walk(arbre arbre, char* code);
#endif