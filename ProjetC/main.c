#include <stdio.h>
#include "io/bin.h"

int main()
{
    BinFile *file = bfopen("C:\\Users\\Guigui\\Desktop\\Projet\\test.txt", 'w');
    bfwrite(file, '1');
    bfwrite(file, '0');
    bfwrite(file, '0');
    bfwrite(file, '0');
    bfwrite(file, '0');
    bfwrite(file, '0');
    bfwrite(file, '0');
    bfwrite(file, '1');

    printf("writing %d byte before closing file.\n", bfclose(file));

    BinFile *file2 = bfopen("C:\\Users\\Guigui\\Desktop\\Projet\\test.txt", 'r');

    for (int i = 0; i < 8; i++)
    {
        char test = bfread(file2);
        printf("%c\n", test);
    }

    return 0;
}