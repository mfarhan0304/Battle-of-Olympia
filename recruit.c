#include <stdio.h>
#include <stdlib.h>
#include "recruit.h"
#include "point.h"
#include "map_matriks.h"
#include "turn.h"
#include "pcolor.h"

Stack S;

/****************** PEMBUATAN ListUnit KOSONG ******************/
void CreateEmptyUnit(ListUnit *L)
/* I.S. sembarang             */
/* F.S. Terbentuk ListUnit kosong */
{
  FirstUnit(*L) = Nil;
}


Player StarterPlayer(int Number, MATRIKS * M)
{
  Player P;

  PlNumber(P) = Number;
  PlMoney(P) = 50;
  CreateEmptyUnit(&PlUnitList(P));
  switch (Number) {
    case 1 : SetUnit(M,1,'K',1,NBrsEff(*M)-2);
             InsVFirst(&PlUnitList(P), 'K', MakePOINT(1, NBrsEff(*M)-2));
             break;
    case 2 : SetUnit(M,2,'K',NKolEff(*M)-2,1);
             InsVFirst(&PlUnitList(P), 'K', MakePOINT(NKolEff(*M)-2, 1));
             break;
  }
  PlTVillage(P) = 0;
  PlIncome(P) = 0;
  PlUpkeep(P) = 0;

  return P;
}


/* PROTOTYPE */
/****************** TEST ListUnit KOSONG ******************/
boolean IsEmptyUnit(ListUnit L)
/* Mengirim true jika ListUnit kosong */
{
  return (FirstUnit(L) == Nil);
}


/****************** Manajemen Memori ******************/
addrUnit AlokasiUnit(char C, POINT Po)
/* Mengirimkan addrUnit hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrUnit tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, NextUnit(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
{
  addrUnit P;
  POINT O;

  P = (Unit *) malloc(sizeof(Unit));
  if (P != Nil) {
    switch (C) {
      case 'K' : Max_Health(P) = 50;
                 Attack(P) = 10;
                 Max_Move(P) = 2;
                 Attack_Type(P) = 'M';
                 Price(P) = 0;
                 break;
      case 'A' : Max_Health(P) = 20;
                 Attack(P) = 5;
                 Max_Move(P) = 3;
                 Attack_Type(P) = 'R';
                 Price(P) = 7;
                 break;
      case 'S' : Max_Health(P) = 30;
                 Attack(P) = 7;
                 Max_Move(P) = 2;
                 Attack_Type(P) = 'M';
                 Price(P) = 5;
                 break;
      case 'W' : Max_Health(P) = 15;
                 Attack(P) = 5;
                 Max_Move(P) = 3;
                 Attack_Type(P) = 'M';
                 Price(P) = 10;
                 break;
    }
    UnitType(P) = C;
    Health(P) = Max_Health(P);
    Move(P) = Max_Move(P);
    Attack_Attempt(P) = true;
    Location(P) = Po;
  }

  return P;
}

void DealokasiUnit(addrUnit *P)
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrUnit P */
{
  free(*P);
}


void InsertFirst(ListUnit *L, addrUnit P)
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-addrUnit P sebagai elemen pertama */
{
  addrUnit Last;

  if (IsEmptyUnit(*L)){
    NextUnit(P) = P;
  } else {
    Last = FirstUnit(*L);
    while (NextUnit(Last) != FirstUnit(*L)){
      Last = NextUnit(Last);
    }
    NextUnit(P) = FirstUnit(*L);
    NextUnit(Last) = P;
  }
  FirstUnit(*L) = P;
}

void InsVFirst(ListUnit *L, char C, POINT Po)
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
{
  addrUnit P;

  P = AlokasiUnit(C, Po);
  if (P != Nil) {
    InsertFirst(L,P);
  }
}

///========================Delete dari list========================///
void DelPUnit (ListUnit *L, addrUnit U)
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
{
  addrUnit Pt, Prec;

	Pt = FirstUnit(*L);
	Prec = Nil;
	if (Pt == U && NextUnit(Pt) == FirstUnit(*L)){
		FirstUnit(*L) = Nil;
	} else {
		if (Pt == U){
			DelFirstUnit(L,&Pt);
		} else {
			while (NextUnit(Pt) != FirstUnit(*L) && Pt != U){
				Prec = Pt;
				Pt = NextUnit(Pt);
			}
			if (Pt == U){
				NextUnit(Prec) = NextUnit(NextUnit(Prec));
			}
		}
	}
}

void DelAllUnit (ListUnit *L)
/* Delete semua elemen list dan alamat elemen di-dealokasi */
{
	/*KAMUS*/
	addrUnit P;
	/*ALGORITMA*/
	while (!IsEmptyUnit(*L)) {
		DelFirstUnit(&*L,&P);
		DealokasiUnit(&P);
	}
}

void DelFirstUnit (ListUnit *L, addrUnit *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
	addrUnit Last;

	*P = FirstUnit(*L);
	if (NextUnit(*P) == FirstUnit(*L)){
		FirstUnit(*L) = Nil;
	} else {
		Last = FirstUnit(*L);
		while (NextUnit(Last) != FirstUnit(*L)){
			Last = NextUnit(Last);
		}
		NextUnit(Last) = NextUnit(*P);
		FirstUnit(*L) = NextUnit(*P);
	}
}

void DelAfter (ListUnit *L, addrUnit *Pdel, addrUnit Prec){
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
	*Pdel = NextUnit(Prec);
	NextUnit(Prec) = NextUnit(NextUnit(Prec));
	if(NextUnit(Prec) == Prec){
		FirstUnit(*L) = Prec;
	}
}

void AvailableUnit(ListUnit *L)
{
  CreateEmptyUnit(L);
  InsVFirst(L, 'K', MakePOINT(0, 0));
  InsVFirst(L, 'W', MakePOINT(0, 0));
  InsVFirst(L, 'S', MakePOINT(0, 0));
  InsVFirst(L, 'A', MakePOINT(0, 0));
}

void RecruitUnit(ListUnit L, Player * Pl, MATRIKS * M)
{
  int Row, Col;
  addrUnit P = FirstUnit(L);
  POINT KingPos = SearchKing(*Pl);
  char *Type;
  int i = 1, no;

  if (EQ(Current, KingPos) && (Building(*M, Absis(Current), Ordinat(Current)).Type == 'T') && (Building(*M, Absis(Current), Ordinat(Current)).Player == PlNumber(*Pl))) {
    printf("Enter coordinate of empty castle : ");
    for (;;) {
      scanf("%d %d", &Col, &Row);
      if (IsCanRecruit(*M, Col, Row, PlNumber(*Pl))) {
        MovementStorage(&S);
        break;
      }
      if (IsEmptyBox(*M, Col, Row)) {
        printstr_red("Must put the unit on your own castle!\n");
      } else {
        printstr_red("That castle is occupied!\n");
      }
      printf("Enter other coordinate of empty castle : ");
    }
    printf("\n===List of Recruits===\n");
    while (NextUnit(P) != FirstUnit(L)) {
      Type = UnitName(UnitType(P));
      printf("%d. %s | Health %d | ATK %d | %dG\n", i, Type, Health(P), Attack(P), Price(P));
      P = NextUnit(P);
      i++;
    }

    for(;;) {
      printf("Enter no. of unit you want to recruit : ");
      scanf("%d", &no);
      if(no > 0 && no <i) {
        break;
      }
      printstr_red("Wrong input!\n");
    }
    P = FirstUnit(L);
    for (i = 1; i < no; i++) {
      P = NextUnit(P);
    }
    if (PlMoney(*Pl) < Price(P)) {
      printstr_red("You don't have enough money\n");
    } else {
      PlMoney(*Pl) -= Price(P);
      PlUpkeep(*Pl) += Price(P);

      SetUnit(M,PlNumber(*Pl),UnitType(P),Col,Row);
      InsVFirst(&PlUnitList(*Pl), UnitType(P), MakePOINT(Col, Row));
      Move(FirstUnit(PlUnitList(*Pl))) = 0;
      Type = UnitName(UnitType(P));
      printstr_green("You have recruited ");
      printstr_green(Type);
      printf("\n");
    }
  } else {
    printstr_red("You can't recruit on your current position\n");
  }
}

char* UnitName(char C) {
  switch (C) {
    case 'K' : return "King";
               break;
    case 'A' : return "Archer";
               break;
    case 'S' : return "Swordsman";
               break;
    case 'W' : return "White Mage";
               break;
    default  : return "No Unit";
  }
}
