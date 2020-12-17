#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Tests.h";
#include "Gestion_fichier.h"
#include "Huffman.h"

void function_test_all() {
	printf("Debut des tests :\n\n\nWaiting . . .\n\n\n");
	printf("TEST_GESTION_FICHIER : \n");
	//TEST_GESTION_FICHIER();//A compléter
	printf("TEST_HUFFMAN : \n");
	TEST_HUFFMAN();
}