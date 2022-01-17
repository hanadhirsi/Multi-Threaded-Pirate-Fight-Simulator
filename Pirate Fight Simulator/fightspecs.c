#include "defs.h"

/*
  Function: initFightSpecs
  Purpose: initializes the values of a given fight specs type
  in: deque to be filled with pirates
  in: hero (either tortoise or hare)
  in: direction enum (FRONT OR BACK)
  in: mutex to control the two threads manipulating one deque
  out: filled deque
*/
void initFightSpecs(FighterType *h, DequeType *p, DirectionType d, sem_t *m, FightSpecsType **fs){
  
  *fs = malloc(sizeof(FightSpecsType));
  
  (*fs)->hero = h;
  (*fs)->pirates = p;
  (*fs)->dir = d;
  (*fs)->dqMutex = m;
}


/*
  Function: fightPirates
  Purpose: thread function that allows a two ends of a pirate deque to be removed from at once
  in: void pointer 
*/
void *fightPirates(void *args){ 
  FightSpecsType *fight = (FightSpecsType *)args;   // type casting args to get the FightSpecsType
  FighterType *removedPirate;                       // variable to hold removed pirates
  

  while((fight->pirates->head != NULL) && (fight->hero->health > 0)){
    
    
    if(sem_wait(fight->dqMutex) < 0){
      printf("Semaphore wait error\n");
      exit(1);
    }
    
      
    if((fight->dir == FRONT) && (fight->pirates->head != NULL)){       // Handles the front fight
      DqRmvFromFront(fight->pirates, &removedPirate);
      simulateFight(fight->hero, removedPirate);
    }
    
    if((fight->dir == BACK) && (fight->pirates->head != NULL)){        // Handles the back fight
      DqRmvFromBack(fight->pirates, &removedPirate);
      simulateFight(fight->hero, removedPirate);
    }
    
    free(removedPirate);                          //free for deallocating the values removed from the array
    
    
    if(sem_post(fight->dqMutex) < 0){
      printf("Semaphore post error\n");
      exit(1);
    }
    
    usleep(1000);                            //slows down proccessing to allow both threads sufficient time
} 
  
}


/*
  Function: simulateFight
  Purpose: simulates a fight between a hero (tortoise or hare) and a pirate
  in: hero that is fighting
  in: pirate that is fighting
*/
void simulateFight(FighterType *hero, FighterType *pirate){
  int heroDamage = hero->strength - pirate->armour;   
  if(heroDamage < 0){heroDamage = 0;}              //if damage is < 0, it is changed to 0
 
   while((hero->health != 0) && (pirate->health != 0)){
     int tempPirateStrength = pirate->strength + randm((pirate->strength) - 1); //random pirate strength updated every hit
     int pirateDamage = tempPirateStrength - hero->armour;
     if(pirateDamage < 0){pirateDamage = 0;}
   
     pirate->health = pirate->health - (heroDamage);
      if(pirate->health <= 0){
        pirate->health = 0;
        hero->health = hero->health + 3;
     }
   
     if(pirate->health != 0){
       hero->health = hero->health - (pirateDamage);
       if(hero->health <= 0){hero->health = 0;}
     }
   
   }
  
}

/*
  Function: cleanFightSpecs
  Purpose: cleans a given FightSpecsType
  in: FightSpecsType to be cleaned
  out: cleaned FightSpecsType
*/
void cleanFightSpecs(FightSpecsType *fs){
  free(fs);
}














