#include <stdio.h>
#include "boolean.h"
#include "undo.h"
#include "point.h"
#include "recruit.h"
#include "pcolor.h"
#include "math.h"

POINT Current;

void MovementStorage(Stack *S)
{
  CreateEmptyStack(S);
  Push(S, Current);
}

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmptyStack (Stack *S)
/* I.S. sembarang */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 1.. MaxEl+1 karena 0 tidak dipakai */
/* Ciri stack kosong : TOP bernilai Nil */
{
  Top(*S) = 0;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsCanUndo(Stack S)
/* Mengirim true jika Stack kosong: lihat definisi di atas */
{
  return (Top(S) != 1);
}

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, POINT Po)
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */
{
  Top(*S)++;
  InfoTop(*S) = Po;
  Current = Po;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Undo (Stack * S, addrUnit P, MATRIKS *M, int Number)
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
{
  if (!IsCanUndo(*S)) {
    printstr_red("Can't move back, go attack your enemy!");
  } else {
    SetUnit(M,0,'\0',Absis(Current),Ordinat(Current));
    Top(*S)--;
    Move(P) += ceil(Panjang(Current, InfoTop(*S)));
    Current = InfoTop(*S);
    Location(P) = Current;
    SetUnit(M,Number,UnitType(P),Absis(Current),Ordinat(Current));
  }
}
