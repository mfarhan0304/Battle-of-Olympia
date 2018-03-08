/* File: mesinkata.c */
/* Implementasi Mesin Kata */

#include <stdio.h>
#include "boolean.h"
#include "mesinkata.h"
#include "mesinkar.h"
#include "ctype.h"

boolean	EndKata;
Kata		CKata;

void IgnoreBlank()
/* Mengabaikan satu atau beberapa BLANK
   I.S. : CC sembarang
   F.S. : CC = BLANK atau CC = MARK */
{
	while ((CC==BLANK) || (CC==MARK)) {
		ADV();
	}
}

void STARTKATA()
/* I.S. : CC sembarang
   F.S. : EndKata = true, dan CC = MARK
          atau EndKata = false, CKata adalah kata yang sudah diakuisisi,
          CC karakter pertama sesudah karakter terakhir kata */
{
	START();
	IgnoreBlank();
	if (CC == MARK || CC == BLANK) {
		EndKata = true;
	} else /* CC != MARK */ {
		EndKata = false;
		SalinKata();
	}
}

void SalinKata()
/* Mengakuisisi kata, menyimpan dalam CKata
   I.S. : CC adalah karakter pertama dari kata
   F.S. : CKata berisi kata yang sudah diakuisisi
          CC = BLANK atau CC = MARK
          CC adalah karakter sesudah karakter terakhir yang diakuisisi.
          Jika panjang kata melebihi NMax, maka sisa kata "dipotong" */
{
	int	i = 1;

	for (;;) {
    CKata.TabKata[i] = toupper(CC);
    ADV();
    if ((CC == MARK) || (CC == BLANK) || (i >= NMax)) {
      break;
      if (i > NMax) {
        i--;
      }
    } else {
      i++;
    }
  } /* CC = MARK or CC = BLANK */
  CKata.Length = i;
}

boolean IsKataSama(Kata K1, Kata K2){
	int i;
	boolean check = true;

	if (K1.Length == K2.Length) {
		for (i = 1; i <= K1.Length; i++){
			if (K1.TabKata[i]!= K2.TabKata[i]){
				check = false;
			}
		}
		return check;
	}
	else {
		return false;
	}
}
