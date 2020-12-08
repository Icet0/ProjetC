#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "list.h"

/*Item Functions*/

Item *nodeAlloc()
{
  Item *node;

  node = (Item *) malloc( sizeof(Item) );
  assert(node);

  node->parent = NULL;
  node->prev = NULL;
  node->next = NULL;
  node->f = node->g = node->h = (double)0.0;

  return node;
}

void freeItem( Item *node )
{
  if (node && node->board) free(node->board);
	if (node) free(node);
}


void initList( list_t *list_p )
{
  //if (list_p == NULL) list_p = malloc(sizeof(list_t));
	assert(list_p);

  list_p->numElements = 0;
  list_p->first = NULL;
  list_p->last = NULL;
}

int listCount( list_t *list )
{
	return list->numElements;
}

// return an item with corresponding board , or null
Item* onList( list_t *list, char *board)
{
    int count = list->numElements;
    if(count == 0){
        return NULL;
    }
    Item *current = list->first;
    while(count>0){
        if(strcmp(current->board,board) == 0){
            printf("Trouve!\n");
            return current;
        }
        else{
            current = current->next;
            count--;
        }
    }
     printf("NON Trouve!\n");
    return NULL;
}

// return and remove first item
Item *popFirst( list_t *list ) //
{
    Item *item = NULL;
    if(list->numElements>0){
        item = list->first;
        list->first = item->next;
        list->numElements--;
    }
    if(list->numElements==0){
        list->first = NULL;
        list->last = NULL;
    }
	//list_t->first->prev = NULL;
	return item;
}

// return and remove last item//
Item *popLast( list_t *list )
{
    Item *item = NULL;
    if(list->numElements>0){
        item  = list->last;
        list->last = item->prev;
        list->last->next = NULL;
        list->numElements--;
    }
    if(list->numElements==0){
        list->first = NULL;
        list->last = NULL;
    }
    return item;
}

// remove a node from list
Item * delList( list_t *list, Item *node) {

    if(list->numElements ==0){
        return NULL;
    }

    if(node == list->first){
        list->first = list->first->next;
    }
    if(node == list->last){
         list->last = list->last->prev;
    }
    Item *temp1, *temp2 ;
    temp1  = node->prev ;
    temp2 = node->next ;
    temp1->next = temp2 ;
    temp2->prev = temp1 ;
    list->numElements--;
    if(list->numElements == 0){
        list->first = NULL;
        list->last = NULL;
    }
    return node;
}

// return and remove best item with minimal f value
Item *popBest( list_t *list ) // and remove the best board from the list.
{
    if(list->numElements ==0){
        return NULL;
    }
    int count = list->numElements;
    Item *current = list->first;
    Item * best = current;
    while(count>0){
        if(current->f < best->f){
            best = current;
            current = current->next;
            count--;
        }
        else{
            current = current->next;
            count--;
        }
    }
    delList(list,best);
    return best;
}

 // add item in top
void addFirst( list_t *list, Item *node ) // add in head
{
    if (list->first == NULL){
        list->first = node ;
        list->last = node ;
    }
    else{
        Item * suiv = list->first;
        node->next = suiv ;
        suiv->prev = node;
        list->first = node ;
    }
    list->numElements++;
}

 // add item in queue
void addLast( list_t *list, Item *node ) // add in tail
{
    if (list->first == NULL){
        list->first = node ;
        list->last = node ;
    }
    else{
        Item * prev = list->last;
        node->prev = prev ;
        prev->next = node;
        list->last = node ;
    }
    list->numElements++;
}

void cleanupList( list_t *list )
{
    while(list->numElements>0){
      freeItem(popFirst(list));
    }
}

void printList( list_t list ) {
	Item *item = list.first;
  while (item) {
    printf("%.2f [%s] - ", item->f, item->board);
    item = item->next;
  }
  printf(" (nb_items: %d)\n", list.numElements);
}



// TEST LIST
/*
int main()
{
  Item *item;
	char str[3];

	list_t openList;

	initList( &openList );
	for (int i=0; i<10; i++) {
		item = nodeAlloc();
		item->f = i;
		sprintf(str, "%2d", i);
		item->board = strdup(str);
		addLast( &openList, item );
	}
    printList(openList);
	for (int i=20; i<25; i++) {
    item = nodeAlloc();
    item->f = i;
    sprintf(str, "%2d", i);
    item->board = strdup(str);
    addFirst( &openList, item );
  }
	printList(openList);
	printf("\n");

	Item *node = popBest( &openList );
	printf("best node = %.2f\n", node->f);
	printList(openList);
	printf("\n");

	strcpy(str, "23");
	node = onList(&openList, str);
	if (node) printf("found %s: %.2f!\n", str, node->f);
	printList(openList);
	printf("\n");

	node = popFirst(&openList);

		item = nodeAlloc();
    item->f = 50;
    sprintf(str, "50");
    item->board = strdup(str);
    addLast( &openList, item );

	node = popFirst(&openList);
	if (node) printf("first: %.2f\n", node->f);
	printList(openList);
  printf("\n");

	node = popLast(&openList);
	if (node) printf("last: %.2f\n", node->f);
	printList(openList);
  printf("\n");

	printf("clean\n");
	cleanupList(&openList);
	printList(openList);
	printf("\n");

	return 0;
}
*/
