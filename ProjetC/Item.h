#pragma once
#ifndef ITEM_H
#include "Arbre_binaire.h"
#define ITEM_H

struct Item_s;

typedef struct Item_s {
	arbre arbre;
	//float f; // cost, heuristic, ...
	struct Item_s* prev, * next; // needed for chained list 
} Item;

#endif 
