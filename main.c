#include "szerencsekerek.h"

/* FŐPROGRAM */

int main() {

	srand(time(NULL));

	kiir_cim();

	kiir_fomenu();

	if (olvas_szo()) {		// Ha nem sikerül olvasni a fájlból, a program kilép

		printf(ANSI_PIROS	"HIBA a fájl olvasása során!\n"		ANSI_RESET);
		exit(1);

	} else {

		valaszt();
	}

	return 0;
}
