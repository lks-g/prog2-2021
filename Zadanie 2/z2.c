#include <stdio.h>
#include <stdlib.h>
#define R_MAX 2147483647
static long long unsigned int SEED = 0x1;

void srnd(int seed)
{
    SEED = seed;
}

int rnd(int from, int to)
{
    SEED = SEED * 16807 % R_MAX;
    return from + (int)SEED % (to - from + 1);
}

int seed, n, m1, m2;

int x, y, i, j;
const int nmin = 10;
const int nmax = 100;

int main()
{
    scanf("%d%d%d%d", &seed, &n, &m1, &m2);
    srnd(seed);
    // generovanie blockerov a boosterov
    int plocha[105] = {0}; // ak je pozicia = 99 + hod kockov
    int vyskyt[105] = {0}; // sluzi pre napocet pozicii

    if (!(seed > 0 && n >= nmin && n <= nmax && (m1 + m2) <= n / 2))
    {
        return 1;
    }
    for (i = 0; i < m1; i++)
    {
        x = rnd(1, n - 1);
        if (plocha[x] == 0)
        {
            plocha[x] = 1;
        }
        else
        {
            i = i - 1;
        }
    }

    for (j = 0; j < m2; j++)
    {
        y = rnd(1, n - 1);
        if (plocha[y] == 0)
        {
            plocha[y] = 2;
        }
        else
        {
            j = j - 1;
        }
    }
    // printovanie boosterov a blockerov
    printf("BLOCK:");
    for (i = 0; i < n; i++)
    {
        if (plocha[i] == 1)
        {
            printf("%d ", i);
        }
    }
    printf("\nBOOST:");
    for (i = 0; i < n; i++)
    {
        if (plocha[i] == 2)
        {
            printf("%d ", i);
        }
    }
    printf("\n");
    // zavod
    int tah = 1;
    int hrac = 1;
    int booster1 = 0; // pocty boostrov
    int booster2 = 0;
    int predboost1 = 0, predboost2 = 0;
    int poboost1 = 0, poboost2 = 0;
    int r1 = 0;
    int r2 = 0;
    int poz1 = -1, poz2 = -1;   // pozicia hracov
    int popoz1 = 0, popoz2 = 0; // pozicia hraca po vykonani tahu
    int prepoz1 = 0, prepoz2 = 0;
    int winner = 0;
    int hotspot = 0;

    while (poz1 < n && poz2 < n)
    { // hra konci ked jeden z hracov dosiahne posledne pole alebo vacsie
        r1 = rnd(1, 6);
        r2 = rnd(1, 6);

        if (tah % 2 == 1)
        {

            prepoz1 = poz1;
            predboost1 = booster1;

            if (poz1 == -1 && (r1 + r2) > 7)
            { // zaciatok hry hrac1

                poz1 = r1 + r2 - 7 + booster1;

                if (plocha[poz1] == 1)
                { // ak poz1 ukazuje na bloker
                    if (booster1 == 0)
                    {
                        plocha[poz1] = 0; //
                        poz1 = -1;
                    }
                    else if (booster1 > 0)
                    {
                        plocha[poz1] = 0;
                        booster1 = 0;
                    }
                }
                else if (plocha[poz1] == 2)
                { // ak poz1 ukazuje na booster
                    booster1++;
                    plocha[poz1] = 0;
                }

                //  printf("test %d", poz1);
            }

            else if (poz1 > -1)
            {

                if (r1 == 6 && r2 == 6 && poz2 > poz1)
                {
                    poz1 = poz2;
                    poz2 = prepoz1;
                    vyskyt[poz2]++;
                }
                else if (r1 == 1 && r2 == 1 && poz1 > poz2 && poz2 > -1)
                {
                    poz1 = poz2;
                    poz2 = prepoz1;
                    vyskyt[poz2]++;
                }
                else
                {
                    poz1 = poz1 + max(r1, r2) + booster1;

                    if (plocha[poz1] == 1)
                    { // ak poz1 ukazuje na bloker
                        if (booster1 == 0)
                        {
                            plocha[poz1] = 0; //
                            poz1 = -1;
                        }
                        else if (booster1 > 0)
                        {
                            plocha[poz1] = 0;
                            booster1 = 0;
                        }
                    }
                    else if (plocha[poz1] == 2)
                    { // ak poz1 ukazuje na booster
                        booster1++;
                        plocha[poz1] = 0;
                    }
                }
            }
            if (poz1 == poz2) // opravit len pre poz2>-1
                poz2 = -1;

            poboost1 = booster1;
            popoz1 = poz1;

            if (poz1 != -1)
                vyskyt[poz1]++;

            printf("[%d,%d] [%d,%d] [%d,%d] [%d,%d]\n", tah, 1, prepoz1, predboost1, r1, r2, popoz1, poboost1);
        }
        else
        {

            prepoz2 = poz2;
            predboost2 = booster2;

            if (poz2 == -1 && (r1 + r2) > 7)
            { // zaciatok hry hrac1
                poz2 = r1 + r2 - 7 + booster2;
                //  printf("test %d", poz1);
                if (plocha[poz2] == 1)
                { // ak poz1 ukazuje na bloker
                    if (booster2 == 0)
                    {
                        plocha[poz2] = 0; //
                        poz2 = -1;
                    }
                    else if (booster2 > 0)
                    {
                        plocha[poz2] = 0;
                        booster2 = 0;
                    }
                }
                else if (plocha[poz2] == 2)
                { // ak poz1 ukazuje na booster
                    booster2++;
                    plocha[poz2] = 0;
                }
            }
            else if (poz2 > -1)
            {

                if (r1 == 6 && r2 == 6 && poz1 > poz2)
                {
                    poz2 = poz1;
                    poz1 = prepoz2;
                    vyskyt[poz1]++;
                }
                else if (r1 == 1 && r2 == 1 && poz2 > poz1 && poz1 > -1)
                {
                    poz2 = poz1;
                    poz1 = prepoz2;
                    vyskyt[poz1]++;
                }
                else
                {
                    poz2 = poz2 + max(r1, r2) + booster2;

                    if (plocha[poz2] == 1)
                    { // ak poz1 ukazuje na bloker
                        if (booster2 == 0)
                        {
                            plocha[poz2] = 0; //
                            poz2 = -1;
                        }
                        else if (booster2 > 0)
                        {
                            plocha[poz2] = 0;
                            booster2 = 0;
                        }
                    }
                    else if (plocha[poz2] == 2)
                    { // ak poz1 ukazuje na booster
                        booster2++;
                        plocha[poz2] = 0;
                    }
                }
            }

            if (poz1 == poz2) // opravit len pre poz2>-1
                poz1 = -1;

            poboost2 = booster2;
            popoz2 = poz2;

            if (poz2 != -1)
                vyskyt[poz2]++;

            printf("[%d,%d] [%d,%d] [%d,%d] [%d,%d]\n", tah, 2, prepoz2, predboost2, r1, r2, popoz2, poboost2);
        }

        if (poz1 >= n)
            winner = 1;
        if (poz2 >= n)
            winner = 2;

        hotspot = maxpole(vyskyt);

        if (winner > 0)
        {
            printf("WINNER:%d\n", winner);
            printf("HOTSPOT:%d\n", hotspot);

            // for(i=0;i<105;i++)
            //    printf("%d %d \n",i,vyskyt[i]);

            return (0);
        }
        tah++;
    }
}

int maxpole(int parpole[])
{

    int i;
    int maxhod = 0, a = 0;

    for (i = 0; i < 105; i++)
    {
        if (parpole[i] > maxhod)
        {
            maxhod = parpole[i];
            a = i;
        }
    }

    return maxhod;
}

int max(int par1, int par2)
{
    int vysledok;
    if (par1 > par2)
        vysledok = par1;
    else
        vysledok = par2;
    return vysledok;
}
