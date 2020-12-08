#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "arbre_binaire.h"

// Type abstrait de données

arbre creer_arbre_vide(void)
{
    return NULL;
}

arbre creer_arbre(Elt e, arbre fg, arbre fd)
{
    arbre tmp = ((arbre)malloc(sizeof(noeud)));
    tmp->elt = e;
    tmp->fils_droit = fd;
    tmp->fils_gauche = fg;
    return tmp;
}

arbre fils_gauche(arbre a)
{
    return a->fils_gauche;
}

arbre fils_droit(arbre a)
{
    return a->fils_droit;
}

Elt racine(arbre a)
{
    return a->elt;
}

bool est_arbre_vide(arbre a)
{
    return (a == NULL);
}

// Fonctions outils

arbre creer_feuille(Elt e)
{
    return creer_arbre(e, creer_arbre_vide(), creer_arbre_vide());
}

bool est_feuille(arbre a)
{
    if (est_arbre_vide(a))
        return 0;
    return (est_arbre_vide(a->fils_gauche) && est_arbre_vide(a->fils_droit));
}

void print_arbre_aux(arbre a)
{
    if (est_arbre_vide(a))
        printf(".");
    else
    {
        printf("%d (", a->elt);
        print_arbre_aux(a->fils_gauche);
        printf(") (");
        print_arbre_aux(a->fils_droit);
        printf(")");
    }
}

void print_arbre(arbre a) // Notation préfixe
{
    print_arbre_aux(a);
    printf("\n");
}

void free_noeud(arbre a)
{
    free(a);
}

void free_arbre(arbre a)
{
    if (!est_arbre_vide(a)) {
        free_arbre(fils_gauche(a));
        free_arbre(fils_droit(a));
        free(a);
    }
}

// FONTIONS RAJOUTEES

void print_noeud(arbre a) {
    printf("Noeud -> Elt :%d\n", racine(a));
}




void parcours_profondeur(arbre a) {
    if (!est_arbre_vide(a)) {
        parcours_profondeur(fils_gauche(a));
        parcours_profondeur(fils_droit(a));
        print_noeud(a);
    }
}
