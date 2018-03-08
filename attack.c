#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include "attack.h"
#include "point.h"
#include "turn.h"
#include "pcolor.h"
#include "undo.h"
#include "info.h"
#include "time.h"
#include "recruit.h"

Stack S;
MATRIKS M;

boolean IsAdjacent (addrUnit A, addrUnit D)
//mengembalikan boolean apakah A bersebelahan dengan D
{
    if (Panjang(Location(A),Location(D))<=1) {
        return true;
    } else {
        return false;
    }
}

void AttackEnemy (addrUnit *A, Queue Q)
//I.S.  A adr unit yg akan menyerang
//F.S.  ditampilkan unit-unit yg bisa diserang oleh A, jika tidak ada unit yg bisa diserang ditampilkan pesan kesalahan
//      jika ada. akan diminta input unit yg diserang dan A menyerang unit tsbt
{
    //kamus lokal
    ListUnit L;
    addrUnit U,D;
    POINT Po;
    int i,in;
    //algoritma
    //Po=MakePOINT (0,0);
    if (Attack_Attempt(*A)) {
    //if (1){
        CreateEmptyUnit(&L);
        U=FirstUnit(PlUnitList(InfoTail(Q)));//curent playernya blm ada variable nya. intinya mau ngasih listunit dari musuhnya
        do {
            if (IsAdjacent(*A,U)) {
                Po=Location(U);
                InsVFirst(&L,UnitType(U),Po);
                //InsertFirst(&L, U);//
            }
            U=NextUnit(U);
        } while (U != FirstUnit(PlUnitList(InfoTail(Q))));//terbentuk list unit" yg bersebelahan dgn A
        if (!IsEmptyUnit(L)) {
            PrintEnemyUnit(Q,L,*A);

            printf("Select enemy you want to attack (type '0' to go back) : ");

            scanf("%d", &in);
            for(;;) {
              if ((in > 0) && (in < NbElmtUnit(L))) {
                break;
              } else if (in == 0) {
                return;
              }
              printstr_red("Wrong input!\n");
              printf("Select enemy : ");
              scanf("%d", &in);
            }

            //in adl indeks unit yg akan diserang
            U=FirstUnit(L);
            for (i=1;i<=NbElmtUnit(L);i++) {
                if (i!=in) {
                    U=NextUnit(U);
                } else {break;}
            }//U copy addrunit yg akan di attack

            Po=Location(U);
            D=SearchInfo(Q, Po, PlNumber(InfoTail(Q)));
            //D adrunit yg ada di list unit musuh
            //D=Search (FirstUnit(PlUnitList(InfoTail(*Q))), (P)->infounit);

            DoAttack (Q, &*A, &D);
            //set movement dan atk attempt
            Attack_Attempt(*A)=false;
            Move(*A)=0;
            MovementStorage(&S);
            DelAllUnit(&L);//supaya ga nyampah
        } else {
            printstr_red ("No enemy unit nearby \n");
        }
    } else {printstr_red ("Can't attack! \n");}
}

void PrintEnemyUnit(Queue Q, ListUnit L, addrUnit A)
{
    addrUnit P,D;
    int i=1;

    P=FirstUnit(L);

    do {
        D=SearchInfo(Q, Location(P), PlNumber(InfoTail(Q)));

        printf("%d. ",i);
        PrintNameUnit (D);
        TulisPOINT (Location(D));
        printf(" | Health %d/%d ",Health(D),Max_Health(D));
        if (Attack_Type(D)==Attack_Type(A) || UnitType(D) == 'K') {printf("(Retaliates)");}
        printf("\n");

        P=NextUnit(P);
        i++;
    } while (P != FirstUnit(L));
}

void DoAttack (Queue Q, addrUnit *A, addrUnit *D)
//I.S   A adalah address dr unit yang akan menyerang D unit yg akan diserang. D berada dalam cangkupan serangan
//F.S   serangan terjadi dan musuh retaliate
{
    //kamus
    int temp;
    int r;

    srand(time(NULL));

    r = rand() % 5;
    //algoritma
    if (r == 0) {
        printstr_red("\nOh no! miss attack!:(\n");
    } else {
        temp=Health(*D);
        Health(*D)=Health(*D)-Attack(*A);

        printf("\nEnemy's ");
        PrintNameUnit (*D);
        printf(" is damaged by %d\n",(temp-Health(*D)));

        if (Health(*D)<=0) {//D mati
            Health(*D)=0;
            //printf("Enemy's %s is damaged by %d\n",UnitType(*D),(temp-Health(*D)));
            //DelPUnit(&PlUnitList(InfoTail(*Q)),&*D);//belom di buat, harusnya ada di list unit
            printf("Enemy's ");
            PrintNameUnit (*D);
            printf(" is dead :D\n");
            Unit(M, Absis(Location(*D)), Ordinat(Location(*D))).Player = 0;//del dr matriks
            Unit(M, Absis(Location(*D)), Ordinat(Location(*D))).Type = '\0';
            DelPUnit (&PlUnitList(InfoTail(Q)), *D);//del dr list musuh
      }
    }

    if ((UnitType(*D)=='K' || Attack_Type(*D)==Attack_Type(*A)) && (Health(*D) > 0)) {//D tdk mati
      //retaliatenya
      printf("Enemy's ");
      PrintNameUnit (*D);
      printf(" retaliates\n");

      r = rand() % 5;
      if (r == 0) {
        printstr_green("Lucky you! Enemy's attack is missing!\n");
      } else {
          temp=Health(*A);
          Health(*A)=Health(*A)-Attack(*D);
          if (Health(*A)<=0) {//A mati
              Health(*A)=0;
              //printf("Your %s is damaged by %d\n",UnitType(*A),(temp-Health(*A)));
              printf("Your ");
              PrintNameUnit (*A);
              printf(" is damaged by %d\n",(temp-Health(*A)));
              //DelPUnit(&PlUnitList(InfoHead(*Q)),&*A);//belom di buat, harusnya ada di list unit
              Unit(M, Absis(Location(*A)), Ordinat(Location(*A))).Player = 0;//del dr matriks
              Unit(M, Absis(Location(*A)), Ordinat(Location(*A))).Type = '\0';
              DelPUnit (&PlUnitList(InfoHead(Q)), *A);
              printf("Your ");
              PrintNameUnit (*A);
              printf(" is dead :(\n");
          } else {
              printf("Your ");
              PrintNameUnit (*A);
              printf(" is damaged by %d\n",(temp-Health(*A)));
          }
      }
    }
}

int NbElmtUnit (ListUnit L)
{
    addrUnit P;
    int i=1;

    P=FirstUnit(L);
    do {
        P=NextUnit(P);
        i++;
    } while (P != FirstUnit(L));
    return i;
}

void PrintNameUnit (addrUnit U)
{
    switch (UnitType(U)) {
        case 'K' : {printf("King");break;}
        case 'S' : {printf("Swordsman");break;}
        case 'A' : {printf("Archer");break;}
        case 'W' : {printf("White Mage");break;}
    }
}
