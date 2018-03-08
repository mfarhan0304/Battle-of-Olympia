#ifndef attack_H
#define attack_H
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "point.h"
#include "turn.h"



boolean IsAdjacent (addrUnit A,addrUnit D);
//mengembalikan boolean apakah A bersebelahan dengan D

void AttackEnemy (addrUnit *A, Queue Q);
//I.S.  A adr unit yg akan menyerang
//F.S.  ditampilkan unit-unit yg bisa diserang oleh A, jika tidak ada unit yg bisa diserang ditampilkan pesan kesalahan
//      jika ada. akan diminta input unit yg diserang dan A menyerang unit tsbt

void PrintEnemyUnit(Queue Q, ListUnit L, addrUnit A);

void DoAttack (Queue Q, addrUnit *A, addrUnit *D);
//I.S   A adalah address dr unit yang akan menyerang D unit yg akan diserang. D berada dalam cangkupan serangan
//F.S   serangan terjadi dan musuh retaliate

int NbElmtUnit (ListUnit L);

void PrintNameUnit (addrUnit U);

#endif
