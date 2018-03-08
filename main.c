#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ctype.h"
#include "map_matriks.h"
#include "recruit.h"
#include "turn.h"
#include "info.h"
#include "change.h"
#include "undo.h"
#include "pcolor.h"
#include "mesinkar.h"
#include "mesinkata.h"
#include "initword.h"
#include "move.h"
#include "attack.h"

Stack S;
MATRIKS M;
POINT Current;
Kata	MOVE, UNDO, CHANGE_UNIT, RECRUIT, ATTACK, MAP, INFO, END_TURN, EXIT, NEXT_UNIT;

int WhoIstheWin(Queue Q);
//F.S get who is the winner

int main() {
	int Row, Col;
	Player P1, P2;
	addrUnit CurrentUnit;
  ListUnit List;
  Queue Q;

	InitializeWord();
  printf("Enter Dimension : ");
  scanf("%d %d", &Col, &Row);
	MakeMATRIKS(Col,Row,&M);
	P1 = StarterPlayer(1, &M);
	P2 = StarterPlayer(2, &M);
  printMap(M);
  MakeTurn(&Q, P1, P2);
	AvailableUnit(&List);
	MovementStorage(&S);

  do {
    PrintStatus(&Q);
		printf("Your input : ");
    STARTKATA();
		printf("\n");
    if (IsKataSama(CKata, RECRUIT)) {
        RecruitUnit(List, &InfoHead(Q), &M);
    } else if (IsKataSama(CKata, MAP)) {
        printMap(M);
    } else if (IsKataSama(CKata, CHANGE_UNIT)) {
        PrintChange(Q, &S);
    } else if (IsKataSama(CKata, MOVE)) {
				Movement(&S, &Q, &M);
    } else if (IsKataSama(CKata, UNDO)) {
				Undo(&S, SearchInfo(Q, Current, PlNumber(InfoHead(Q))), &M, PlNumber(InfoHead(Q)));
		} else if (IsKataSama(CKata, ATTACK)) {
				addrUnit CurrentUnit = SearchInfo(Q, Current, PlNumber(InfoHead(Q)));
				AttackEnemy(&CurrentUnit, Q);
		} else if (IsKataSama(CKata, INFO)) {
        printf("Enter the coordinate of the cell : ");
        scanf("%d %d", &Col, &Row);
        PrintInfo (Q, M, Col, Row);
    } else if (IsKataSama(CKata, NEXT_UNIT)) {
				NextAvailable(Q, &S);
    } else if (IsKataSama(CKata, END_TURN)) {
				NextTurn(&Q, &S);
		} else if (IsKataSama(CKata, EXIT)) {
				printstr_green("See you later!\n");
				exit(0);
		} else {
			printstr_red("Wrong command!\n");
		}
  } while(WhoIstheWin(Q) == 0);

	return 0;
}

int WhoIstheWin(Queue Q)
//mengirimkan 0 jika belum ada player yg menang, mengirim 1 jika player 1 menang, 2 jika player 2 menang
{
    //kamus
    addrUnit P1, P2, Ptrav;
    boolean found1 = false, found2 = false;

    //algoritma
    P1 = FirstUnit(PlUnitList(InfoHead(Q)));
		P2 = FirstUnit(PlUnitList(InfoTail(Q)));
    if (PlNumber(InfoHead(Q)) != 1) {
        P1 = FirstUnit(PlUnitList(InfoTail(Q)));
				P2 = FirstUnit(PlUnitList(InfoHead(Q)));
    }

		if (P1 != Nil) {
			Ptrav = P1;
			do {
					if (UnitType(Ptrav) == 'K') {
							found1 = true;
					}
					Ptrav = NextUnit(Ptrav);
			} while(Ptrav != P1); //unit player 1 sudah selesai ditelusuri
		}


		if (P2 != Nil) {
			Ptrav = P2;
			do {
					if (UnitType(Ptrav) == 'K') {
							found2 = true;
					}
					Ptrav = NextUnit(Ptrav);
			} while(Ptrav != P2); //unit player 2 sudah selesai ditelusuri
		}


    if (found1 && found2) {
			return 0;
		} else if (found1) {
			printstr_green("Player 1 is the winner!\n");
			return 1;
		} else {
			printstr_green("Player 2 is the winner!\n");
			return 2;
		}
}
