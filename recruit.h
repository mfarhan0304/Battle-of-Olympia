#ifndef recruit_H
#define recruit_H

#include "boolean.h"
#include "point.h"
#include "map_matriks.h"

#define Nil NULL

typedef struct {
	char UType;
	int Max_Health;
	int Health;
	int Attack;
	int Max_Move;
	int Move;
	char Attack_Type;
	boolean Attack_Attempt;
	POINT Location;
	int Price;
} infoUnit;
typedef struct tUnit *addrUnit;
typedef struct tUnit {
	infoUnit infounit;
	addrUnit nextunit;
} Unit;
typedef struct {
	addrUnit FirstUnit;
} ListUnit;

typedef struct {
	int Number;
  int Money;
	ListUnit Owned_Unit;
	int Total_Village;
	int Income;
	int Upkeep;
} Player;

#define UnitType(P) (P)->infounit.UType
#define Max_Health(P) (P)->infounit.Max_Health
#define Health(P) (P)->infounit.Health
#define Attack(P) (P)->infounit.Attack
#define Max_Move(P) (P)->infounit.Max_Move
#define Move(P) (P)->infounit.Move
#define Attack_Type(P) (P)->infounit.Attack_Type
#define Attack_Attempt(P) (P)->infounit.Attack_Attempt
#define Location(P) (P)->infounit.Location
#define Price(P) (P)->infounit.Price
#define InfoUnit(P) (P)->infounit
#define NextUnit(P) (P)->nextunit
#define FirstUnit(L) (L).FirstUnit

#define PlNumber(I) (I).Number
#define PlMoney(I) (I).Money
#define PlUnitList(I) (I).Owned_Unit
#define PlTVillage(I) (I).Total_Village
#define PlIncome(I) (I).Income
#define PlUpkeep(I) (I).Upkeep

/****************** TEST LIST KOSONG ******************/
boolean IsEmptyUnit (ListUnit L);
/* Mengirim true jika list kosong. Lihat definisi di atas. */

/****************** PEMBUATAN ListUnit KOSONG ******************/
void CreateEmptyUnit (ListUnit *L);
/* I.S. sembarang             */
/* F.S. Terbentuk ListUnit kosong */

Player StarterPlayer(int Number, MATRIKS * M);

void AvailableUnit(ListUnit *L);

/****************** Manajemen Memori ******************/
addrUnit AlokasiUnit (char C, POINT Po);
/* Mengirimkan addrUnit hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrUnit tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokasiUnit (addrUnit *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrUnit P */


void RecruitUnit(ListUnit L, Player * Pl, MATRIKS * M);

char* UnitName (char C);

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (ListUnit *L, char C, POINT Po);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (ListUnit *L, addrUnit P);
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addrUnit P sebagai elemen pertama */

///========================Delete dari list========================///
void DelPUnit (ListUnit *L, addrUnit U);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */

void DelAllUnit (ListUnit *L);

void DelFirstUnit (ListUnit *L, addrUnit *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */

void DelAfter (ListUnit *L, addrUnit *Pdel, addrUnit Prec);
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */

#endif
