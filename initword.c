#include "initword.h"
#include "mesinkata.h"

Kata		MOVE, UNDO, CHANGE_UNIT, RECRUIT, ATTACK, MAP, INFO, END_TURN, EXIT, NEXT_UNIT;

void InitializeWord() {
  MOVE.Length = 4;
  MOVE.TabKata[1] = 'M';
  MOVE.TabKata[2] = 'O';
  MOVE.TabKata[3] = 'V';
  MOVE.TabKata[4] = 'E';

  UNDO.Length = 4;
  UNDO.TabKata[1] = 'U';
  UNDO.TabKata[2] = 'N';
  UNDO.TabKata[3] = 'D';
  UNDO.TabKata[4] = 'O';

  CHANGE_UNIT.Length = 11;
  CHANGE_UNIT.TabKata[1] = 'C';
  CHANGE_UNIT.TabKata[2] = 'H';
  CHANGE_UNIT.TabKata[3] = 'A';
  CHANGE_UNIT.TabKata[4] = 'N';
  CHANGE_UNIT.TabKata[5] = 'G';
  CHANGE_UNIT.TabKata[6] = 'E';
  CHANGE_UNIT.TabKata[7] = '_';
  CHANGE_UNIT.TabKata[8] = 'U';
  CHANGE_UNIT.TabKata[9] = 'N';
  CHANGE_UNIT.TabKata[10] = 'I';
  CHANGE_UNIT.TabKata[11] = 'T';

  RECRUIT.Length = 7;
  RECRUIT.TabKata[1] = 'R';
  RECRUIT.TabKata[2] = 'E';
  RECRUIT.TabKata[3] = 'C';
  RECRUIT.TabKata[4] = 'R';
  RECRUIT.TabKata[5] = 'U';
  RECRUIT.TabKata[6] = 'I';
  RECRUIT.TabKata[7] = 'T';

  ATTACK.Length = 6;
  ATTACK.TabKata[1] = 'A';
  ATTACK.TabKata[2] = 'T';
  ATTACK.TabKata[3] = 'T';
  ATTACK.TabKata[4] = 'A';
  ATTACK.TabKata[5] = 'C';
  ATTACK.TabKata[6] = 'K';

  MAP.Length = 3;
  MAP.TabKata[1] = 'M';
  MAP.TabKata[2] = 'A';
  MAP.TabKata[3] = 'P';

  INFO.Length = 4;
  INFO.TabKata[1] = 'I';
  INFO.TabKata[2] = 'N';
  INFO.TabKata[3] = 'F';
  INFO.TabKata[4] = 'O';

  END_TURN.Length = 8;
  END_TURN.TabKata[1] = 'E';
  END_TURN.TabKata[2] = 'N';
  END_TURN.TabKata[3] = 'D';
  END_TURN.TabKata[4] = '_';
  END_TURN.TabKata[5] = 'T';
  END_TURN.TabKata[6] = 'U';
  END_TURN.TabKata[7] = 'R';
  END_TURN.TabKata[8] = 'N';


  EXIT.Length = 4;
  EXIT.TabKata[1] = 'E';
  EXIT.TabKata[2] = 'X';
  EXIT.TabKata[3] = 'I';
  EXIT.TabKata[4] = 'T';

  NEXT_UNIT.Length = 9;
  NEXT_UNIT.TabKata[1] = 'N';
  NEXT_UNIT.TabKata[2] = 'E';
  NEXT_UNIT.TabKata[3] = 'X';
  NEXT_UNIT.TabKata[4] = 'T';
  NEXT_UNIT.TabKata[5] = '_';
  NEXT_UNIT.TabKata[6] = 'U';
  NEXT_UNIT.TabKata[7] = 'N';
  NEXT_UNIT.TabKata[8] = 'I';
  NEXT_UNIT.TabKata[9] = 'T';
}
