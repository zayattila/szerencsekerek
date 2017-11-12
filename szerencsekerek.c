#include "szerencsekerek.h"

char opcio;
bool fut = true; 
unsigned int nyeremeny = 0;
unsigned int jatekosok_szama = 0;

int* sorrend;
int* osszeg;
int* lehetosegek;
char* nyertes;
char** jatekosok;

char keresett[MAXIMUM_KIFEJEZES_HOSSZA];
char hasonlit[MAXIMUM_KIFEJEZES_HOSSZA];

const char kerek[7][10] = {"Csőd", "Passz", "Újra", "1000", "5000", "10000", "20000"};	

/* AZ ALPROGRAMOK DEFINÍCIÓI */

int clean_stdin() {		// A sortörő karakter keresése

    while (getchar()!='\n');

 	return 1;
}

void kiir_cim() {			// A játék címének kiírása

	system("clear");
	printf("   _____                                     _              __ _    \n");
	printf("  / ____|                                   | |            /_/| |   \n");
	printf(" | (___ _______ _ __ ___ _ __   ___ ___  ___| | _____ _ __ ___| | __\n");
	printf("  \\___ \\_  / _ \\ '__/ _ \\ '_ \\ / __/ __|/ _ \\ |/ / _ \\ '__/ _ \\ |/ /\n");
	printf("  ____) / /  __/ | |  __/ | | | (__\\__ \\  __/   <  __/ | |  __/   < \n");
	printf(" |_____/___\\___|_|  \\___|_| |_|\\___|___/\\___|_|\\_\\___|_|  \\___|_|\\_\\\n");
	printf("\n");
}

void kiir_fomenu() {		// A főmenű kiírása

	fflush(stdin);
	printf("Kérlek válassz!\n");
    printf("\n[1] Játék\n");
   	printf("[2] Leírás\n");
    printf("[x] Kilépés\n");
    printf("\n");

	do {						

    	opcio = getchar();		// Opció beolvasása, a whitespaceket skippelve 
    } while (isspace(opcio));
  
}

int olvas_szo() {		// A kifejezés beolvasása és nagybetűssé változtatása a helyes összehasonlítás érdekében

	FILE *fin;

	if ((fin = fopen(FILE_NEV, "r")) == NULL) {		// Nem sikerült a fájl megnyitása

		return 1;

	} else {											// Sikerült a fájl megnyitása, a kifejezés beolvasása

		fscanf(fin,"%[^\n]", keresett);

		strcpy(hasonlit, keresett);						// Új sztring létrehozása a nagybetűssé alakításhoz, így a játék végén pontosan a keresett kifejezést írhatjuk a képernyőre, nem az átalakítottat

		for (int i = 0; i < strlen(hasonlit); ++i) {		

			hasonlit[i] = toupper((unsigned char)hasonlit[i]);		// Nagybetűssé alakítás

		}

		return 0; 
	}

	fclose(fin);
}

void valaszt() {			// Navigálás a főmenüben			

	switch (opcio) {

			case '1' :			// Játék

				fut = true;			// Új játék során a cilusnak ismét futnia kell
				jatek();
				break;	 

			case '2' :			// Leírás

				printf("Üdvözlünk a Szerencserék játékban!\nA játékot %d - %d játékos játszhatja. Véletlenszerűen sorsoljuk ki a pörgetés sorrendjét. A kereken a következőket láthatjátok:\n\n", MINIMUM_JATEKOSOK_SZAMA, MAXIMUM_JATEKOSOK_SZAMA);
				printf(">   Csőd: az adott játékos elveszíti az addig gyűjtött pénzét, nem mondhat betűt és a következő játékos forgathat.\n");
				printf(">   Passz: az adott játékos nem veszíti el a pénzét, de nem is mondhat betűt és a következő játékos forgathat.\n");
				printf(">   Újra: ismét az adott játékos forgat.\n");
				printf(">   Szám: az adott játékos mondhat egy betűt, és ha a betű szerepel a kitalálandó kifejezésben (és még nem volt), akkor a játékos megkapja az összeget,amely után vagy újra forgat "); 
				printf("vagy rákérdez a megoldásra. Ha nem találta el az adott betűt, vagy rákérdezett, de nem találta el a megfejtendő kifejezést, akkor a következő játékos forgathat. Ha megfejtette, akkor ő nyert, és vége a játéknak.\n\n");
				printf("A keresendő kifejezést a %s fájl első sorában kell megadni, a kifejezés whitespaceket NEM tartalmazhat.\n", FILE_NEV);
				fflush(stdin);
				printf("Kérlek válassz!\n");
				printf("\n");
   				printf("\n[1] Játék\n");
 				printf("[x] Kilépés\n");

 				do {

    				opcio = getchar();			// Opció beolvasása, a karakterek skippelésével
                } while (isspace(opcio));

                if (opcio == '1') {			// Játék

                	jatek();
                }

				break;

			case 'x' :						// Kilépés

				fut = false;
				break;

			default :			// Érvénytelen karakter

				printf(ANSI_PIROS	"HIBA: Érvénytelen karakter!\n"	ANSI_RESET);
				break;
	}
}

void var() {			// Az Enter lenyomására váró alprogram, néha két Entert vár, debugolni nem sikerült


	printf("Nyomj Entert a folytatáshoz...");

	while(!clean_stdin());

	getchar();
}

void olvas_jatekosok_szama() {			// A játékosok számának beolvasása

	bool ok = false;

	char c;

	while (!ok) {							// Az input helyességének ellenőrzése

		do {

			printf("\nKérem a játékosok számát! (%d és %d között) ", MINIMUM_JATEKOSOK_SZAMA,MAXIMUM_JATEKOSOK_SZAMA);

		} while ((scanf("%d%c", &jatekosok_szama, &c) != 2 || c != '\n') && clean_stdin());		// Amíg az input nem int típusú

		printf("\n\n");

		if (jatekosok_szama >= MINIMUM_JATEKOSOK_SZAMA && jatekosok_szama <= MAXIMUM_JATEKOSOK_SZAMA) {		// Az input megfelelő

			ok = true;;

		} else if (jatekosok_szama < MINIMUM_JATEKOSOK_SZAMA) {		

			printf(ANSI_PIROS	"HIBA: a játékosok száma túl kevés!\n"	ANSI_RESET);			// Az input túl kicsi

		} else {	

			printf(ANSI_PIROS 	"HIBA: a játékosok száma túl sok!\n"	ANSI_RESET);			// Az input túl nagy
		}

	}
}

void olvas_jatekosok_neve() {			// A játékosok nevének beolvasása

	jatekosok = malloc(jatekosok_szama * sizeof(char*));		// A tömb helyfoglalása

	for (int i = 0; i < jatekosok_szama; ++i) {

		jatekosok[i] = malloc(MAXIMUM_NEV_HOSSZA + 1 * sizeof(char)); 		// A sztring helyfoglalása

		printf("Az %d. játékos neve: ", i+1);
		scanf("%s", jatekosok[i]);
	}
}

void inic() {			// Helyfoglalás és inicializálás

	osszeg = malloc(jatekosok_szama * sizeof(int));

	lehetosegek = malloc(jatekosok_szama * sizeof(int));

	for (int i = 0; i < jatekosok_szama; ++i) {

			osszeg[i] = 0;
			lehetosegek[i] = LEHETOSEGEK_SZAMA;		
	}
} 

void general_sorrend() {			// A pörgetési sorrend generálása

	int i;

	int tmp;

	sorrend = malloc(jatekosok_szama * sizeof(int));	// A tömb helyfoglalása

	for (i = 0; i < jatekosok_szama; ++i) {				

		sorrend[i] = i;									// A tömb inicializálása
	}

	for (i = jatekosok_szama-1; i > 0; --i) {			

		int j = rand() % (i+1);							// A véletlenszerű sorrend generálása
		tmp = sorrend[i];
		sorrend[i] = sorrend[j];
		sorrend[j] = tmp;
	}

	printf("\nA generált pörgetési sorrend:\n\n");		// A sorrend kiiratása

	for (i = 0; i < jatekosok_szama; ++i) {

		for (int j = 0; j < jatekosok_szama; ++j) {

			if (sorrend[j] == i) {	

				printf("%d. %s\n", i+1, jatekosok[j]);
			}
		}
	}
}

void porget(int n) {			// A pörgetés szimulációja, a játékos sorszámát adjuk át

	char tipp;
	unsigned int p = rand() % 7;			// A pörgetés sorszámát tároló változó

	printf(ANSI_ZOLD "\n%s" ANSI_RESET " pörget.\n\n", jatekosok[n]);
	printf(ANSI_ZOLD "%d" ANSI_RESET " lehetőséged van még.\n", lehetosegek[n]);
	printf("Jelenlegi egyenleged:" ANSI_ZOLD " %d " ANSI_RESET "FT\n\n", osszeg[n]);

	var();

	printf("\nA kerék forog...\n");

	printf("\n%s pörgetése: ", jatekosok[n]);

	switch (p) {							// Az esetek kezelése

		case 0:									// Csőd

			printf(ANSI_PIROS	"Csőd\n" ANSI_RESET);
			osszeg[n] = 0;
			break;

		case 1:									// Passz

			printf(ANSI_SARGA	"Passz\n" ANSI_RESET);
			break;

		case 2:									// Újra

			printf(ANSI_MAGENTA	"Újra\n" ANSI_RESET);
			porget(n);
			break;

		default:								// Szám

			lehetosegek[n]--;						// A játékos fentmaradó lehetőségeinek csökkentése

			printf(ANSI_ZOLD	"%s FT\n\n"	ANSI_RESET, kerek[p]);
			printf("Melyik karakter szerepelhet a kifejezésben? ");

			do {									

				tipp = getchar();					// A tippelt karakter beolvasása a whitespaceket skippelve
			} while (isspace(tipp));

			tipp = toupper((unsigned char)tipp);

			if (strchr(hasonlit, tipp) == NULL) {		// Helytelen tipp

				printf(ANSI_PIROS	"\nEz a karakter sajnos nem szerepel a kifejezésben.\n"	ANSI_RESET);

			} else {									// Helyes tipp, az összeget int-é alakítjuk és hozzáadjuk a játékos eddig szerzett pénzéhez

				osszeg[n] += atoi(kerek[p]);
				helyes_tipp(n);
			}

			break;

	}
}

void helyes_tipp(int n) {		// Helyes karakter tippelése esetén lefutó alprogram, a játékos sorszámát adjuk át

	char szotipp[100];				// A tippelt szót tároló sztring

	fflush(stdin);

	printf(ANSI_ZOLD	"\n\nEz a betű szerepel a kifejezésben!\n\n"		ANSI_RESET);
	printf("Kérlek válassz!\n\n");

	if (lehetosegek[n] > 0) {

    	printf("[1] Újra pörgetek\n");
   		printf("[2] Megtippelem a megoldást\n\n");

   } else {							// Ha a játékosnak nincs több lehetősége, nem pörgethet már újra

   		printf("[ ] Nem pörgethetsz már újra, sajnos nincs több lehetőséged.\n");
   		printf("[2] Megtippelem a megoldást\n");
   }
   	
   	opcio = ' ';

   	do {							

    	opcio = getchar();			// Opciü beolvasása a whitespacek skippelésével
    } while (isspace(opcio));	

	switch (opcio) {				// Az esetek kezelése

		 case '1' :						// Újra pörget

		 	if (lehetosegek[n] > 0) {
			
				porget(n);
			}
			break;	 

		case '2' :						// Megtippeli a keresett kifejezést

			printf("A keresett kifejezés: ");
			scanf("%s", szotipp);

			for (int i = 0; i < strlen(szotipp); ++i) {			 

				szotipp[i] = toupper((unsigned char) szotipp[i]);		// Nagybetűssé alakítja a tippelt szót
			}

			if (!strcmp(szotipp,hasonlit)) {					// Helyes tipp, megnyerte a játékot

				printf(ANSI_ZOLD	"\nGratulálok, megnyerted a játékot!\n"	ANSI_RESET);

				nyertes = malloc(strlen(jatekosok[n]) +1);
				strcpy(nyertes, jatekosok[n]);

				nyeremeny = osszeg[n];

				fut = false;

			} else {											// Helytelen tipp

				printf(ANSI_PIROS	"\n1Sajnos nem ez a megoldás.\n"	ANSI_RESET);
			}

			break;

		default :						// Érvénytelen karakter

			printf(ANSI_PIROS	"HIBA: Érvénytelen karakter!\n"	ANSI_RESET);
			break;
	} 
}

void jatek() {				// A játékot indító alprogram

	int i;

	olvas_szo();

	olvas_jatekosok_szama();
	olvas_jatekosok_neve();

	inic();

	general_sorrend();

	while (fut) {			// A futást kezelő ciklus

		for (i = 0; i < jatekosok_szama; ++i) {				// A sorrendet kezelő ciklus				

			for (int j = 0; j < jatekosok_szama; ++j) {			// A jelenlegi sorszámmal rendelkező játékost kereső ciklus

				if (sorrend[j] == i && lehetosegek[j] > 0) {		// Ha a játékosnak maradt még lehetősége

					porget(j);

					if (!fut) break;
				}
			}

			if (!fut) {

				break;
			}
		} 

		if (!nyertes) {		// Ha nincs meg a nyertes, megvizsgálja, hogy van-e még olyan játékos, akinek maradt lehetősége
	
			i = 0;

			fut = false;

			while (!fut && i < jatekosok_szama) {

				if (lehetosegek[i]) {

					fut = true;		// Ha maradt valakinek lehetősége, újra pörgethet
				}

				++i;
			}

		}
	}

	jatek_vege();
}

void jatek_vege() { 			// A játék végén megjelenő menü

	printf(ANSI_ZOLD	"\nA játék véget ért.\n"		ANSI_RESET );
	
	if (nyertes) {					// Volt nyertes

		printf("\nA játék nyertese " ANSI_ZOLD	"%s"	ANSI_RESET " volt, nyereménye: " ANSI_ZOLD	"%d FT\n\n\n" ANSI_RESET, nyertes,nyeremeny);

	} else {						// Nem volt nyertes

		printf(ANSI_PIROS	"A játéknak nem volt nyertese.\n\n"	ANSI_RESET);
		printf(ANSI_MAGENTA "A keresett kifejezés a következő volt: %s\n" ANSI_RESET, keresett);
	}

	var();

	opcio = ' ';	// Az opció resetelése

	/* MEMÓRIA FELSZABADÍTÁSA */

	free(osszeg);
	free(sorrend);
	free(jatekosok);
	free(lehetosegek);
	free(nyertes);

	fflush(stdin);
	printf("Kérlek válassz!\n\n");
    printf("[1] Új játék\n");
   	printf("[2] Leírás\n");
    printf("[x] Kilépés\n");
    printf("\n");

 	do {

    	opcio = getchar();			// Opció beolvasása, a karakterek skippelésével
    } while (isspace(opcio));

	valaszt();
}


