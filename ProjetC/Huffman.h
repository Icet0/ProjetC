#pragma once
#ifndef __HUFFMAN_H__

#include "Arbre_binaire.h"
#include "liste.h"
#define __LIST_H__



//void serialisation(arbre a, char* s, int i);
arbre deserialisation(char* s, int i);

bool rechercher_Char(list_t* list, char c);
Item* rechercher_Item(list_t* list, char c);
list_t* calcul_freq_char(char* string);
arbre creer_Arbre_char(list_t* list);
void TEST_HUFFMAN();


void walk(arbre arbre, char* code);
#endif