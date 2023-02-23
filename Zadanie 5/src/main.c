#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rng.h"
#include "data.h"

void status_Monster(Unit Monster) /// Funkcia vypise stav MONSTRA
{
    printf("%s, ATT:%d, DEF:%d, HP:%d, LVL:%d\n", Monster.type->name, Monster.type->att, Monster.type->def, Monster.hp, Monster.level);
}

void status_Enemy(int index, Unit pole_nepriatelov[index]) /// Funkcia vypise stav ENEMY
{
    printf("[%d] %s, ATT:%d, DEF:%d, HP:%d, LVL:%d\n", index, pole_nepriatelov[index].type, pole_nepriatelov[index].type->att, pole_nepriatelov[index].type->def, pole_nepriatelov[index].hp, pole_nepriatelov[index].level);
}

void Inicializacia_Enemy(int pocet, Unit pole_nepriatelov[pocet]) /// Funkcia na vytvorenie Armady
{
    int rand;      /// Premmenna uchova pseudo-nahodne cislo
    int index = 0; /// Index pola

    for (int i = 0; i < pocet; i++) /// Cyklus vygeneruje pole nepriatelov podla pseudo-nahodnych cisel
    {
        rand = rnd(0, ENEMY_TYPE_COUNT - 1);
        pole_nepriatelov[i].type = &enemy_types[rand]; /// Ziskanie nazvu jednotky

        rand = rnd(ENEMY_MIN_INIT_HP, ENEMY_MAX_INIT_HP);
        pole_nepriatelov[i].hp = rand; /// Ziskanie HP(zivotov) jednotky

        rand = rnd(0, UNIT_MAX_LEVEL);
        pole_nepriatelov[i].level = rand; /// Ziskanie Levelu jednotky

        /// Vypis jednotiek
        printf("[%d] %s, ATT:%d, DEF:%d, HP:%d, LVL:%d\n", index, pole_nepriatelov[i].type, pole_nepriatelov[i].type->att, pole_nepriatelov[i].type->def, pole_nepriatelov[i].hp, pole_nepriatelov[i].level);
        index++; /// Zvysenie indexu
    }
}

int main(int argc, char *argv[])
{
    char *ptr; /// Pointer vyuzity pre prevode z char na int

    long int seed, Enemy_Pocet; /// Seed pre srnd funkciu, Pocet nepriatelskych jednotiek

    int utok_enm = 0;                            /// Utok_enm obsahuje Index Enemaka s min HP
    int dmg, Monster_Total = 0, Enemy_Total = 0; /// Premmenne ktore obsahuju: DMG, Maximalny DMG sposobeny Monstrom, --//-- sposobeny Enemakom

    int base_dmg, strength, defense; /// Premenne potrebne na vypocet DMG

    int alive; /// Premenne na ulozenie zivych

    int podmienka = 0; /// Pomocna premenna na chzbovu situaciu 1.

    if (argc == 6) /// Ak je zadany volitelny parameter spusti sa funkcia na vytvorenie vlastnych jednotiek
    {
        FILE *file;
        int att, def;   /// Ulozenie ATT a DEF zo suboru
        char enemy[40]; /// Pole na ulozenie nazvu jednotiek

        file = fopen(argv[5], "r"); /// Otvorenie suboru na citanie

        if (file == NULL)
            return 2;

        for (int o = 0; o < ENEMY_TYPE_COUNT; o++) /// Cyklus nacita jednotky s ich ATT a DEF hodnotami
        {
            fscanf(file, "%s %d %d", enemy, &att, &def);

            strcpy(enemy_types[o].name, enemy); /// Na index i sa ulozi vybrana jednotka
            enemy_types[o].att = att;           /// priradenie hodnoty ATT pre vybranu jednotku
            enemy_types[o].def = def;           /// priradenie hodnoty DEF pre vybranu jednotku
        }

        fclose(file); /// Zatvorenie suboru
    }

    Unit Monster; /// Vytvorenie premennej typu Unit.

    Enemy_Pocet = strtol(argv[2], &ptr, 10); /// Prevod vstupnych argumentov z char do int
    seed = strtol(argv[3], &ptr, 10);        /// Prevod vstupnych argumentov z char do int

    srnd(seed); /// Pseudo-random-number generator

    Unit pole_nepriatelov[Enemy_Pocet]; /// Vytvorenie premennej typu Unit

    int h = 0;

    while (h < MONSTER_TYPE_COUNT) /// Cyklus zisti TYP MONSTRA
    {
        if (strcmp(argv[1], monster_types[h].name) == 0) /// Porovnanie zadaneho monstra s databazov monstier
        {
            Monster.type = &monster_types[h].name; /// Priradenie nazvu monstra
            Monster.hp = MONSTER_INITIAL_HP;       /// Priradenie zivotu monstra (default 500)
            Monster.level = 0;                     /// Priradenie levelu monstra
            podmienka = 1;
        }
        h++; /// Zvysenie indexu pola
    }

    if (podmienka == 0) /// Ak je podmienka splnena program skonci s navratovou hodnotou 1.
        return 1;

    /// Vypis vytvoreneho monstra
    printf("%s, ATT:%d, DEF:%d, HP:%d, LVL:%d\n", Monster.type->name, Monster.type->att, Monster.type->def, Monster.hp, Monster.level);
    Inicializacia_Enemy(Enemy_Pocet, pole_nepriatelov); /// Volanie funkcie na vygenerovanie nepriatelov.

    printf("\n"); /// Medzera

    while (1) /// Cyklus v ktorom prebehne SUBOJ
    {
        int najmenej = ENEMY_MAX_INIT_HP + 1; /// Uchovanie min HP jednotky
        alive = 0;

        for (int i = 0; i < Enemy_Pocet; i++) /// Cyklus zisti Enemy index s najmensimi HP
        {
            if (pole_nepriatelov[i].hp > 0) /// Pokial ma nepriatel aj monstrum viac HP ako 0 tak sa podmienka splni
            {
                if (najmenej > pole_nepriatelov[i].hp)
                {
                    najmenej = pole_nepriatelov[i].hp; /// Zistenie min HP
                    utok_enm = i;                      /// Index Enemaka s min HP
                }
                alive++;
            }
        }

        if (alive == 0) /// Pokial nie je ziadna jednotka ziva vyhrava Monstrum
        {
            printf("Winner: %s\n", Monster.type->name);
            break;
        }

        else if (Monster.hp < 0) /// Pokial je monstrum mrtve vyhrava Enemy
        {
            printf("Winner: Enemy\n");
            break;
        }

        /// Vzorce na vypocet DMG pre MONSTER
        base_dmg = 30 + Monster.level - pole_nepriatelov[utok_enm].level;
        strength = 100 + rnd(1, Monster.hp) + Monster.type->att;
        defense = 100 + rnd(1, pole_nepriatelov[utok_enm].hp) + pole_nepriatelov[utok_enm].type->def;
        dmg = (base_dmg * strength) / defense;

        Monster_Total += dmg; /// Total Monster DMG

        printf("%s => %d => [%d] %s\n", Monster.type->name, dmg, utok_enm, pole_nepriatelov[utok_enm].type->name);
        pole_nepriatelov[utok_enm].hp -= dmg; /// Odcitanie DMG of Enemy HP

        for (int k = 0; k < Enemy_Pocet; k++)
        {
            if (pole_nepriatelov[k].hp > 0 && Monster.hp > 0) /// Pokial je Enemy a Monster ALIVE
            {
                if (pole_nepriatelov[k].hp < 0)
                {
                    continue;
                }

                /// Vzorce na vypocet DMG pre ENEMIES
                base_dmg = 30 + pole_nepriatelov[k].level - Monster.level;
                strength = 100 + rnd(1, pole_nepriatelov[k].hp) + pole_nepriatelov[k].type->att;
                defense = 100 + rnd(1, Monster.hp) + Monster.type->def;
                dmg = (base_dmg * strength) / defense;

                if (Monster.hp < 0)
                    continue;

                printf("[%d] %s => %d => %s\n", k, pole_nepriatelov[k].type->name, dmg, Monster.type->name); /// Vypis Utoku Enemies
                Monster.hp -= dmg;                                                                           /// Odcitanie DMG od monster HP

                Enemy_Total += dmg; /// Total Enemy DMG
            }
        }

        if (Monster.level < UNIT_MAX_LEVEL && Monster.hp > 0) /// Ak ma MONSTER mensi level ako 10 tak sa jeho level zvysuje pokial nedosiahne MAX LEVEL
        {
            Monster.level += 1;
        }

        printf("\n");            /// Medzera
        status_Monster(Monster); /// Vypis stavu Monstra

        for (int l = 0; l < Enemy_Pocet; l++) /// Vypis stavu jednotiek
        {
            status_Enemy(l, pole_nepriatelov);
        }

        printf("\n");
    }

    printf("Total monster DMG: %d\n", Monster_Total); /// Vypis Total DMG pre MONSTER
    printf("Total enemies DMG: %d\n", Enemy_Total);   /// Vypis Total DMG pre ENEMY

    return 0;
}
