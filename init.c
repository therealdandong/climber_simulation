#include "defs.h"
/*
    function initRace
    input RaceInfoType**,
    purpose: init race object with value.
    return void

*/


void initRace(RaceInfoType** raceMatch){
  *raceMatch = malloc(sizeof(RaceInfoType));
  (*raceMatch)->numRunners = 0;
  (*raceMatch)->numDorcs = 0;
  addRunner(raceMatch,"Timmy","T",START_POS,PATH_1,MAX_HEALTH,0);
  addRunner(raceMatch,"Harold","H",START_POS,PATH_2,MAX_HEALTH,0);
  if (sem_init(&((*raceMatch)->mutex),0,1)<0){
      printf("%s\n","error has occur" );
      exit(0);
  }
  strcpy((*raceMatch)->winner,"");
  (*raceMatch)->statusRow = STATUS_ROW;
  srand((unsigned)time(NULL));
  initNcurses();
  scrPrt("health: T   H\0",HEALTH_ROW,HEALTH_COL);
  scrPrt("---------------------------------------\0",HEALTH_ROW+1,0);
  scrPrt("---------------------------------------\0",START_POS+1,0);
}
