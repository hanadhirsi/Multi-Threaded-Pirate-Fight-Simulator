#include "defs.h"

/*
  Function: initFighter
  Purpose: initializes the values in a given fighter type
  in: fighter to be initialized 
  in: strength of fighter
  in: armour of fighter
  in: health of fighter
  out: initialized fighter
*/
void initFighter(int strn, int arm, int hlth, FighterType **fighter){
  

  
  *fighter = malloc(sizeof(FighterType));
  

  (*fighter)->strength = strn;
  (*fighter)->armour = arm;
  (*fighter)->health = hlth;
  

  
}

/*
  Function: initPirateArray
  Purpose: initializes all pirate deques in a given array by deep copying the first one to the others
  in: pirate array to be initialized
  out: initialized pirate array
*/
void initPirateArray(DequeType p[NUM_SCENARIOS]){
  for(int i=1; i < NUM_SCENARIOS; i++){
    initDeque(&p[i]);
  }
  
  if(NUM_SCENARIOS > 0){initPirateGroup(&p[0]);}
  
  for(int i=1; i < NUM_SCENARIOS; i++){
    DqDeepCopy(&p[0], &p[i]);
  }
}

/*
  Function: initPirateGroupd
  Purpose: initializes 10 pirate fighters in a given deque with randomized stats
  in: deque to be filled with pirates
  out: filled deque
*/
void initPirateGroup(DequeType *pirates){
  
  initDeque(pirates);
  
  FighterType *f;
  
  initFighter((randm(5) + 5) , (randm(4) + 1), PIRATE_HEALTH , &f);
  DqAddToBack(pirates, f);
  initFighter((randm(5) + 5) , (randm(4) + 1), PIRATE_HEALTH , &f);
  DqAddToBack(pirates, f);
  initFighter((randm(5) + 5) , (randm(4) + 1), PIRATE_HEALTH , &f);
  DqAddToBack(pirates, f);
  initFighter((randm(5) + 5) , (randm(4) + 1), PIRATE_HEALTH , &f);
  DqAddToBack(pirates, f);
  initFighter((randm(5) + 5) , (randm(4) + 1), PIRATE_HEALTH , &f);
  DqAddToBack(pirates, f);
  initFighter((randm(5) + 5) , (randm(4) + 1), PIRATE_HEALTH , &f);
  DqAddToBack(pirates, f);
  initFighter((randm(5) + 5) , (randm(4) + 1), PIRATE_HEALTH , &f);
  DqAddToBack(pirates, f);
  initFighter((randm(5) + 5) , (randm(4) + 1), PIRATE_HEALTH , &f);
  DqAddToBack(pirates, f);
  initFighter((randm(5) + 5) , (randm(4) + 1), PIRATE_HEALTH , &f);
  DqAddToBack(pirates, f);
  initFighter((randm(5) + 5) , (randm(4) + 1), PIRATE_HEALTH , &f);
  DqAddToBack(pirates, f);
}

/*
  Function: printFighter
  Purpose: prints the stats of one fighter
  in: fighter to be printed
  out: printed contents of one fighter
*/
void printFighter(FighterType *f){


  printf("Strength: %d ", f->strength);
  printf("Armour: %d ", f->armour);
  printf("Health: %d ", f->health);
}

