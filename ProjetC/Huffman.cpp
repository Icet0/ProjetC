#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "Huffman.h"

long taille_fichier = 0;
long taille_fichier_bin = 0;
long taille_code = 0;



bool rechercher_Char(list_t* list, char c) {// permet la recherche d'un char dans la liste
    if (onList(list,c) != NULL) {
        return true;
    }
    return false;
}

Item* rechercher_Item(list_t* list,char c) {// permet la recherche d'un char dans la liste et le retourne
    return onList(list,c);
}

list_t* calcul_freq_char(char* string) {
    list_t* list = newList();
    for (int i = 0; i < strlen(string); i++)
    {
        if (rechercher_Char(list, string[i]) == false) {
            arbre ab = creer_arbre(string[i], NULL, NULL);
            Item* item = nodeAlloc();
            item->arbre = ab;
            addFirst(list, item);//On ajoute a la pile notre item (arbre->contenant le char et la freq)
        }
        else {
            Item* tmp = rechercher_Item(list, string[i]);
            tmp->arbre->frequence++;//On augment la fréquence de 1
        }
    }
    //On ajoute le caractère de FIN \0
    Item* it = nodeAlloc();
    arbre ab_tmp = creer_arbre('\0', NULL, NULL);
    it->arbre = ab_tmp;
    addFirst(list, it);
    return list;
}

arbre creer_Arbre_char(list_t* list) {

    //Tant que l'on a plus d'un noeud/element ou de deux dans le tableau
    while (list->numElements > 1)
        //récupérer les noeuds minimals du tableau et les ajouter dans un nouveau noeud que l'on met dans la liste
    {
        Item* aux0 = popBest(list);
        Item* aux1 = popBest(list);
        arbre fg = aux0->arbre;
        arbre fd = aux1->arbre;
        arbre ar = creer_arbre(NULL, fg, fd);
        ar->frequence = ar->fils_gauche->frequence + ar->fils_droit->frequence;
        Item* item = nodeAlloc();
        item->arbre = ar;
        addFirst(list, item);//On rajoute le nouvel arbre à notre liste
    }
    return list->first->arbre;//On return ce qui doit normalement être notre dernier élt présent dans notre liste et qui contient tout notre arbre
}






char* table_encodage(arbre arbre)
{
    char code[TAILLE_MAX_CODE] = {};
	char resultat[TAILLE_MAX_CODE] = {};
    serialisation(arbre, code,'0',0, resultat);
    printf("fin table encodage");
	return resultat;
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MES MODIFS


//Cette fonction permet d'ecrire le code dans les feuilles de l'arbre et stock l'arbre encodé dans tmp[]
int serialisation(arbre arbreb, char* code, char c, int i, char tmp[]) {
	
	if (est_arbre_vide(arbreb)) {
		/*  */
		return i;
	}
	else {
		char tmp3[100] = {};

		char tmp1[100] = {};
		char tmp2[100] = {};
		code[i] = c;
		strcpy(tmp1, code);
		strcpy(tmp2, code);
		i++;
		char* tmp4 = (char*)malloc(sizeof(char) * strlen(code));
		char* tmp5 = (char*)malloc(sizeof(char) * strlen(code)-1);//code final
		strcpy(tmp4, code);
		//On enlève le premier 0
		for (int k = 0; k < strlen(tmp4); k++)
		{
			tmp5[k] = tmp4[k+1];
		}
		arbreb->code = tmp5;//MARCHE, on enlève bien le 0
		arbreb->code[i] = '\0';
		//fprintf(output->file, "Code de %c :", arbreb->elt);
		if (est_feuille(arbreb)) {
			tmp3[0] = '0'; tmp3[1] = '0'; tmp3[2] = '0';

			int j = 3;
			int cpt = 0;
			int indice = 0;
			printf("Code de %c :", arbreb->elt);
			if (arbreb->elt == '\0') {
				tmp3[j] = 'n';
				tmp3[j + 1] = 'u';
				tmp3[j + 2] = 'l';
				tmp3[j + 3] = 'l';
				indice = 4;
			}
			else {
				tmp3[j] = arbreb->elt;
				indice = 1;
			}
			for (j; j-2 < i; j = j + 1)
			{
				//write_bin_file(output, arbreb->code[j]);
				printf("%c", arbreb->code[j-3]);
				tmp3[j+indice] = arbreb->code[j-3];
				cpt++;
			}
			
			char c_tmp[3];/* c_tmp[0] = '0'; c_tmp[1] = '0'; c_tmp[2] = '0';*/
			
			sprintf(c_tmp,"%d",cpt);

			switch (strlen(c_tmp))
			{
			case 1:
				tmp3[0] = '0'; tmp3[1] = '0'; tmp3[2] = c_tmp[0];
				break;
			case 2:
				tmp3[0] = '0'; tmp3[1] = c_tmp[0]; tmp3[2] = c_tmp[1];

				break;
			case 3:
				tmp3[0] = c_tmp[0]; tmp3[1] = c_tmp[1]; tmp3[2] = c_tmp[2];
				break;
			default:
				printf("\n\n\n\n\n\t\t\t\t\tERROR\n\n\n\n\n\n\n\n");
				break;
			}

			strcat(tmp, tmp3);

			printf("\n");
		}
		serialisation(fils_gauche(arbreb), tmp1, '0', i,tmp);
		serialisation(fils_droit(arbreb), tmp2, '1', i,tmp);

	}
	return i;
}




//on passe du caractère au bit
void codage_caract(char caract, arbre arbre, Bin_file* output) {

	if (!est_arbre_vide(arbre)) {

		if (arbre->elt == caract && est_feuille(arbre)) {
			for (int j = 0; j < strlen(arbre->code); j = j + 1)
			{
				if (output == NULL) {
					printf("%c", arbre->code[j]);
				}
				else {
					write_bin_file(output, arbre->code[j]);
				}
			}
		}
		codage_caract(caract, fils_gauche(arbre), output);
		codage_caract(caract, fils_droit(arbre), output);
	}
}

void codage(arbre arbre, Bin_file* output, char* contenu) {
	if (!est_arbre_vide(arbre) && output != NULL && contenu != NULL) {
		for (int i = 0; i < strlen(contenu)+1; i++)
		{
			codage_caract(contenu[i], arbre, output);
		}
	}
	printf("\n\nTaille fichier avant compression : %d\n\n", strlen(contenu)+1);
	taille_fichier = strlen(contenu);
	// p e rajouter ici le rajout des bits
}


//NE MARCHE PAS EN RECURSIF

//décodage codebinaire to string
//void decodage(arbre A, arbre arbre, Bin_file* output,Bin_file* input,int count) {//output = fichier de destination
//	if (input != NULL /*&& output != NULL*/) {
//		//printf("\nOn se trouve a la position : %ld\n",ftell(input->file));
//		char bit = read_bin_file(input);
//		if (bit != EOF) {
//			if (!est_arbre_vide(arbre) && bit != NULL) {
//				if (est_feuille(arbre)) {
//					//ecrire dans le fichier
//					//printf("%c", arbre->elt);
//					fputc(arbre->elt, output->file);	
//
//					if (arbre->elt == '\0') {
//						//printf("caractere de FIN");
//						return;
//					}
//					arbre = A;//restet de l'arbre
//				}
//
//				printf("%d\n", count);
//				//printf("\nRead bin = %c", bit);
//				if (bit == '0') {
//					decodage(A, fils_gauche(arbre), output, input, count + 1);
//				}
//				if (bit == '1') {
//					decodage(A, fils_droit(arbre), output, input, count + 1);
//				}
//			}
//		}
//		else {
//			return;
//		}
//	}
//}

void decodage(arbre A, arbre arbre, Bin_file* output, Bin_file* input) {
	if (input != NULL /*&& output != NULL*/) {
		taille_fichier = 0;
		char bit = '0';
		bool flag = false;
		while ((!est_arbre_vide(arbre) && !flag)) {
			bit = read_bin_file(input);
			if (bit == EOF)return;
			if (est_feuille(arbre)) {
				//printf("%c", arbre->elt);
				fputc(arbre->elt, output->file);
				taille_fichier++;
				if (arbre->elt == '\0') {
					flag = true;
				}
				arbre = A;//On repart à la racine
			}
			if (bit == '0') {
				arbre = arbre->fils_gauche;
			}
			else if (bit == '1') {
				arbre = arbre->fils_droit;
			}
		}
		taille_fichier_bin = input->nb_octets;
	}
}




void ecriture_Dico_Header(char* dico, Bin_file* output) {
	if (output != NULL && dico != NULL) {
		int i = 0;
		int len = strlen(dico);
		char* tmp = (char*)malloc(sizeof(char) * len);
		strcpy(tmp,dico);
		for (i = 0; i < len ; i++)
		{
			char c = tmp[i];
			//printf("\non ecrit %c\n", c);
			fputc(c, output->file);
		}
		fputc('\0', output->file);

		printf("\n\nOn ecrit le dico : %d caracteres\n\n", i );
	}
}

char* lecture_Dico_Header(Bin_file* input) {
	char* dico = (char*)malloc(sizeof(char) * TAILLE_MAX_CODE);
	dico = {};
	dico = lecture_normal_file(input);
	//for (int i = 0; i < strlen(dico); i++)
	//{
	//	printf("On lit le caractere : %c\n",	dico[i]);
	//}
	printf("\ntaille lecture dico %d : \n", strlen(dico));
	taille_code = strlen(dico);
	return (dico);
}

arbre creer_Arbre_By_Dico(char* dico,int taille) {
	arbre arbre_racine = creer_arbre('\0',NULL,NULL);
	arbre arbre_tmp = arbre_racine;
	//On travaille par blocs (taille(sur3bits) + char(sur1bit) + code(surTaillebits)

	int j = 0;//Indice de bloc
	while (j<taille)
	{
		int i = 0; //Indice dans le bloc
		int taille_code = 0;//Taille en nb de bits du code
		char caractere;//Caractere actuel

		//CALCUL DE TAILLE DU CODE GRACE AU 3 PREMIERS BITS
		taille_code = ((-48+(int)dico[i + j])*100) + ((-48+(int)dico[i + j + 1])*10) + (-48+(int)dico[i + j + 2]);// A COMPLETER

		bool flag = false; // caractere de fin ou non
		i = 3;//On passe les 3 premiers 'bits' toujours dédié a la taille du code
		caractere = dico[i + j];//On rajoute j pour avoir tt les blocs
		if (caractere == 'n' && dico[i + 1 + j] == 'u') {
			i += 4;
			flag = true;
		}
		else {
			i++;//(i=4)
		}
		
		arbre arbref;
		int k = 0;//Indice de notre boucle for pour parcourir notre code
		for (k; k < taille_code; k++)
		{
			arbref = creer_arbre('\0',NULL,NULL);//On creer notre arbre fils
			char bit = dico[i+j+k];
			if (bit == '0') {
				if (arbre_racine->fils_gauche == NULL) {
					arbre_racine->fils_gauche = arbref;
				}
				arbre_racine = arbre_racine->fils_gauche;
			}
			else if (bit == '1') {
				if (arbre_racine->fils_droit == NULL) {
					arbre_racine->fils_droit = arbref;
				}
				arbre_racine = arbre_racine->fils_droit;
			}
		}



		if (flag) {
			arbre_racine->elt = '\0';
		}
		else {
			arbre_racine->elt = caractere;
		}
		i += k;//On rajoute à i le k (longueur code)
		arbre_racine = arbre_tmp;
		j += i;//On rajoute à j le i (longueur bloc)
	}
	return arbre_tmp;
}

void completer_bits(Bin_file* file) {
	for (int i = file->i_octet; i < 8 ; i++)
	{
		write_bin_file(file, '0');
	}
}

//On appelle les différentes fonctyions de la compression
void compression(char* nameInput, char* nameOutput) {
	printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\tCOMPRESSIONS\n\n\n\n\n\n\n");
	Bin_file* file = open_normal_file(nameInput, 'r');

	/*list_t* list = newList();
	list = calcul_freq_char(lecture_normal_file(file));*/

	//On a essayer de tt rassembler sur la ligne suivante
	arbre ar = creer_Arbre_char(calcul_freq_char(lecture_normal_file(file)));
	close_normal_file(file);
	Bin_file* file_bin = open_bin_file(nameOutput, 'w');
	char* tmp = (char*)malloc(sizeof(char) * TAILLE_MAX_CODE);
	tmp = table_encodage(ar);
	int taille_header = strlen(tmp);
	ecriture_Dico_Header(tmp,file_bin);
	file = open_normal_file(nameInput, 'r');
	codage(ar, file_bin, lecture_normal_file(file));
	completer_bits(file_bin);//Rajoute les derniers bit manquants
	printf("\nTaille fichier compresse : %d\n", file_bin->nb_octets+taille_header);
	printf("\nLe taux de compression est de %f %\n", ((float)(100 * (taille_fichier - (file_bin->nb_octets + taille_header))) / (taille_fichier)));
	close_bin_file(file_bin);
	close_normal_file(file);
	free_arbre(ar);      // A decommenter une fois que l'on passe l'arbre dans le header du fichier compressé
	
}








//Idem pour décompression

void decompression(char* nameInput, char* nameOutput) {
	printf("\n\n\n\n\n\n\n\t\t\t\t\t\t\tDECOMPRESSIONS\n\n\n\n\n\n\n");

	Bin_file* file_bin = open_bin_file(nameInput, 'r');
	
	char* dico = (char*)malloc(sizeof(char) * TAILLE_MAX_CODE);
 	dico = lecture_Dico_Header(file_bin);
	int taille_dico = strlen(dico);
	arbre ar_by_dico = creer_Arbre_By_Dico(dico, taille_dico);
	Bin_file* file = open_normal_file(nameOutput, 'w');
	fseek(file_bin->file, taille_dico + 1, SEEK_SET);//On change le pointeur de départ pour la lecture du fichier (taille_dico+1)octets (ce qui représente la taille du code)
	decodage(ar_by_dico, ar_by_dico, file, file_bin);
	printf("\nTaille fichier compresse : %d\n", taille_fichier_bin+taille_code);
	printf("\nTaille fichier decompresse : %d\n", taille_fichier);
	printf("\nLe fichier etait compresse a %f %\n", ((float)(100 * (taille_fichier - (taille_fichier_bin+taille_code))) / (taille_fichier)));
	close_bin_file(file_bin);
	close_normal_file(file);
	free_arbre(ar_by_dico);
}


////////////////////////////////////////////////////////TESTS//////////////////////////////////////////////////////////////









void RUN_HUFFMAN() {
	
	printf("\n\n\n\n\n\n\n\n\t\tBonjour, appuyez sur ETREE pour commencer\n");
	getchar();
	system("cls");

	const char* nom_fichier_start = "D:/Travail/Polytech 3A/Projet_C/ProjetC/ProjetC/test1.txt";
	const char* nom_fichier_bin = "D:/Travail/Polytech 3A/Projet_C/ProjetC/ProjetC/test2.bin";
	const char* nom_fichier_end = "D:/Travail/Polytech 3A/Projet_C/ProjetC/ProjetC/test3.txt";
	
	int entre = 666;
	while (entre != 0)
	{
		printf("\n\n\nVeuillez taper 1 pour la compression de :\n\t%s\nvers :\n\t%s\n\nEt veuillez taper 2 pour la decompression de :\n\t%s\nvers :\n\t%s\n\n\nVeuillez taper 0 pour quitter\n\n",
			nom_fichier_start, nom_fichier_bin, nom_fichier_bin, nom_fichier_end);
		scanf("%d", &entre);
		switch (entre)
		{
		case 1:
			compression((char*)nom_fichier_start, (char*)nom_fichier_bin);
			break;
		case 2:
			decompression((char*)nom_fichier_bin, (char*)nom_fichier_end);
			break;
		case 0:
			break;
		default:
			printf("\nMauvais numero");
			break;
		}
		
		
	}
	
	


}


