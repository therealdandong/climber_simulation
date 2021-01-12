#include "defs.h"
/*
  function addRunner
  purpose: addrunner to race object
  input:RaceInfoType **raceMatch,char* name,char* symbol,int currentPosition,int currentPath,
  int health,int dead
  return void

*/

void addRunner(RaceInfoType **raceMatch,char* name,char* symbol,int currentPosition,int currentPath,
int health,int dead){
  EntityType entity;
  strcpy(entity.avatar,symbol);
  entity.avatar[1] = '\0';
  entity.currPos = currentPosition;
  entity.path = currentPath;


  RunnerType*runner;
  runner = malloc(sizeof(RunnerType));
  strcpy(runner->name,name);
  runner->ent = entity;
  runner->health = health;
  runner->dead = dead;
  pthread_create(&(runner->ent.thr),NULL,goRunner,runner);
  (*raceMatch)->runners[(*raceMatch)->numRunners] =runner;
  ((*raceMatch)->numRunners)++;
}
/*
  function addDorc
  purpose: addDorc to race object
  input:RaceInfoType** races
  int health,int dead
  return void

*/

void addDorc(RaceInfoType** races){


  EntityType * orcs = malloc(sizeof(EntityType));
  strcpy(orcs->avatar,"d\0");
  int temp = randm(1000);
  //printf("\n%d\n", temp);
  if(temp<=300){
    orcs->path = PATH_1;
  }
  else if (temp>300 && temp<=600){
    orcs->path = PATH_2;
  }
  else if(temp>600){
    orcs->path = (PATH_1+PATH_2)/2;
  }
  orcs->currPos= END_POS;
  pthread_create(&(orcs->thr),NULL,goDorc,orcs);
  (*races)->dorcs[(*races)->numDorcs] = orcs;
  ((*races)->numDorcs)++;

}
