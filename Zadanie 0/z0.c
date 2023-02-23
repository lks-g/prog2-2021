#include <stdio.h>

/*
Napíšte funkciu primeFactors, ktorá vypíše všetky prvočíselné delitele vstupného čísla a (parameter funkcie).
Parameter m určuje maximálny počet vypísaných prvočíselných deliteľov (čítaj ďalej).
Funkciu primeFactors otestujte v rámci vášho programu vo funkcii main podľa nižšie uvedených pokynov. */

/* Premenna 'a' je cele cislo, ktoreho prvociselne delitele ideme vypisat. Musi platit, ze a>1. */
/* Premenna 'm' je lubovolne nezaporne cele cislo, ktore urcuje maximalny pocet vypisanych prvociselnych delitelov. */

int primeFactors(); /* Preddefinovanie funkcie primeFactors. */

int main(){
    int a = 0, m = 0;

    printf("Enter two numbers: ");
    scanf("%d%d", &a, &m); /* scanf zoberie ciselny vstup od pouzivatela a ulozi ho do premennych 'a' a 'm' */
    primeFactors(a, m);    /* Volame funkciu na zistenie prvociselnych delitelov vstupneho cisla. */
    
    return 0;
}

int primeFactors(int a, int m) {
    int jePrvocislo; /* Premenna 'je Prvocislo' uchova pravdivu hodnotu (1) alebo nepravdivu hodnotu (0). */

    /* Ak je podmienka splnena, program vypise chybnu spravu 'ERROR'. Pretoze najmensie prvocislo je 2. */
    if (a <= 1) { 
        printf("ERROR");
    }

    else if (m == 0) { /* Ak je podmienka splnena, program nevypise nic */
        return 0; 
    }

    else if (a > 1) { /* Pri splneni podmienky sa spusti funkcia. */
        for (int i = 2; i <= a; i++) { /* Cyklus najde vsetky prvociselne delitele. */
            if (a % i == 0) { /* Prikaz sa pozrie, ci cislo 'i' je delitelom cisla 'a'. */
                jePrvocislo = 1;
                for (int j = 2; j <= i / 2; j++) { /* Cyklus skontroluje ci 'i' je prvocislo. */
                    if (i % j == 0) { /* Prikaz zisti zvysok po deleni i % j. */
                        jePrvocislo = 0;
                        break;
                    }
                }
                
                if (jePrvocislo == 1 && m >= 1) { /* Pokial 'i' je prvocislo aj delitel cisla, vypis prvocislo v rozsahu m. */
                    printf("%d\n", i);
                    m--; /* Odpocita 1 od 'm' m = m-1 */
                }
            }
        }
    }

    return 0;
}