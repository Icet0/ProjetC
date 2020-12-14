#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "Gestion_fichier.h"




void expand_byte(unsigned char x, char* octet)
{
	int i;
	for (i = 7; i >= 0; i--) {
		octet[i] = '0' + (x % 2);
		x = x >> 1;
	}
}
//===========================================================//
// //
// Ouverture d'un fichier binaire //
// //
// Valeur : //
// Structure Bin_file permettant les accès bit à bit //
// //
// Entrée : //
// filename : nom du fichier //
// mode : lecture 'r' ou écriture 'w' //
// //
//===========================================================//
Bin_file* open_bin_file(char* filename, char mode)
{
	FILE* input, * output;
	Bin_file* fichier;
	fichier = (Bin_file*)malloc(sizeof(Bin_file));
	fichier->mode = mode;
	if (mode == 'r') {
		input = fopen(filename, "rb");
		if (input == NULL) return NULL;
		fichier->file = input;
		fichier->record_length = 0;
		fichier->i_record = 0;
		fichier->i_octet = 0;
		fichier->nb_octets = 0;
	}
	else if (mode == 'w') {
		output = fopen(filename, "wb");
		if (output == NULL) return NULL;
		fichier->file = output;
		fichier->record_length = 0;
		fichier->i_record = 0;
		fichier->i_octet = 0;
		fichier->nb_octets = 0;
	}
	return fichier;
}
//=======================================================================//
// //
// Ecriture d'un bit dans un fichier //
// //
// En pratique : écriture du bit dans octet //
// lorsque octet est plein (8 bits) => copie dans tampon // 
// tampon plein => écriture dans fichier //
// Entrée : //
// output : structure associée au fichier de sortie //
// bit : bit à stocker //
// //
//=======================================================================//

void write_bin_file(Bin_file* output, char bit)
{
	unsigned char octet, b;
	int i;
	output->octet[output->i_octet++] = bit;
	if (output->i_octet == 8) {
		octet = 0;
		b = 0x80; // octet[0] -> bit de poids fort
		for (i = 0; i < 8; i++) {
			if (output->octet[i] == '1') octet = octet | b;
			b = b >> 1;
		}
		output->i_octet = 0;
		output->record[output->i_record++] = octet;
		output->nb_octets++;
		if (output->i_record == BLOCK_SIZE) {
			fwrite(output->record, 1, BLOCK_SIZE, output->file);
			output->i_record = 0;
		}
	}
}
//=============================================================//
// //
// Fermeture d'un fichier binaire // 
// Avec écriture du dernier bloc lors d'un accès en écriture //
// //
// Entrée : //
// fichier : structure associée au fichier à fermer //
// //
//=============================================================//
int close_bin_file(Bin_file* fichier)
{
	unsigned char octet, b;
	int i;
	int nb_octets;
	nb_octets = fichier->nb_octets;
	if (fichier->mode == 'w') {
		if (fichier->i_octet != 0) { // Traitement des derniers bits
			octet = 0;
			b = 0x80; // octet[0] -> bit de poids fort
			for (i = 0; i < fichier->i_octet; i++) {
				if (fichier->octet[i] == '1') octet = octet | b;
				b = b >> 1;
			}
			fichier->record[fichier->i_record++] = octet;
			nb_octets++;
		}
		if (fichier->i_record != 0) fwrite(fichier->record, 1, fichier->i_record, fichier->file);
	}
	fclose(fichier->file);
	free(fichier);
	return nb_octets;
}
char read_bin_file(Bin_file* input)
{
	char bit;
	if (input->record_length == 0) {
		input->record_length = fread(input->record, 1, BLOCK_SIZE, input->file);
		input->i_record = 0;
		expand_byte(input->record[input->i_record++], input->octet);
		input->i_octet = 0;
		input->nb_octets += input->record_length;
	}
	bit = input->octet[input->i_octet++];
	if (input->i_octet == 8) {
		expand_byte(input->record[input->i_record++], input->octet);
		input->i_octet = 0;
		if (input->i_record == BLOCK_SIZE) {
			input->record_length = fread(input->record, 1, BLOCK_SIZE, input->file);
			input->i_record = 0;
			input->nb_octets += input->record_length;
		}
	}
	return bit;
}


Bin_file* open_normal_file(char * filename,char mode) {
	FILE* input, * output;
	Bin_file* fichier;
	fichier = (Bin_file*)malloc(sizeof(Bin_file));
	fichier->mode = mode;
	if (mode == 'r') {
		input = fopen(filename, "r");
		if (input == NULL) return NULL;
		fichier->file = input;
		fichier->record_length = 0;
		fichier->i_record = 0;
		fichier->i_octet = 0;
		fichier->nb_octets = 0;
	}
	else if (mode == 'w') {
		output = fopen(filename, "w");
		if (output == NULL) return NULL;
		fichier->file = output;
		fichier->record_length = 0;
		fichier->i_record = 0;
		fichier->i_octet = 0;
		fichier->nb_octets = 0;
	}
	return fichier;
}

void close_normal_file(Bin_file* fichier) {
	if (fichier->file != NULL)
	{
		fclose(fichier->file); // On ferme le fichier qui a été ouvert
	}
}


char* lecture_normal_file(Bin_file* input) {
	char caractereActuel;
	caractereActuel = '\0';
	list_t* liste = newList();
	printf("ouverture normal file : ");
	while (caractereActuel != EOF)
	{
		caractereActuel = fgetc(input->file); // On lit le caractère
		if (caractereActuel != EOF) {
			printf("%c", caractereActuel); // On l'affiche
			Item* item = nodeAlloc();
			arbre arbre = creer_arbre(caractereActuel, NULL, NULL);
			item->arbre = arbre;
			addLast(liste, item);
		}
	}
	char* result = (char*)malloc(sizeof(char) * liste->numElements);
	//result = {};
	int i = 0;
	while (liste->first != NULL)  
	{
		result[i] = popFirst(liste)->arbre->elt;
		//printf("\nresultat[%d] : %c\n", i, result[i]);
		i++ ;
	}
	result[i] = '\0';
	return result;	
}




void TEST_GESTION_FICHIER() {
	printf("\tTest ouverture fichier : ");
	const char* nom_fichier_1 = "D:/Travail/Polytech 3A/Projet_C/ProjetC/ProjetC/test1.bin";
	const char* nom_fichier_2 = "D:/Travail/Polytech 3A/Projet_C/ProjetC/ProjetC/test1.txt";
	Bin_file* file1 = open_bin_file((char*)nom_fichier_1, 'w');
	if ( file1->file != NULL) {
		printf("_fichier ouvert correctement\n");
		close_bin_file(file1);
	}
	printf("\tTest Guillaume\n");
	Bin_file* file = open_bin_file((char*)nom_fichier_1, 'w');
	write_bin_file(file, '1');
	write_bin_file(file, '1');
	write_bin_file(file, '0');
	write_bin_file(file, '1');
	write_bin_file(file, '0');
	write_bin_file(file, '0');
	write_bin_file(file, '0');
	write_bin_file(file, '1');

	printf("writing %d byte before closing file.\n", close_bin_file(file));

	Bin_file* file2 = open_bin_file((char*)nom_fichier_1, 'r');

	for (int i = 0; i < 8; i++)
	{
		char test = read_bin_file(file2);
		printf("%c\n", test);
	}
	close_bin_file(file);
	printf("\tTest Ouverture .txt");
	Bin_file* file3 = open_normal_file((char*)nom_fichier_2, 'r');
	lecture_normal_file(file3);
	close_normal_file(file3);
	close_bin_file(file2);

	printf("\nfin test ouverture .txt\n");

}