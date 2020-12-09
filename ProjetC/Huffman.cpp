#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

#include "Huffman.h"

//
//void serialisation(arbre a, char* s, int i)
//{
//    if (est_arbre_vide(a))
//    {
//        s[i] = '0';
//        (i)++;
//    }
//    else
//    {
//        s[i] = '1';
//        (i)++;
//        s[i] = a->elt;
//        (i)++;
//        serialisation(a->fils_gauche, s, i);
//        serialisation(a->fils_droit, s, i);
//    }
//    s[i] = '\0';
//}
char* serialisation(arbre a, char* s) {
    if (est_arbre_vide(a)) {
        char tmp[] = "0";
        strcat(s, tmp);
    }
    else
    {
        char res[3] = "";
        char elem1[2] = "";
        char elem = a->elt;
        elem1[0] = elem;
        char tmp[] = "1";
        strcat(res, tmp);
        strcat(res, elem1);
        strcat(s, res);
        serialisation(a->fils_gauche, s);
        serialisation(a->fils_droit, s);

    }
    return s;
}


arbre deserialisation(char* s, int i)
{
    arbre a, g, d;
    char c;
    if (s[i] != '\0')
    {
        if (s[i] == '0')
        {
            a = NULL;
            (i)++;
        }
        else
        {
            (i)++;
            c = s[i];
            (i)++;
            g = deserialisation(s, i);
            d = deserialisation(s, i);
            a = creer_arbre(c, g, d);
        }
    }
    else
    {
        a = NULL;
    }
    return a;
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


    //int codagehuffman(*noeud nd, *arbre arbre)
    //{
    //    if (est_tete(nd) == 1) {
    //        return nd->code = "\0";
    //    }
    //    if (nd == fils_gauche(pere(nd))) {
    //        return nd->code = "0" + codagehuffman(pere(nd), arbre);
    //    }
    //    if (nd == fils_droit(pere(nd))) {
    //        return nd->code = "1" + codagehuffman(pere(nd), arbre);
    //    }
    //}
    ////fonction rechercher noeud qui pour un un caractère donné renvoie le noeud correspondant



//char* str_append(char* str, char* other) //code + '1' ajouter un string en fin
//{
//    char* result = (char *)malloc(sizeof(char) * (strlen(str) + strlen(other)));
//    strcat(str, other);
//    //strcat(result, other);
//
//    //free(str);
//    //free(other);
//
//    return str;
//}

void table_encodage(arbre arbre)
{
    char code[255] = {};

    walk(arbre, code);
    
    printf("fin table encodage");
}

void walk(arbre arbre, char code[]) //parcours l'arbre
{
    if (arbre->fils_droit == NULL && arbre->fils_gauche == NULL)
    {
        char tmp[255] = {};
        strcpy(tmp, code);


        arbre->code = tmp;
    
    }
    else
    {
        if (arbre->fils_gauche != NULL)
        {
            walk(arbre->fils_gauche, strcat(code, (char*)"0"));
            //spr 1ier
        }

        if (arbre->fils_droit != NULL)
        {
            code[strlen(code) - 1] = '\0';
            walk(arbre->fils_droit, strcat(code, (char*)"1"));
            code[strlen(code) - 1] = '\0';
            //spr 1ier
        }
    }
}




void TEST_HUFFMAN() {
    printf("\tTest calcul_frequence : ");
    const char* s = "abbcccdddd";//1a2b3c4d
    list_t* list = newList();
    list = calcul_freq_char((char*)s);
    printf(" _la liste donnee est %s", s);
    printList(*list);

    printf("\tTest creation_arbre : ");
    arbre ar = creer_Arbre_char(list);
    print_arbre(ar);

    table_encodage(ar);
    //printf("code for arbre : %s", tab['a']);
}


