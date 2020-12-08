#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "Arbre_binaire.h"
#include "Huffman.h"



#include <string.h>
#define C 200
#include "liste.h"

void serialisation(arbre a, char* s, int i)
{
    if (est_arbre_vide(a))
    {
        s[i] = '0';
        (i)++;
    }
    else
    {
        s[i] = '1';
        (i)++;
        s[i] = a->elt;
        (i)++;
        serialisation(a->fils_gauche, s, i);
        serialisation(a->fils_droit, s, i);
    }
    s[i] = '\0';
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


/*
void lecture_char() {
    if (fin != 0) {
        if (rechercher(s[i]) == 0) {
            creer_arbre(s[i], NULL, NULL, NULL);
            addFirst(new, l);
        }
        new->cpt += 1;
    }

    //Tant que l'on a plus d'un noeud/element ou de deux dans le tableau
    while (l->numElements != 1)
        //ajouter valeur 0 ou 1 au noeud
        //récupérer les noeuds minimals du tableau et les ajouter dans un nouveau noeud que l'on met dans la liste

    {
        aux0 = popBest(l);
        aux1 = popBest(l);
        new = creer_arbre(aux0->cpt + aux1->cpt, aux0, aux1, NULL);
        new->cpt += aux0->cpt + aux1->cpt;
        addFirst(new, l);
        l->numElements -= 1;
    }
    //Affectation des valeurs
    arbre = popBest(l);

    int codagehuffman(*noeud nd, *arbre arbre)
    {
        if (est_tete(nd) == 1) {
            return nd->code = "\0";
        }
        if (nd == fils_gauche(pere(nd))) {
            return nd->code = "0" + codagehuffman(pere(nd), arbre);
        }
        if (nd == fils_droit(pere(nd))) {
            return nd->code = "1" + codagehuffman(pere(nd), arbre);
        }
    }
    //fonction rechercher noeud qui pour un un caractère donné renvoie le noeud correspondant
}


*/



