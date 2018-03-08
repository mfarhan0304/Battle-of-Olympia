/* ********** Definisi TYPE MATRIKS dengan indeks dan elemen integer ********** */

#ifndef MATRIKS_H
#define MATRIKS_H

#include "boolean.h"
#include "point.h"

/* Ukuran minimum dan maksimum baris dan kolom */
#define BrsMin 8
#define BrsMax 100
#define KolMin 8
#define KolMax 100

extern POINT Current;

typedef int indeks; /* indeks baris, kolom */
typedef struct {
	int Player;
	char Type;
	POINT Place;
} Stat;
typedef struct {
	Stat Building;
	Stat Unit;
} ElType;
typedef struct {
	ElType Mem[BrsMax+1][KolMax+1];
    int NBrsEff; /* banyaknya/ukuran baris yg terdefinisi */
	int NKolEff; /* banyaknya/ukuran kolom yg terdefinisi */
} MATRIKS;

/* NBrsEff <= 1 dan NKolEff <= 1 */
/* Indeks matriks yang digunakan: [BrsMin..BrsMax][KolMin..KolMax] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* *** Selektor *** */
#define NBrsEff(M) (M).NBrsEff
#define NKolEff(M) (M).NKolEff
#define Building(M,i,j) (M).Mem[(i)][(j)].Building
#define Unit(M,i,j) (M).Mem[(i)][(j)].Unit

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M);
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */

void SetBuilding(MATRIKS* M, int Number, char newb, int r, int c);

void SetUnit(MATRIKS* M, int Number, char ubaru, int i, int j);
/* Membentuk unit baru */

boolean IsTooNearby(int Col, int Row, int NK, int NB);

void SetVillage(MATRIKS*M, int NB, int NK);

void printMap (MATRIKS M);

void printChar (char C, int Player);

boolean IsEmptyBox (MATRIKS, int Row, int Col);

boolean IsCanRecruit(MATRIKS M, int Col, int Row, int Number);

#endif
