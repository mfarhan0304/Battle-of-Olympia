#include <stdio.h>
#include "move.h"
#include "map_matriks.h"
#include "point.h"
#include "math.h"
#include "turn.h"
#include "info.h"
#include "pcolor.h"

POINT Current;

void Movement(Stack *S, Queue *Q, MATRIKS *M)
{
  int Col, Row;
  addrUnit P = SearchInfo(*Q, Current, PlNumber(InfoHead(*Q)));

  if (Move(P) == 0) {
    printstr_red("You can't move again!\n");
  } else {
    MovementGuide(Max_Move(P), PlNumber(InfoTail(*Q)), Move(P), M, Current);
    printMap(*M);

    printf("Please enter cell's coordinate X Y : ");
    for(;;) {
      scanf("%d %d", &Col, &Row);
      if (Unit(*M, Col, Row).Player == 4) {
        break;
      }
      printstr_red("You can't move there!\n");
      printf("Please enter another cell's coordinate X Y : ");
    }

    SetUnit(M, 0, ' ', Absis(Current), Ordinat(Current));
    SetUnit(M, PlNumber(InfoHead(*Q)), UnitType(P), Col, Row);
    printstr_green("You have successfully moved to ");
    if (Building(*M, Col, Row).Type == 'V') {
      Move(P) = 0;
      ((Health(P) + 3) > Max_Health(P)) ? (Health(P) == Max_Health(P)): (Health(P) += 3);
      Current = MakePOINT(Col,Row);
      MovementStorage(S);
      if (Building(*M, Col, Row).Player != PlNumber(InfoHead(*Q))) { //Village bukan punya player terkini
        if (Building(*M, Col, Row).Player == PlNumber(InfoTail(*Q))) {//Village bukan village bebas
          PlTVillage(InfoTail(*Q)) -= 1;
          PlIncome(InfoTail(*Q)) = 2*PlTVillage(InfoTail(*Q));
        }
        PlTVillage(InfoHead(*Q)) += 1;
        SetBuilding(M, PlNumber(InfoHead(*Q)), 'V', Col, Row);
      }
    } else {
      Move(P) -= ceil(Panjang(Current, MakePOINT(Col, Row)));
      Push(S, MakePOINT(Col, Row));
    }
    PlIncome(InfoHead(*Q)) = 2*PlTVillage(InfoHead(*Q));
    Location(P) = Current;
    TulisPOINT(Current);
    printf("\n");
    MakeMapNormal(M);
  }
}

void MovementGuide(int Max_Move, int Number, int MovePoints, MATRIKS * M, POINT Po) //Number = NextPlayerID
{
  int Col = Absis(Po);
  int Row = Ordinat(Po);

  if ((MovePoints < 0) || (Col < 0) || (Col >= NKolEff(*M)) || (Row < 0) || (Row >= NBrsEff(*M))) { //basis

  } else {
    if (IsEmptyBox(*M, Col, Row) && IsInRange(Po, Max_Move)) {
      Unit(*M, Col, Row).Player = 4; //set '#'
    }
    MovePoints--;
    if (Unit(*M, Col + 1, Row).Player != Number) {
      MovementGuide(Max_Move, Number, MovePoints, M, MakePOINT(Col + 1, Row));
    }
    if (Unit(*M, Col, Row + 1).Player != Number) {
      MovementGuide(Max_Move, Number, MovePoints, M, MakePOINT(Col, Row + 1));
    }
    if (Unit(*M, Col - 1, Row).Player != Number) {
      MovementGuide(Max_Move, Number, MovePoints, M, MakePOINT(Col - 1, Row));
    }
    if (Unit(*M, Col, Row - 1).Player != Number) {
      MovementGuide(Max_Move, Number, MovePoints, M, MakePOINT(Col, Row - 1));
    }
  }
}

boolean IsInRange (POINT Po, int Max_Move)
{
  return (Panjang(Current, Po) <= Max_Move);
}

void MakeMapNormal(MATRIKS *M)
{
  for (int y = 0; y < NBrsEff(*M); y++) {
		for (int x = 0; x < NKolEff(*M); x++) {
      if (Unit(*M, x, y).Player == 4) {
        Unit(*M, x, y).Player = 0;
      }
		}
  }
}
