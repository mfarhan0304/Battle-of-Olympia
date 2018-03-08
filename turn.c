#include <stdio.h>
#include "boolean.h"
#include <stdlib.h>
#include "turn.h"
#include "info.h"
#include "undo.h"
#include "pcolor.h"

MATRIKS M;
POINT Current;

void HealingMage(Queue * Q)
{
  for(int Row = Ordinat(Current) - 1; Row <= Ordinat(Current) + 2; Row++) {
    for(int Col = Absis(Current) - 1; Col <= Absis(Current) + 2; Col++) {
      if ((Col >= 0) || (Col < NKolEff(M)) || (Row >= 0) || (Row < NBrsEff(M))) { //not out of available matrices
        if (Unit(M,Col,Row).Player == PlNumber(InfoHead(*Q))) {
          addrUnit P = SearchInfo(*Q, MakePOINT(Col, Row), PlNumber(InfoHead(*Q)));
          ((Health(P) + 2) > Max_Health(P)) ? (Health(P) = Max_Health(P)): (Health(P) += 2);
        }
      }
    }
  }
}

void ChangeStatus(Queue *Q, Player * Pl)
{
  int sum = 0;
  addrUnit P = FirstUnit(PlUnitList(*Pl));

  if (UnitType(P) == 'W') {
    HealingMage(Q); //Healing with mage
  }

  PlMoney(*Pl) += (PlIncome(*Pl) - PlUpkeep(*Pl));
}

POINT SearchKing(Player P)
{
  boolean bFound = false;
  addrUnit Ptrav;

  Ptrav = FirstUnit(PlUnitList(P));
  do {
      if (UnitType(Ptrav) == 'K') {
          bFound = true;
      } else {
          Ptrav = NextUnit(Ptrav);
      }
  } while ((Ptrav != FirstUnit(PlUnitList(P))) && (!bFound));

  return Location(Ptrav);
}

void MakeTurn(Queue * Q, Player P1, Player P2)
{
	CreateEmptyTurn(Q);
	AddTurn(Q, P1);
	AddTurn(Q, P2);
}

void NextTurn(Queue * Q, Stack * S)
{
	Player NextP;

  ChangeStatus(Q, &InfoHead(*Q));
	DelTurn(Q, &NextP);
	Current = SearchKing(InfoTail(*Q));
  MovementStorage(S);
	AddTurn(Q, NextP);
  RefreshStatus(&NextP);
}

void RefreshStatus(Player * Pl)
{
  addrUnit P = FirstUnit(PlUnitList(*Pl));

  do {
    Attack_Attempt(P) = true;
    Move(P) = Max_Move(P);
    P = NextUnit(P);
  } while(P != FirstUnit(PlUnitList(*Pl)));
}

void PrintStatus(Queue * Q)
{
	char *Type, *can;
	Player Pl = InfoHead(*Q);
	addrUnit P = SearchInfo(*Q, Current, PlNumber(Pl));

	printf("\nPlayer %d's Turn\n", PlNumber(Pl));
	printf("Cash : %dG | Income : %dG | Upkeep : %dG\n", PlMoney(Pl), PlIncome(Pl), PlUpkeep(Pl));
	Type = UnitName(UnitType(P));

	printf("Unit : %s (%d,%d) | ", Type, Absis(Location(P)), Ordinat(Location(P)));
	printf("Health : %d/%d | ", Health(P), Max_Health(P));
	printf("Movement Point : %d | ", Move(P));
	printf("Can Attack : ");
  if (Attack_Attempt(P)) {
    printstr_green("Yes\n");
  } else {
    printstr_red("No\n");
  }

}

/* Prototype manajemen memori */
void AlokasiTurn(address *P, Player X)
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
{
	*P = (address) malloc (sizeof(ElmtQueue));
	if (*P != Nil) {
		InfoPlayer(*P) = X;
		NextPlayer(*P) = Nil;
	} else {
		*P = Nil;
	}
}

void DealokasiTurn(address  P)
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
{
	free(P);
}

boolean IsEmptyTurn(Queue Q)
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
{
	return (Head(Q)==Nil && Tail(Q) == Nil);
}


/*** Kreator ***/
void CreateEmptyTurn(Queue * Q)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
{
	Head(*Q) = Nil;
	Tail(*Q) = Nil;
}

/*** Primitif Add/Delete ***/
void AddTurn(Queue * Q, Player X)
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
{
	address P;

	AlokasiTurn(&P, X);
	if (P != Nil) {
		if (IsEmptyTurn(*Q)) {
			Head(*Q) = P;
		} else {
			NextPlayer(Tail(*Q)) = P;
		}
		Tail(*Q) = P;
	}
}

void DelTurn(Queue * Q, Player * X)
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */
{
	address P;

	*X = InfoHead(*Q);
	P = Head(*Q);
	Head(*Q) = NextPlayer(P);
	if (Head(*Q) == Nil) {
		Tail(*Q) = Nil;
	}
	DealokasiTurn(P);
}
