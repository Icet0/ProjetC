#include <stdlib.h>
#include <stdio.h>
#include "bin.h"

BinFile *bfopen(char *name, char mode) // Ouverture fichier bit à bit
{
    BinFile *result = (BinFile *)malloc(sizeof(BinFile));

    result->mode = mode;

    if (mode == 'r')
    {
        result->file = fopen(name, "r");
    }
    else
    {
        result->file = fopen(name, "w");
    }

    result->record_length = 0;
    result->i_record = 0;
    result->i_octet = 0;
    result->nb_octets = 0;

    return result;
}

void bfwrite(BinFile *output, char bit) // Ecriture d’un bit dans un fichier bit à bit
{
    unsigned char octet, mask;
    int i;

    // Ecris l'octet en version literal '0' ou '1'
    output->octet[output->i_octet++] = bit; // stockage du bit

    // Si l'octet est plein (octet literal toujours) '01001001'
    if (output->i_octet == 8)
    {
        octet = 0;
        mask = 0x80;

        for (i = 0; i < 8; i++)
        {
            if (output->octet[i] == '1')
            {
                octet = octet | mask; // OU binaire
            }
            mask = mask >> 1; // decalage d'un bit à droite
        }

        // Ici, octet = 01001001 en binaire
        // On écrit donc l'octet dans le 'record'
        output->i_octet = 0;
        output->record[output->i_record] = octet;
        output->i_record++;
        output->nb_octets++;

        // Si le record/buffer est plein on écrit dans le fichier
        if (output->i_record == BLOCK_SIZE)
        {
            fwrite(output->record, sizeof(char), BLOCK_SIZE, output->file);
            output->i_record = 0;
        }
    }
}

char bfread(BinFile *input) // Lecture d’un bit dans un fichier bit à bit
{
    char bit;
    int i;

    if (input->record_length == 0)
    {
        input->record_length = fread(input->record, sizeof(char), BLOCK_SIZE, input->file);
        input->i_record = 0;
        // Transfert des 8 bits de input->record[input->i_record] dans input->octet
        unsigned char mask = 128;
        for (i = 0; i < 8; i++)
        {
            if ((input->record[input->i_record] & mask) != 0)
            {
                input->octet[i] = '1';
            }
            else
            {
                input->octet[i] = '0';
            }
            mask = mask >> 1; // decalage d'un bit à droite
        }
        // mask & input->record[input->i_record] -->          true/false --> '1' / '0'
        // 1000 & 1011                           --> 1000 --> true       --> '1'
        // 0100 & 1011                           --> 0000 --> false      --> '0'
        // 0010 & 1011                           --> 0010 --> true       --> '1'
        // 0001 & 1011                           --> 0001 --> true       --> '1'

        input->i_record++;
        input->i_octet = 0;
        input->nb_octets = input->nb_octets + input->record_length;
    }

    bit = input->octet[input->i_octet];
    input->i_octet++;

    if (input->i_octet == 8)
    {
        // Transfert des 8 bits de input->record[input->i_record] dans input->octet
        unsigned char mask = 128;
        for (i = 0; i < 8; i++)
        {
            if ((input->record[input->i_record] & mask) != 0)
            {
                input->octet[i] = '1';
            }
            else
            {
                input->octet[i] = '0';
            }
            mask = mask >> 1; // decalage d'un bit à droite
        }
        input->i_record++;
        input->i_octet = 0;
        if (input->i_record == BLOCK_SIZE)
        {
            input->record_length = 0;
        }
    }
    return bit;
}

int bfclose(BinFile *fichier)
{
    int nb_octets = fichier->nb_octets;
    unsigned char octet, mask;
    int i;

    if (fichier->mode == 'w')
    {
        if (fichier->i_octet != 0) // Traitement derniers bits
        {
            octet = 0;
            mask = 0x80;
            for (i = 0; i < fichier->i_octet - 1; i++)
            {
                if (fichier->octet[i] == '1')
                {
                    octet = octet | mask;
                }
                mask = mask >> 1;
            }
            fichier->record[fichier->i_record++] = octet;
            fichier->i_record = fichier->i_record++;
            nb_octets = nb_octets++;
        }
        // Flush le buffer
        if (fichier->i_record != 0)
        {
            fwrite(fichier->record, sizeof(char), BLOCK_SIZE, fichier->file); // Ecriture de fichier->record dans fichier->file
        }
    }
    fclose(fichier->file);
    free(fichier);

    return nb_octets;
}
