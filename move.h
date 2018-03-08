#ifndef _MOVE_H
#define _MOVE_H

#include "map_matriks.h"
#include "point.h"
#include "boolean.h"
#include "turn.h"

void Movement(Stack *S, Queue *Q, MATRIKS *M);

void MovementGuide(int Max_Move, int Number, int MovePoints, MATRIKS * M, POINT Po);

boolean IsInRange (POINT Po, int Max_Move);

void MakeMapNormal(MATRIKS *M);

#endif
