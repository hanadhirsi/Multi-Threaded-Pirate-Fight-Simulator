#include "defs.h"

/*
  Function: initStats
  Purpose: initializes the stats of a given stats type
  in: amount of successful runs (tortoise and hare survive)
  in: amount of partially succesful runs (tortoise or hare dies)
  in: amount of failures (both heroes die)
  out: initialized stats type
*/
void initStats(int successes, int partSuccesses, int failures, StatsType **s){
  
  *s = malloc(sizeof(StatsType));
  
  (*s)->numSuccess = successes;
  (*s)->numPartSuccess = partSuccesses;
  (*s)->numFailure = failures;
}

/*
  Function: initStatsArray
  Purpose: initializes the stats of all StatsTypes in the array
  in: array of StatsTypes
  out: initialized stats type array 
*/
void initStatsArray(StatsType *s[NUM_SCENARIOS]){
  for(int i=0; i < NUM_SCENARIOS; i++){
    initStats(0, 0, 0, &s[i]);
  }
}

/*
  Function: printPercentages
  Purpose: prints the percentages of successes, partial successes, and fails for each scenario
  in: array of stats types
  out: printed stats for each scenario
*/
void printPercentages(StatsType *sts[NUM_SCENARIOS], int runs){
  
  printf("---------------------------------------------------\n");
  printf("Hero with Sword     Success     Partial     Failure\n");
  printf("---------------------------------------------------\n");
  
  for(int i=0; i < NUM_SCENARIOS; i++){
    if(i == 0){printf("Tortoise            ");}
    else if(i == 1){printf("Hare                ");}
    else{printf("Neither             ");}
    
     printf(" %-12g  %-12g  %-12g\n",
     round((sts[i]->numSuccess*100)/runs),  
     round((sts[i]->numPartSuccess*100)/runs),  
     round((sts[i]->numFailure*100)/runs));
      
    printf("---------------------------------------------------\n");
  }
    
  printf("Total Runs: %d\n", runs);
    
  
  
}

/*
  Function: computeStats
  Purpose: addes the number of successes, partial successes, and fails according to an array of ResultType enums
  in: array scenarios (RunSpecsTypes)
  in: array of ResultType enums
*/
void computeStats(RunSpecsType *scenarios[NUM_SCENARIOS], int results[NUM_SCENARIOS]){
  
    for(int i=0; i < NUM_SCENARIOS; i++){
    
       switch(results[i]){
       
         case SUCCESS:
           scenarios[i]->stats->numSuccess += 1;
           break;
           
         case FAILURE:
           scenarios[i]->stats->numFailure += 1;
           break;
           
         case PART_SUCCESS:
           scenarios[i]->stats->numPartSuccess += 1;
           break;
           
         default:
           break;
       }
    }
}



/*
  Function: cleanStats
  Purpose: deallocates a given stats type array
  in: array of stats types
  out: cleaned stats type array
*/
void cleanStats(StatsType *sts[NUM_SCENARIOS]){
  for(int i=0; i < NUM_SCENARIOS; i++){
    free(sts[i]);  
  }
}







