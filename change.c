#include <stdio.h>
#include "change.h"
#include "point.h"
#include "info.h"
#include "undo.h"
#include "pcolor.h"

POINT Current;

void NextAvailable(Queue Q, Stack * S)
{
	Player Pl = InfoHead(Q);
	addrUnit P = SearchInfo(Q, Current, PlNumber(Pl));
  boolean bFound = false;

	do {
		P = NextUnit(P);
    if ((Attack_Attempt(P)) || (Move(P) > 0)) {
      bFound = true;
    }
	} while((NEQ(Current, Location(P))) && (!bFound));

  if (bFound && NEQ(Current, Location(P))) {
      Current = Location(P);
      MovementStorage(S);
  } else {
    printstr_red("There's no other unit that can attack or move\n");
  }
}

void PrintChange(Queue Q, Stack *S)
{
  int i = 1, no;
	char *Type, *can;
  POINT storage[20];
	Player Pl = InfoHead(Q);
	addrUnit P = FirstUnit(PlUnitList(Pl));

	printf("== List of Units ==\n");
	do {
    if (!EQ(Current, Location(P))) {
      Type = UnitName(UnitType(P));
  		if (Attack_Attempt(P)) {
  			can = "Yes";
  		} else {
  			can = "No";
  		}
  		printf("%d. %s (%d,%d) | Health : %d\n", i, Type, Absis(Location(P)), Ordinat(Location(P)), Health(P));
      storage[i] = Location(P);
      i++;
    }
		P = NextUnit(P);
	} while(P != FirstUnit(PlUnitList(Pl)));

  printf("Please enter the no. of unit you want to select : ");
  scanf("%d", &no);
  Current = storage[no];
  MovementStorage(S);
  P = SearchInfo(Q, Current, PlNumber(Pl));
  Type = UnitName(UnitType(P));
  printstr_green("You're now selecting ");
  printstr_green(Type);
  printf("\n");
}
