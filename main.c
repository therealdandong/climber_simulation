#include "defs.h"




int main(){
  initRace(&race);
  raceLoop(&race);
  pthread_join(race->runners[0]->ent.thr,NULL);
  pthread_join(race->runners[1]->ent.thr,NULL);
  for(int i=0;i<race->numDorcs;i++){
    pthread_cancel(race->dorcs[i]->thr);
  }
  if(strcmp(race->winner,"")!=0){
    displayStatusBar(race->winner,0);
  }
  else if(strcmp(race->winner,"")==0){
    displayStatusBar("",3);
  }
  cleanupNcurses(37);

}
void freeAll(){
  free(race->runners[1]);
  free(race->runners[2]);
  for(int i=0;i<(race->numDorcs);i++){
    free(&race->dorcs[i]);
  }
  free(race);
}


