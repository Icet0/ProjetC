#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Gestion_fichier.h"


//OUVERTURE D'UN FICHIER BIT A BIT


Bin_file* ouverture_fichier_bit(char* nom_de_fichier, char mode) {

	//Variable locale : fichier(pointeur sur Bin_file)
	Bin_file* fichier;
	fichier = (Bin_file*)malloc(sizeof(Bin_file));
	fichier->mode = mode;
	//Si accès en lecture
	//Ouverture du fichier input en lecture
	if (fichier->mode = 'r') {
		fichier->file = fopen(nom_de_fichier, "input");
	}
	else if(fichier->mode = 'w'){
		fichier->file = fopen(nom_de_fichier, "input");
	}
	fichier->record_length = 0;
	fichier->i_record = 0;
	fichier->i_octet = 0;
	fichier->nb_octets = 0;
	return fichier;
}