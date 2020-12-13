#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "Huffman.h"




arbre deserialisation(char* s, int* i)
{
    if (s[*i] == '0') {
        return creer_arbre_vide();
    }
    else {
        if (s[*i] == '1') {
            (*i)++;
        }
        else {
            arbre gauche = deserialisation(s, i); // Meme principe que le parcours en profondeur, on commence par la gauche
            arbre droit = deserialisation(s, i);
            return(creer_arbre(s[*i], gauche, droit));

        }
    }

}

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





//int serialisation(arbre arbreb, char* code, char c, int i) {
//
//    if (est_arbre_vide(arbreb)) {
//        /*  */
//        return i;
//    }
//    else {
//        char tmp1[100] = {};
//        char tmp2[100] = {};
//       /* char* tmp2 = (char*)malloc(100);*/
//        code[i] = c;
//        strcpy(tmp1, code);
//        strcpy(tmp2, code);
//        i++;
//        arbreb->code = code;
//        arbreb->code[i] = '\0';
//        printf("Code de %c : %s\n", arbreb->elt, arbreb->code);
//        serialisation(fils_gauche(arbreb), tmp1, '0', i);
//        serialisation(fils_droit(arbreb), tmp2, '1', i);
//
//    }
//    return i;
//
//}


void table_encodage(arbre arbre)
{
    char code[255] = {};
	char resultat[255] = {};
    serialisation(arbre, code,'0',0,NULL, resultat);
    printf("fin table encodage");
}





////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MES MODIFS



int serialisation(arbre arbreb, char* code, char c, int i, Bin_file* output, char tmp[]) {
	
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
		strcpy(tmp4, code);
		arbreb->code = tmp4;
		arbreb->code[i] = '\0';
		//fprintf(output->file, "Code de %c :", arbreb->elt);
		if (est_feuille(arbreb)) {
			int j = 1;
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
			for (j; j < i; j = j + 1)
			{
				//write_bin_file(output, arbreb->code[j]);
				printf("%c", arbreb->code[j]);
				tmp3[j+indice] = arbreb->code[j];
				cpt++;
			}
			
			char c_tmp[100];
			sprintf(c_tmp,"%d",cpt);
			tmp3[0] = c_tmp[0];

			strcat(tmp, tmp3);

			printf("\n");
		}
		serialisation(fils_gauche(arbreb), tmp1, '0', i, output,tmp);
		serialisation(fils_droit(arbreb), tmp2, '1', i, output,tmp);

	}
	return i;
}

//char* obtention_code(char* liste,char caractere) {//PAS UTILE SI ON A LE BON CODE
//	char* code = (char*)malloc(sizeof(char) * strlen(liste));
//
//	int i = 0;
//	bool flag = true;
//	while (i < strlen(liste))
//	{
//		char tmp1[10] = {};//buffer pour la taille 
//		int j = i;
//		int cpt = 0;
//		while (((int)liste[j]>=48 && (int)liste[j]<=57) && flag) {//est pas un chiffre et frag vrai
//			tmp1[cpt] = liste[j];
//			int taille = atoi((const char*)tmp1);
//			j++;
//			cpt++;
//		}
//		char* buffer = (char*)malloc(sizeof(char) * (int)liste[i]);
//
//		if (liste[i]==caractere) {
//			
//			while (liste[i - 1] < liste[i - 2]) {
//
//			}
//		}
//	}
//	return NULL;
//}


//on passe du caractère au bit
void codage_caract(char caract, arbre arbre, Bin_file* output) {

	if (!est_arbre_vide(arbre)) {

		if (arbre->elt == caract) {
			for (int j = 1; j < strlen(arbre->code); j = j + 1)
			{
				//write_bin_file(output, arbre->code[j]);
				printf("%c",arbre->code[j]);
			}
		}
		codage_caract(caract, fils_gauche(arbre), output);
		codage_caract(caract, fils_droit(arbre), output);
	}
}

/*
//on passe des bits au caractère
void décodage_caract(char* bits, arbre arbre, Bin_file* output) {

	if (!est_arbre_vide(arbre)) {
		int i = 0;
		char* cod;
		for (int j = 1; j < strlen(arbre->code); j = j + 1) {
			cod[i] = arbre->code[j];
			i = i + 1;
		}
		cod[i] = '\0';
		if (cod == bits) {
			fprintf(output->file, "%c", arbre->elt);
			//printf("%c",arbre->elt);
		}

		décodage_caract(bits, fils_gauche(arbre), output);
		décodage_caract(bits, fils_droit(arbre), output);
	}
}
//recherche si un bit est présent dans le tableau et retourne 1 ou 0
int rechercher_bits(char* bits, arbre arbre) {
	int boole = 0;
	if (!est_arbre_vide(arbre)) {
		int i = 0;
		char* cod;
		for (int j = 1; j < strlen(arbre->code); j = j + 1) {
			cod[i] = arbre->code[j];
			i = i + 1;
		}
		cod[i] = '\0';
		if (cod == bits) {

			boole = 1;
			return boole;
		}

		rechercher_bits(bits, fils_gauche(arbre));
		rechercher_bits(bits, fils_droit(arbre));
		return boole;
	}
}
//On appelle les différentes fonctyions de la compression
void compression(char* nameInput, Bin_file* output) {
	FILE* inpt;
	int i;
	int j;
	const char* s;
	char* code;
	char c;
	inpt = fopen(nameInput, "r");
	list_t* list = newList();
	while (fscanf(inpt, "%d", &i) != EOF) {
		list = calcul_freq_char((char*)s);
	}
	arbre ar = creer_Arbre_char(list);
	j = serialisation(ar, code, c, j, output);
	codage_caract((char)s, ar, output);
	fclose(inpt);
}


*/




/*
//Idem pour décompression
void decompression(char* nameInput, Bin_file* output, arbre ar) {
	Bin_file* inpt;
	int i;
	int j;
	char* s;
	char* code;
	char c;
	inpt = open_bin_file(nameInput, (char)"r");
	while (read_bin_file(inpt) != EOF) {
		s = read_bin_file(inpt);
		if (rechercher_bits((char*)s, ar) == 1) {
			décodage_caract((char*)s, ar, output);
		}
	}
	close_bin_file(inpt);
}
*/

////////////////////////////////////////////////////////TESTS//////////////////////////////////////////////////////////////









void TEST_HUFFMAN() {
    printf("\tTest calcul_frequence : ");
    const char* s = "abbcccdddd";//1a2b3c4d
    list_t* list = newList();

    //list = calcul_freq_char((char*)s);

	const char* nom_fichier_2 = "D:/Travail/Polytech 3A/Projet_C/ProjetC/ProjetC/test1.txt";
	Bin_file* file3 = open_normal_file((char*)nom_fichier_2, 'r');
	list = calcul_freq_char(lecture_normal_file(file3));

    printf(" _la liste donnee est %s", s);
    printList(*list);

    printf("\tTest creation_arbre : ");
    arbre ar = creer_Arbre_char(list);
    print_arbre(ar);

    table_encodage(ar);
    //printf("code for arbre : %s", tab['a']);
	//printf("\n\n\ntest compare\n\n\n");
	//printf("%d", 'A' > '0');

}


