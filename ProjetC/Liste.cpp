
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "Liste.h"
#define MAX_BOARD 36
/* Item Functions */

Item* nodeAlloc()
{
	Item* node;

	node = (Item*)malloc(sizeof(Item));
	assert(node);
	node->arbre = NULL;
	node->prev = NULL;
	node->next = NULL;
	//node->f = 0;

	return node;
}

void freeItem(Item* node)
{
	if (node) free(node);
}

list_t* newList() {
	list_t* list;
	list = (list_t*)malloc(sizeof(list_t));
	assert(list);
	initList(list);
	return list;
}

void initList(list_t* list_p)
{
	//if (list_p == NULL) list_p = (list_t*)malloc(sizeof(list_t));
	assert(list_p);

	list_p->numElements = 0;
	list_p->first = NULL;
	list_p->last = NULL;
}

int listCount(list_t* list)
{
	return list->numElements;
}

// return an item with corresponding char in arbre , or null
Item* onList(list_t* list, char caract)
{	
	if (list != NULL) {
		Item* item = list->first;
		int i;
		while (item != NULL) {
			i = 0;
			if (item->arbre->elt == caract) {
				return item;
			}

			item = item->next;
		}
	}
	return NULL;
}

// return and remove first item
Item* popFirst(list_t* list) //made by me
{
	if (list != NULL && list->first != NULL) {
		Item* resultat = list->first;

		if ((list->last) == resultat) { //On oublie pas de traiter le cas ou il y à qu'un seul elem dans la list
			list->last = NULL;
		}

		list->first->prev = NULL;
		list->first = list->first->next;
		if (list->first != NULL) {
			list->first->prev = NULL;
		}
		resultat->next = NULL;
		list->numElements--;
		return resultat;
	}
	return NULL;
}

// return and remove last item
Item* popLast(list_t* list) //made by me
{
	if (list != NULL && list->last != NULL) {
		Item* resultat = list->last;
		if (list->first == resultat) {//On oublie pas de traiter le cas ou il y à qu'un seul elem dans la list
			list->first == NULL;
		}
		list->last->next = NULL;
		list->last = list->last->prev;
		if (list->last != NULL) {
			list->last->next = NULL;
		}
		resultat->prev = NULL;
		list->numElements--;
		return resultat;
	}
	return NULL;
}

// remove a node from list
void delList(list_t* list, Item* node) {//made by me
	if (list != NULL && node != NULL) {
		if (list->first == node) {//cas ou le node est au début
			Item* resultat = list->first;
			list->first = list->first->next;
			freeItem(resultat);
			list->numElements--;
		}
		Item* tmp = list->first->next;
		bool flag = false;
		while (tmp != NULL && !flag)
		{
			if (tmp == node) {
				Item* prec = tmp->prev;
				Item* suiv = tmp->next;
				//on raccorde la liste
				prec->next = suiv;
				suiv->prev = prec;
				freeItem(tmp);
				list->numElements--;
				flag = true;
			}
			if (!flag) {
				tmp = tmp->next;
			}
		}
	}
}

// return and remove best item with minimal f value
							//made by me
Item* popBest(list_t* list) // and remove the best board from the list.
{
	if (list != NULL) {
		float best_f = list->first->arbre->frequence;
		Item* resultat = list->first;
		Item* tmp = list->first->next;
		while (tmp != NULL)
		{
			if (tmp->arbre->frequence < best_f) {
				best_f = tmp->arbre->frequence;
				resultat = tmp;
			}
			tmp = tmp->next;
		}
		Item* prec = resultat->prev;
		Item* suiv = resultat->next;
		//on raccorde la liste
		if(prec!=NULL)prec->next = suiv;
		if (suiv != NULL)suiv->prev = prec;
		//ne pas oublier les cas du premier ou dernier elem
		if (list->first == resultat)list->first = suiv;
		if (list->last == resultat)list->last = prec;
		resultat->prev = NULL;
		resultat->prev = NULL;
		list->numElements--;
		return (resultat);
	}
	return NULL;
}

// add item in top
void addFirst(list_t* list, Item* node) // add in head
{
	if (list->first != NULL && node != NULL) {
		Item* suiv = list->first;
		node->next = suiv;
		suiv->prev = node;
		list->first = node;
		list->numElements++;
	}
	else {
		list->first = node;
		list->last = node;
		list->numElements++;
	}
}

// add item in queue
void addLast(list_t* list, Item* node) // add in tail
{
	if (list->last != NULL && node != NULL) {
		Item* prec = list->last;
		node->prev = prec;
		prec->next = node;
		list->last = node;
		list->numElements++;
	}
	else {
		list->last = node;
		list->first = node;
		list->numElements++;
	}
}

void cleanupList(list_t* list)
{
	if (list != NULL) {
		list->last = NULL;
		Item* tmp = list->first;
		if (tmp != NULL) {
			if (list->first->next != NULL) {
				list->first = list->first->next;
				cleanupList(list);
			}
			else {
				//list->numElements--;
				freeItem(tmp->next);
			}

			list->first = NULL;
			list->numElements--;
			freeItem(tmp);
		}
	}
}

void printList(list_t list) {
	Item* item = list.first;
	while (item) {
		if (item->arbre->elt == '\0'){
			printf("\n\t\t%d pour le char : %c (caractere de fin)", item->arbre->frequence, item->arbre->elt);
		}
		else {
			printf("\n\t\t%d pour le char : %c", item->arbre->frequence, item->arbre->elt);
		}
		item = item->next;
	}
	printf("\n\t\t(nb_items: %d)\n", list.numElements);
}
