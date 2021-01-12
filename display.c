#include "defs.h"

/*
  function:displayHealth
  purpose: display Health for the runner
  input: RunnerType* runner
  return: void

*/

void displayHealth(RunnerType* runner){
  char *str;
  integerToString(&str,runner->health);
  if(strcmp(runner->ent.avatar,"T")==0){
    scrPrt(str,2,38);
  }
  else if(strcmp(runner->ent.avatar,"H")==0){
    scrPrt(str,2,42);
  }
  free(str);
}
/*
  function:displayStatusBar
  purpose: display 4 kind of StatusBar(collision,winner,dead,alldead)
  input: RunnerType* runner
  return: void

*/


void displayStatusBar(char* name,int type){
  //collsion case
  if(type == 1){
    char tempStr[MAX_BUF]="STATUS: collision between ";
    strcat(tempStr,name);
    strcat(tempStr," and dorc");
    strcat(tempStr,"\0");
    scrPrt(tempStr,(race->statusRow)++,STATUS_COL);
  }
  // winner case
  else if(type == 0){
    char tempStr[MAX_BUF]="OUTCOME: The Winner is ";
    strcat(tempStr,name);
    strcat(tempStr,"\0");
    scrPrt(tempStr,(race->statusRow)++,STATUS_COL);
  }
  // dead case
  else if(type == 2){
    char tempStr[MAX_BUF]="STATUS: ";
    strcat(tempStr,name);
    strcat(tempStr," has dead");
    strcat(tempStr,"\0");
    scrPrt(tempStr,(race->statusRow)++,STATUS_COL);
  }
  //all dead case
  else if(type == 3){
    char tempStr[MAX_BUF]="OUTCOME: every one die ";
    strcat(tempStr,"\0");
    scrPrt(tempStr,(race->statusRow)++,STATUS_COL);
  }
}
