/* File : queuelist.h */
/* Representasi queue dengan list berkait dengan first (HEAD) dan last (TAIL) */
#ifndef turn_H
#define turn_H
#include "boolean.h"
#include <stdlib.h>
#include "recruit.h"
#include "undo.h"

/* Konstanta */
#define Nil NULL

/* Queue dengan representasi berkait dengan pointer */
typedef struct tElmtQueue * address;
typedef struct tElmtQueue {
	Player Info;
	address Next;
} ElmtQueue;

/* Type queue dengan ciri HEAD dan TAIL : */
typedef struct {
	address HEAD;  /* alamat penghapusan */
	address TAIL;  /* alamat penambahan */
} Queue;

/* Selektor */
#define Head(Q) (Q).HEAD
#define Tail(Q) (Q).TAIL
#define InfoHead(Q) (Q).HEAD->Info
#define InfoTail(Q) (Q).TAIL->Info
#define NextPlayer(P) (P)->Next
#define InfoPlayer(P) (P)->Info

void HealingMage(Queue * Q);

void ChangeStatus(Queue * Q, Player * Pl);

POINT SearchKing(Player Pl);

void MakeTurn(Queue * Q, Player P1, Player P2);

boolean IsNextTurn(Queue Q);

void NextTurn(Queue * Q, Stack * S);

void RefreshStatus(Player * Pl);

void PrintStatus(Queue * Q);

/* Prototype manajemen memori */
void AlokasiTurn (address *P, Player X);
/* I.S. Sembarang */
/* F.S. Alamat P dialokasi, jika berhasil maka Info(P)=X dan
        Next(P)=Nil */
/*      P=Nil jika alokasi gagal */
void DealokasiTurn (address  P);
/* I.S. P adalah hasil alokasi, P != Nil */
/* F.S. Alamat P didealokasi, dikembalikan ke sistem */
boolean IsEmptyTurn (Queue Q);
/* Mengirim true jika Q kosong: HEAD(Q)=Nil and TAIL(Q)=Nil */
void CreateEmptyTurn(Queue * Q);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk */
/*** Primitif Add/Delete ***/
void AddTurn (Queue * Q, Player X);
/* Proses: Mengalokasi X dan menambahkan X pada bagian TAIL dari Q
   jika alokasi berhasil; jika alokasi gagal Q tetap */
/* Pada dasarnya adalah proses insert last */
/* I.S. Q mungkin kosong */
/* F.S. X menjadi TAIL, TAIL "maju" */
void DelTurn(Queue * Q, Player * X);
/* Proses: Menghapus X pada bagian HEAD dari Q dan mendealokasi
   elemen HEAD */
/* Pada dasarnya operasi delete first */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "mundur" */

#endif
