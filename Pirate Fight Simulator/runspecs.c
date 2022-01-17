#include "defs.h"

/*
  Function: initRunSpecsType
  Purpose: initializes a given RunSpecsType 
  in: RunSpecsType to be initialized
  in: Stats Type of run specs
  in: pirate deque of run specs
  out: initialized run specs
*/
void initRunSpecsType(DequeType *p, StatsType *sts, RunSpecsType **rs){
  
  
  *rs = malloc(sizeof(RunSpecsType));
  
  initFighter(TORT_STRENGTH, TORT_ARMOUR , HERO_HEALTH, &((*rs)->tort));
  initFighter(HARE_STRENGTH , HARE_ARMOUR , HERO_HEALTH, &((*rs)->hare));
  (*rs)->pirates = p;
  (*rs)->stats = sts;
  
 
}

/*
  Function: initScenarioArray
  Purpose: initializes an array of RunSpecsTypes
  in: RunSpecsType array to be initialized
  in: array of pirate deques to be added to each run specs type
  in: array of stats types to be added to each run specs type
  out: initialized run specs type array
*/
void initScenarioArray(DequeType p[NUM_SCENARIOS], StatsType *sts[NUM_SCENARIOS], RunSpecsType *scenarios[NUM_SCENARIOS]){

  for(int i=0; i < NUM_SCENARIOS; i++){
    initRunSpecsType(&p[i], sts[i], &scenarios[i]);
  }
  
  AddSwordtoScenarios(scenarios);
  
}

/*
  Function: initScenarioArray
  Purpose: initializes an array of RunSpecsTypes
  in: RunSpecsType array to be initialized
  in: array of pirate deques to be added to each run specs type
  in: array of stats types to be added to each run specs type
  out: initialized run specs type array
*/
void AddSwordtoScenarios(RunSpecsType *scenarios[NUM_SCENARIOS]){
  
  
  if(NUM_SCENARIOS >= 2){
    scenarios[0]->tort->strength += SWORD_STRENGTH;
    scenarios[1]->hare->strength += SWORD_STRENGTH;
  }
  
}



/*
  Function: runOneScenario
  Purpose: thread function for running a single scenario, opens two more threads to begin each hereos' fight one boths sides of a pirate deque
  in: void pointer holding run specs type 
*/
void *runOneScenario(void *args){
  RunSpecsType *run = (RunSpecsType *)args;   // typecasting RunSpecsType containing data for one scenario
  FightSpecsType *frontFight;
  FightSpecsType *backFight;                  //initializing two FightSpecsTypes to split for two threads (each for front and back fight)
  ResultType r;
  
  
  pthread_t fight1, fight2;
  sem_t mutex;                              //initialzing mutex to help control two threads
  
  if(sem_init(&mutex, 0, 1) < 0) {
    printf("Semaphore initialization error\n");
    exit(1);
  }
  
  initFightSpecs(run->hare, run->pirates, BACK, &mutex, &backFight);
  initFightSpecs(run->tort, run->pirates, FRONT, &mutex, &frontFight);
  
  pthread_create(&fight1, NULL, fightPirates, frontFight);
  pthread_create(&fight2, NULL, fightPirates, backFight);
  
  pthread_join(fight1, NULL);
  pthread_join(fight2, NULL);

  if((run->pirates->head == NULL) && (run->tort->health > 0) && (run->hare->health > 0)){       //Checking pirate deque and hero health after threads join back to see who won
    r = SUCCESS;
  }
  else if((run->pirates->head == NULL)&& ((run->tort->health > 0) || (run->hare->health > 0))){
    r = PART_SUCCESS;
  }
  else if(((run->tort->health == 0) && (run->hare->health == 0))){
    r = FAILURE;
  }
  else{
    r = RES_UNKNOWN;
  }
   
  cleanFightSpecs(frontFight);                  //cleaning FightSpecsTypes
  cleanFightSpecs(backFight);

  pthread_exit((void *)r);                   //Casting result enum as a void pointer to return to main function (will typecast back to an enum to read the value)
   
  
}

/*
  Function: cleanScenarios
  Purpose: deallocates an array of RunSpecsTypes
  in: RunSpecsType array to be cleaned
  out: cleaned RunSpecsType array
*/
void cleanScenarios(RunSpecsType *scenarios[NUM_SCENARIOS]){
  for(int i=0; i < NUM_SCENARIOS; i++){
    free(scenarios[i]->tort);
    free(scenarios[i]->hare);
    free(scenarios[i]); 
  }
  
}

/*
  Function: cleanPirates
  Purpose: deallocates an array of pirate deques
  in: deque array to be cleaned
  out: cleaned deque array
*/
void cleanPirates(DequeType p[NUM_SCENARIOS]){
  for(int i=0; i < NUM_SCENARIOS; i++){
    cleanupDq(&p[i]);
  }
}





