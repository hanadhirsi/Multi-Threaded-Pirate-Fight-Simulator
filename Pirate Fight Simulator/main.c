#include "defs.h"



int main(int argc, char *argv[])
{

  RunSpecsType *allScenarios[NUM_SCENARIOS];   //Declaring arrays for scenarios, pirates, and statistics
  DequeType allPirates[NUM_SCENARIOS];
  StatsType *allStats[NUM_SCENARIOS];
  
  int runs;
  void* resultReader;                       //void pointer used to read return value of thread function
  int result[NUM_SCENARIOS];
  
  
  pthread_t t[NUM_SCENARIOS];           
  
  srand( (unsigned)time( NULL ) );          //To make sure random numbers change after each run
  
  initStatsArray(allStats);                //initializing stats

 
  if(argc == 2){
    runs = atoi(argv[1]);
  }                                        //If commandline argument is not made for num runs, it will default to constant in defs.h
  else{
    runs = NUM_RUNS;
  }
  
  
  for(int i=0; i < runs; i++){           //Looping over num runs times
    
    initPirateArray(allPirates);
    initScenarioArray(allPirates, allStats, allScenarios);           //initializing pirate deques and adding them to RunSpecsType along with stats
  
    for(int i=0; i < NUM_SCENARIOS; i++){
       pthread_create(&t[i], NULL, runOneScenario, allScenarios[i]);
    }
                                                                     // for loops to create and join the right amount of threads
    for(int i=0; i < NUM_SCENARIOS; i++){
       pthread_join(t[i], &resultReader);
       result[i] = *((int*)&resultReader);                           // typecasting the void pointer returned by each thread to get enums for outcome (success, part success, or fail)
    }
    
    computeStats(allScenarios, result);                            
    
    cleanPirates(allPirates);
    cleanScenarios(allScenarios);                      //cleaning all pirate memory and scenario memory
    
  }
  
  printPercentages(allStats, runs);                    //printing percentages then cleaning stats
    
  cleanStats(allStats);
  
  return 0;
}

/*
  Function:  randm
  Purpose:   returns a pseudo randomly generated number, 
             in the range 0 to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1) 
*/
int randm(int max)
{
  double r = ( (double)rand() / ((double)(RAND_MAX)+(double)(1)) ); 

  return (int)(r * max);
}
