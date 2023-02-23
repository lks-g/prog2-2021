#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <ctype.h>
#include <unistd.h>

/////////////////////     NEMENIT !!!      ////////////////////////

// Funkcia na nacitanie jedneho riadku textu zo standardneho vstupu.

// VSTUP:
//        Ziadny.
// VYSTUP:
//        Smernik na alokovany blok pamate
//        obsahujuci C retazec reprezentujuci
//        nacitany riadok ukonceny znakom '\n'.
//        Funkcia vrati NULL ak:
//          * dojde k chybe pri alokacii pamate
//          * dojde chybe citania
//          * narazi sa na EOF (End-of-file)

char *readline()
{
    const size_t BSIZE = 100;
    char *line = NULL;
    size_t capacity = 0;

    do
    {
        // Priprav dostatok pamate.
        capacity += BSIZE;

        // Alokuj miesto na capacity + '\0'.
        line = (char *)realloc(line, (capacity + 1) * sizeof(char));
        if (line == NULL)
            return line;

        // Nacitaj zo vstupu riadok (resp. jeho zvysok).
        if (fgets(line + capacity - BSIZE, BSIZE + 1, stdin) == NULL)
        {
            free(line);
            return NULL; // doslo k chybe citania alebo sme narazili na EOF
        }
        // Opakuj, pokym sa nenacita cely riadok.
        // Indikacia, ze zostal zvysok riadku:
        //   1. je naplnena cela BSIZE
        //   2. na konci nie je '\n'
    } while (strlen(line + capacity - BSIZE) >= BSIZE && line[capacity - 1] != '\n');
    // nacitany riadok obsahuje na konci znak '\n'
    return line;
}

////////////////////////////////////////////////////////////////

int main(int argc, char *argv[])
{
    char *optstring = ":aculr:";
    int prepinac;

    int argCheck = 0, argCheckL = 0;

    while ((prepinac = getopt(argc, argv, optstring)) != -1) // Cyklus na podmienky.
    {
        switch (prepinac)
        {
        case 'a':
            break;

        case 'c':
            break;

        case 'u':
            argCheck = 1;
            if (argCheckL == 1)
            {
                return 3;
            }
            break;

        case 'l':
            argCheckL = 1;
            if (argCheck == 1)
            {
                return 3;
            }
            break;

        case ':':
            return 2;

        case 'r':
            break;

        default:
            return 1;
        }
    }

    char *line = NULL;

    while ((line = readline()) != "\n\0")
    {
        if (line[0] == '\n')
        {
            return 1;
        }
        break;
    }

    int len = strlen(line);
    int opt;

    while ((opt = getopt(argc, argv, optstring)) != -1)
    {
        switch (opt)
        {
        case 'a':
            for (int i = 0; i < len; i++)
            {
                if (isalpha(line[i]))
                {
                    line[i] = line[i];
                }
                else
                {
                    line[i] = ' ';
                }
            }
            break;

        case 'c':

            for (int j, i = 0; line[i] != '\0'; i++)
            {
                while (!(isalpha(line[i]) || line[i] == '\0'))
                {
                    for (j = i; line[j] != '\0'; j++)
                    {
                        line[j] = line[j + 1];
                    }
                    line[j] = '\0';
                }
            }
            break;

        case 'u':
            for (int i = 0; i < len; i++)
            {
                line[i] = toupper(line[i]);
            }
            break;

        case 'l':
            for (int i = 0; i < len; i++)
            {
                line[i] = tolower(line[i]);
            }
            break;

        default:
            return 1;
        }
    }

    printf("%s", line);
    free(line);

    return 0;
}
