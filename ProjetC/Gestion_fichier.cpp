#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Gestion_fichier.h"


//OUVERTURE D'UN FICHIER BIT A BIT

/*
Bin_file* ouverture_fichier_bit(const char* nom_de_fichier, char mode) {

	//Variable locale : fichier(pointeur sur Bin_file)
	Bin_file* fichier;
	fichier = (Bin_file*)malloc(sizeof(Bin_file));
	fichier->mode = mode;
	//Si accès en lecture
	//Ouverture du fichier input en lecture
	if (fichier->mode == 'r') {
		fichier->file = fopen(nom_de_fichier, "rb");
	}
	else if(fichier->mode == 'w'){
		fichier->file = fopen(nom_de_fichier, "wb");
	}

	if (fichier->file != NULL) {
		fichier->record_length = 0;
		fichier->i_record = 0;
		fichier->i_octet = 0;
		fichier->nb_octets = 0;
	}
	else {
		printf("Probleme lors de l'ouverture du fichier %s\n\n", nom_de_fichier);
	}
	return fichier;
}
	
void ecriture_fichier_bit(Bin_file* output, char bit) {
	if (output != NULL) {
		unsigned char octet, b;// variables locales
		int i;
		output->octet[output->i_octet++] = bit; // stockage du bit
		if (output->i_octet == 8) {
			// octet " plein "
			octet = 0;
			b = 0x80; // octet[0] -> bit de poids fort
			for (int i = 0; i <= 7; i++) {// Pour transférer les 8 bits
				if (output->octet[i] == '1') {
					octet = octet | b; // OU binaire
				}
				b = b >> 1; // Décalage d’un bit à droite
			}
			output->i_octet = 0;
			output->record[output->i_record] = octet;
			output->i_record = output->i_record + 1;
			output->nb_octets = output->nb_octets + 1;
			if (output->i_record == BLOCK_SIZE) {
				//Ecriture de output->record dans output->file
				fprintf(output->file, "%d", output->record[output->i_record]);//%d ou %p ???
				output->i_record = 0;
			}
		}
	}
}


char lecture_fichier_bit(Bin_file* input) {
	
	char bit;
	if (input != NULL) {
		if (input->record_length = 0) {
			//Lecture depuis input->file dans input->record
			fread(input->record,BLOCK_SIZE,BLOCK_SIZE,input->file);
			//
			input->record_length = (sizeof(input->record)/sizeof(char));
			input->i_record = 0;
			//Transfert des 8 bits de input->record[input->i_record] dans input->octet
			for (int i = 0; i < 8; i++)
			{
				if (input->i_record+i < BLOCK_SIZE) {// mettre <= si il nous manque le dernier bit
					input->octet[i] = input->record[input->i_record + i];
				}
			}
			//
			input->i_record = input->i_record + 1;
			input->i_octet = 0;
			input->nb_octets = input->nb_octets + input->record_length;
		}
		bit = input->octet[input->i_octet];
		input->i_octet = input->i_octet + 1;
		if (input->i_octet == 8) {

			//Transfert des 8 bits de input->record[input->i_record] dans input->octet
			for (int i = 0; i < 8; i++)
			{
				if (input->i_record + i < BLOCK_SIZE) {// mettre <= si il nous manque le dernier bit
					input->octet[i] = input->record[input->i_record + i];
				}
			}
			//
			input->i_record = input->i_record + 1;
			input->i_octet = 0;
			if (input->i_record == BLOCK_SIZE) {
				input->record_length = 0;
			}
		}
	}
	return bit;
}


int fermeture_fichier_bit(Bin_file* fichier) {
	int nb_octets = fichier->nb_octets;
	unsigned char octet, b;
	if (fichier->mode == 'r') {
		if (fichier->i_octet != 0) { // Traitement derniers bits
			octet = 0;
			b = 0x80;
			for (int i = 0; i <= fichier->i_octet - 1; i++) {

				if (fichier->octet[i] == '1') {
					octet = octet | b;
				}
				b = b >> 1;
			}
		
			fichier->record[fichier->i_record++] = octet;
			fichier->i_record = fichier->i_record + 1;
			nb_octets = nb_octets + 1;
		}
		if (fichier->i_record != 0) {
			//Ecriture de fichier->record dans fichier->file
			for (int i = 0; i <= fichier->i_record; i++)
			{
				ecriture_fichier_bit(fichier, fichier->record[i]);// ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? ? 
			}

		}
	}
	fclose(fichier->file);
	free(fichier);
	return nb_octets;
}
*/

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

void TEST_GESTION_FICHIER() {
	printf("\tTest ouverture fichier : ");
	const char* nom_fichier_1 = "D:/Travail/Polytech 3A/Projet_C/ProjetC/ProjetC/test1.txt";
	const char* nom_fichier_2 = "test2.txt";
	if (open_bin_file((char*)nom_fichier_1,'w')->file != NULL)printf("_fichier ouvert correctement\n");
	printf("\tTest Guillaume\n");
	Bin_file* file = open_bin_file((char*)nom_fichier_1, 'w');
	write_bin_file(file, '1');
	write_bin_file(file, '0');
	write_bin_file(file, '0');
	write_bin_file(file, '0');
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

}