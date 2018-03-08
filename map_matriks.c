#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "map_matriks.h"
#include "point.h"
#include "pcolor.h"

MATRIKS M;
POINT Current;

void printCur (char C, int Player) {
	printf("  ");
	if (Player == 0) {
		printf(" ");
	} else {
		print_yellow(C);
	}
	printf("  |");
}

void printChar (char C, int Player) {
	printf("  ");
	switch (Player) {
		case 1 : print_red(C);
						 break;
		case 2 : print_cyan(C);
						 break;
		case 3 : print_green(C);
						 break;
		case 4 : printf("#");
						 break;
		default: printf(" ");
	}
	printf("  |");
}

void SetBuilding(MATRIKS * M, int Number, char newb, int x, int y)
{
	Building(*M,x,y).Type = newb;
	Building(*M,x,y).Player = Number;
	Building(*M,x,y).Place = MakePOINT(x,y);
}

void SetUnit(MATRIKS * M, int Number, char newu, int x, int y)
{
    Unit(*M,x,y).Type = newu;
		Unit(*M,x,y).Player = Number;
		Unit(*M,x,y).Place = MakePOINT(x,y);
}

boolean IsTooNearby(int Col, int Row, int NK, int NB)
{
	if ((Col >= (NK - 5)) && (Row <= 2)) {
		return true;
	} else if ((Row >= (NB - 5)) && (Col <= 2)) {
		return true;
	} else {
		return false;
	}
}

void SetVillage(MATRIKS * M, int NK, int NB)
{
	int x, y, count;

	srand(time(NULL));

	for (count = 0; count < div(NB*NK,20).quot; count++) {
		do {
			x = rand() % NK;
			y = rand() % NB;

			if (!IsTooNearby(x, y, NK, NB)) {
				SetBuilding(M,3,'V',x,y);
			}
		} while(IsTooNearby(x,y,NK,NB));
	}
}

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NK, int NB, MATRIKS * M)
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
{
	int x, y;

	NBrsEff(*M) = NB;
	NKolEff(*M) = NK;

	for (y = 0; y < NBrsEff(*M); y++) {
		for (x = 0; x < NKolEff(*M); x++) {
			Building(*M, x, y).Player = 0;
			Building(*M, x, y).Type = '\0';
			Unit(*M, x, y).Player = 0;
			Unit(*M, x, y).Type = '\0';
		}
	}

	SetVillage(M,NK,NB);

	SetBuilding(M,2,'C',NK-1,1);
	SetBuilding(M,2,'C',NK-2,0);
	SetBuilding(M,2,'T',NK-2,1);
	SetBuilding(M,2,'C',NK-3,1);
	SetBuilding(M,2,'C',NK-2,2);

	SetBuilding(M,1,'C',1,NB-1);
	SetBuilding(M,1,'C',0,NB-2);
	SetBuilding(M,1,'T',1,NB-2);
	SetBuilding(M,1,'C',1,NB-3);
	SetBuilding(M,1,'C',2,NB-2);

	Current = MakePOINT(1, NB-2);
}

void printMap (MATRIKS M) {
	int x, y, ny;

	for (ny = 0; ny < 2; ny++) {
		(ny == 0) ? printf("    ") : printf("   +");
		for (x = 0; x < NKolEff(M); x++) {
			switch (ny) {
				case 0 : (x > 9) ? printf("  %d  ", x) : printf("  %d   ", x);
								 break;
				default: printf("-----+");
			}
		}
		printf("\n");
	}

	for (y = 0; y < NBrsEff(M); y++) {
		for (ny = 0; ny <= 3; ny++) {
			switch (ny) {
				case 1 : (y > 9) ? printf("%d |", y) : printf(" %d |", y);
								 break;
				case 3 : printf("   +");
								 break;
				default: printf("   |");
			}
			for (x = 0; x < NKolEff(M); x++) {
				switch (ny) {
					case 0 : printChar(Building(M,x,y).Type, Building(M,x,y).Player);
									 break;
					case 1 : if (EQ(Current, MakePOINT(x,y))) {
										 printCur(Unit(M,x,y).Type, Unit(M,x,y).Player);
									 } else {
										 printChar(Unit(M,x,y).Type, Unit(M,x,y).Player);
									 }
									 break;
					case 2 : printf("     |");
									 break;
					case 3 : printf("-----+");
									 break;
				}
			}
			printf("\n");
		}
	}
}

boolean IsEmptyBox (MATRIKS M, int Col, int Row) {
	return (Unit(M, Col, Row).Player == 0);
}

boolean IsCanRecruit(MATRIKS M, int Col, int Row, int Number)
{
	return (IsEmptyBox(M, Col, Row) && (Building(M,Col,Row).Player == Number));
}
