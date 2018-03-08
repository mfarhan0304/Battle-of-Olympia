#include <stdio.h>
#include "info.h"
#include "recruit.h"
#include "pcolor.h"

POINT Current;

void PrintInfo(Queue Q, MATRIKS M, int Col, int Row)
//Memberikan info building maupun unit pada koordinat tertentu
{
  char *Type, *Owner;
  addrUnit P;

  printf("== Building Info ==\n");
  if (Building(M, Col, Row).Player == 0) {
    printstr_red("There's no building\n");
  } else {
    switch (Building(M, Col, Row).Type) {
      case 'V' : Type = "Village";
                 break;
      case 'C' : Type = "Castle";
                 break;
      case 'T' : Type = "Tower";
                 break;
    }
    switch (Building(M, Col, Row).Player) {
      case 1 : Owner = "Player 1";
               break;
      case 2 : Owner = "Player 2";
               break;
      case 3 : Owner = "no one";
               break;
    }
    printf("%s\nOwned by %s\n\n", Type, Owner);
  }

  printf("== Unit Info ==\n");

  if (Unit(M, Col, Row).Player == 0) {
    printstr_red("There's no unit\n");
  } else {
    switch (Unit(M, Col, Row).Type) {
      case 'K' : Type = "King";
                 break;
      case 'A' : Type = "Archer";
                 break;
      case 'S' : Type = "Swordsman";
                 break;
      case 'W' : Type = "White Mage";
                 break;
    }

    P = SearchInfo(Q, MakePOINT(Col, Row), Unit(M, Col, Row).Player);

    printf("%s\nOwned by Player %d\n", Type, Unit(M, Col, Row).Player);
    printf("Health %d/%d | ATK %d\n", Health(P), Max_Health(P), Attack(P));
  }
}

addrUnit SearchInfo(Queue Q, POINT Po, int Number)
//Mencari addrUnit player <Number> dengan memanfaatkan koordinat
{
  boolean bFound = false;
  Player P = InfoHead(Q);
  addrUnit Ptrav;

  if (Number != PlNumber(P)) {
    P = InfoTail(Q);
  }

  Ptrav = FirstUnit(PlUnitList(P));
  do {
      if (EQ(Location(Ptrav), Po)) {
          bFound = true;
      } else {
          Ptrav = NextUnit(Ptrav);
      }
  }while ((Ptrav != FirstUnit(PlUnitList(P))) && (!bFound));

  return Ptrav;
}
