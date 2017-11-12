#ifndef KEREK_H
#define KEREK_H

#include <stdio.h>
#include <stdlib.h>
#include<stdbool.h>
#include <string.h>
#include <ctype.h>
#include <curses.h>
#include <time.h>

#define ANSI_PIROS  "\x1b[31m"
#define ANSI_ZOLD   "\x1b[32m"
#define ANSI_SARGA  "\x1b[33m"
#define ANSI_MAGENTA "\x1b[35m"
#define ANSI_RESET   "\x1b[0m"

#define FILE_NEV "szotar.txt"
#define LEHETOSEGEK_SZAMA 1
#define MAXIMUM_NEV_HOSSZA 10
#define MINIMUM_JATEKOSOK_SZAMA 2
#define MAXIMUM_JATEKOSOK_SZAMA 5
#define MAXIMUM_KIFEJEZES_HOSSZA 100	


/* GLOBÁLIS VÁLTOZÓK */

extern char opcio;
extern bool fut; 
extern unsigned int nyeremeny;
extern unsigned int jatekosok_szama;

extern int* sorrend;
extern int* osszeg;
extern int* lehetosegek;
extern char* nyertes;
extern char** jatekosok;

extern char keresett[MAXIMUM_KIFEJEZES_HOSSZA];
extern char hasonlit[MAXIMUM_KIFEJEZES_HOSSZA];

extern const char kerek[7][10];		// A keréken látható szövegek

/* AZ ALPROGRAMOK DEKLARÁLÁSA */

int clean_stdin();

void kiir_cim();

void kiir_fomenu();

int olvas_szo();

void valaszt();

void olvas_jatekosok_szama();

void olvas_jatekosok_neve();

void inic();

void general_sorrend();

void porget(int n);

void helyes_menu();

void helyes_valaszt(int n);

void helyes_tipp();

void jatek();

void jatek_vege();

#endif
