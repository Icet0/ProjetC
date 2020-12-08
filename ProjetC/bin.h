#include <stdio.h>

#define BLOCK_SIZE 4096 // 1 bloc sur disque = 4096 octets

typedef struct
{
    FILE *file;                       // identification du fichier
    char mode;                        // lecture 'r' ou écriture 'w'
    unsigned char record[BLOCK_SIZE]; // tampon pour lire ou écriture
    int record_length;                // nombre d'éléments dans le tampon
    int i_record;                     // indice dans le tampon
    char octet[8];                    // pour expension d'un octet en 8 caractères
    int i_octet;                      // indice dans octet
    int nb_octets;                    // nombre d'octets lus ou écrits
} BinFile;

BinFile *bfopen(char *name, char mode);
void bfwrite(BinFile *output, char bit);
char bfread(BinFile *input);
int bfclose(BinFile *fichier);