#include "defs.h"

/*
  function:goRunner
  purpose:handle go runner when thread is created.
  input void *run;
  return void
*/
void *goRunner(void * run){
  RunnerType * runner = (RunnerType*) run;
  while(runner->dead==C_FALSE && runner->ent.currPos!=END_POS){
    int temp = randm(1000);
    int step;


    findStep(temp,&step,&runner);

    // check for collsion after step has move
    if(sem_wait(&(race->mutex))<0){
      printf("semaphore wait went wrong");
      exit(1);
    }
    /////////////////////////////
    /////// collsion check
    ////////////////////////////
    if(step<0){
      (runner->health)+=step;
    }

    checkCollision(&runner,step);

    if(sem_post(&(race->mutex))<0){
      printf("semaphore post went wrong");
      exit(1);
    }

    /////////////////////////////////
    ////////check if runner die
    /////////////////////////////////
    if(runner->health == 0){
      strcpy(runner->ent.avatar,"+");
      runner->dead = C_TRUE;
      displayStatusBar(runner->name,2);
    }


    updateRunnerPosition(&runner,step);

    (runner->ent.currPos)+=step;
    usleep(250000);

  }
  ////////////////////
  //// implement3.5.3
  ////////////////////
  if(strcmp(race->winner,"")==0 && runner->dead==C_FALSE){
    strcpy(race->winner,runner->name);
  }

  ////////////////////
  //// implement3.5.4
  ////////////////////
  scrPrt(runner->ent.avatar,runner->ent.currPos,runner->ent.path);

}

/*
    function:updateRunnerPosition
    purpose: update runner position.
    input:RunnerType** runner,int findStep
    return: void

*/


void updateRunnerPosition(RunnerType **runner,int step){
  if(sem_wait(&(race->mutex))<0){
    printf("semaphore wait went wrong");
    exit(1);
  }
  // update blank on previous
  scrPrt(" \0",(*runner)->ent.currPos,(*runner)->ent.path);
  //update new position
  scrPrt((*runner)->ent.avatar,(*runner)->ent.currPos+step,(*runner)->ent.path);
  displayHealth((*runner));
  //////////////////////////////////
  /////// lock end
  /////////////////////////////////
  if(sem_post(&(race->mutex))<0){
    printf("semaphore post went wrong");
    exit(1);
  }
}

/*helper function
    function:integerToString
    purpose: convert integer To String(within 100);


*/


void integerToString(char** str,int num){
  *str = malloc(sizeof(char)*3);
  if(num<10){
    (*str)[0] = ' ';
    (*str)[1] =(num + '0');
    (*str)[2]='\0';
  }
  else if(num<100){
    (*str)[0] = (num/10)+'0';
    (*str)[1] = (num%10)+'0';
    (*str)[2] = '\0';
  }
}


/*
  function:findStep
  purpose: find the next step for runner.
  input: int temp,int*step,RunnerType**runner
  return: void

*/


void findStep(int temp,int*step,RunnerType**runner){
  if(temp<700){
    (*step) = randm(-4)-1;
  }
  else if(temp >=700){
    (*step) = randm(3)+1;
  }
  ////////////
  ///the runner is climbing up
  ///////////
  if((*step)<0){
    // the case of climbing up
    // need to walk more than capable
    if((*runner)->health+(*step)<=0){
      // but we are alive when we reach top
      if((*runner)->health>=((*runner)->ent.currPos - END_POS)){
        //runner->health -=(runner->ent.currPos - END_POS);
        (*step) = -((*runner)->ent.currPos - END_POS);
      }
      // we die trying to walk, die of exhausted.
      else if((*runner)->health < ((*runner)->ent.currPos - END_POS)){
        // this runner is death.
        (*step) = -((*runner)->health);
        //runner->health =0;
      }
    }
    // the case of climbing up
    // can walk full distance
    else if((*runner)->health+(*step)>0){
      // the case of reach top
      if((*runner)->ent.currPos+(*step)<=END_POS){
        //runner->health-= (runner->ent.currPos - END_POS);
        (*step) = -((*runner)->ent.currPos - END_POS);
      }
      // the case of able to finished walking up.
      else if((*runner)->ent.currPos+(*step)>END_POS){
        //runner->health+=step;
        //runner->ent.currPos +=step;
        (*step)=(*step);
      }
    }
  }
  // walk down stair
  else if((*step)>0){
    if((*runner)->ent.currPos+(*step)>35){
      (*step)=START_POS-(*runner)->ent.currPos;
    }
    else if((*runner)->ent.currPos<=35){
      (*step) = (*step);
    }
  }
}

/*
  function:checkCollision
  purpose: checkCollision when runner meet dorcs
  input: RunnerType** runner,int step
  return: void

*/



void checkCollision(RunnerType** runner,int step){
  for(int i=0;i<race->numDorcs;i++){

    if(race->dorcs[i]->currPos == (*runner)->ent.currPos && race->dorcs[i]->path == (*runner)->ent.path){


      if((*runner)->health>3){
        ((*runner)->health) -= 3;
      }
      else if((*runner)->health<=3){
        ((*runner)->health) = 0;
      }
      displayStatusBar((*runner)->name,1);
    }

  }
}


/*
  function:findOrcStep
  purpose: find the next row step and column step for dorcs
  input: EntityType**orc,int nextRow,int *nextCol
  return: void

*/

void findOrcStep(EntityType**orc,int nextRow,int *nextCol){
  int temp;

  temp = randm(1000);
  // move path 2 column to the left.if over the leftest path, set left path
  if(temp<333){
      if((*orc)->path-2<10){
        *nextCol = 10;
      }
      else if((*orc)->path-2>=10){
        *nextCol = (*orc)->path-2;
      }
  }
  // move path 2 column to the right. if over the rightest path, set right path
  else if(temp>=333 && temp<666){
    if(((*orc)->path+2)>14){
      *nextCol = 14;
    }
    else if((*orc)->path+2<=14){
      *nextCol = (*orc)->path+2;
    }
  }
  // stay at the same path;
  else if(temp>=666){
    *nextCol = (*orc)->path;
  }
}



/*
  function:goDorc
  purpose: handler for dorc when thread is created.
  input: void* orcs
  return: void

*/



void *goDorc(void* orcs){
  EntityType *orc = ((EntityType*)orcs);
  while(orc->currPos<35){
    int nextRow = randm(5)+1;
    int nextCol;

    findOrcStep(&orc,nextRow,&nextCol);

    ////////////////////////////
    //////lock begin
    ///////////////////////////
    if(sem_wait(&(race->mutex))<0){
      printf("semaphore wait went wrong");
      exit(1);
    }
    ///////////////////////////
    ////display previous
    //////////////////////////
    scrPrt(" \0",orc->currPos,orc->path);
    if((orc->currPos+nextRow)>=35){
      nextRow = START_POS - orc->currPos;
    }
    scrPrt(orc->avatar,orc->currPos+nextRow,nextCol);
    ////////////////////////////
    //////lock end
    ///////////////////////////
    if(sem_post(&(race->mutex))<0){
      printf("semaphore wait went wrong");
      exit(1);
    }
    (orc->currPos)+=nextRow;

    (orc->path) = nextCol;
    usleep(700000);
  }
  scrPrt(" \0",orc->currPos,orc->path);

}

/*
  function:raceLoop
  purpose: race loop controller
  input: RaceInfoType ** races
  return: void

*/


void raceLoop(RaceInfoType ** races){
  while(strcmp((*races)->winner,"")==0 && (*races)->runners[0]->health!=0 &&(*races)->runners[1]->health!=0){
    if(randm(1000)<300){
      addDorc(races);
    }
    usleep(250000);

  }
}
