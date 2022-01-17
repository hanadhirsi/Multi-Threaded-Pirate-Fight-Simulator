#ifndef DEFS_H
#define DEFS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

#define C_OK                 0
#define C_NOK               -1

#define NUM_RUNS       100
#define NUM_PIRATES     10
#define NUM_SCENARIOS    3

#define TORT_STRENGTH    5
#define TORT_ARMOUR      8
#define HARE_STRENGTH    8
#define HARE_ARMOUR      5
#define HERO_HEALTH     20
#define PIRATE_HEALTH   10
#define SWORD_STRENGTH   2

#define MAX_STR         64

typedef enum { SUCCESS, FAILURE, PART_SUCCESS, RES_UNKNOWN } ResultType;
typedef enum { FRONT, BACK } DirectionType;

typedef struct {	// Stats for one scenario, accumulated over all runs
  int numSuccess;
  int numPartSuccess;
  int numFailure;
} StatsType;

typedef struct {	// One fighter:  Tortoise, Hare, or Pirate
  int  strength;
  int  armour;
  int  health;
} FighterType;

typedef struct Node {
  FighterType  *data;
  struct Node  *next;
} NodeType;

typedef struct {	// Stores the fighting pirates for one scenario
  NodeType *head;
  NodeType *tail;
} DequeType;

typedef struct {	// Specs for one scenario of one run
  DequeType   *pirates;
  FighterType *tort;
  FighterType *hare;
  StatsType   *stats;
} RunSpecsType;

typedef struct {	// Specs for one fight of one scenario of one run
  FighterType  *hero;
  DequeType    *pirates;
  DirectionType dir;
  sem_t        *dqMutex;
} FightSpecsType;


int randm(int);		// Pseudo-random number generator function



// Functions for deque.c
void initDeque(DequeType *dq);
void DqAddToBack(DequeType *dq, FighterType *f);
void DqRmvFromFront(DequeType *dq, FighterType **f);
void DqRmvFromBack(DequeType *dq, FighterType **f);
void DqDeepCopy(DequeType *dq, DequeType *dqCopy);
void printDq(DequeType *dq);
void cleanupDq(DequeType *dq);

// Functions for fighter.c
void initFighter(int strn, int arm, int hlth, FighterType **fighter);
void printFighter(FighterType *f);
void initPirateArray(DequeType p[NUM_SCENARIOS]);
void initPirateGroup(DequeType *pirates);

// Functions for fightspecs.c
void initFightSpecs(FighterType *h, DequeType *p, DirectionType d, sem_t *m, FightSpecsType **fs);
void* fightPirates(void *args);
void simulateFight(FighterType *hero, FighterType *pirate);
void cleanFightSpecs(FightSpecsType *fs);

// Functions for stats.c
void initStats(int successes, int partSuccesses, int failures, StatsType **s);
void initStatsArray(StatsType *s[NUM_SCENARIOS]);
void computeStats(RunSpecsType *scenarios[NUM_SCENARIOS], int results[NUM_SCENARIOS]);
void printPercentages(StatsType *sts[NUM_SCENARIOS], int runs);
void cleanStats(StatsType *sts[NUM_SCENARIOS]);

// Functions for runspecs.c
void initRunSpecsType(DequeType *p, StatsType *sts, RunSpecsType **rs);
void initScenarioArray(DequeType p[NUM_SCENARIOS], StatsType *sts[NUM_SCENARIOS], RunSpecsType *scenarios[NUM_SCENARIOS]);
void AddSwordtoScenarios(RunSpecsType *scenarios[NUM_SCENARIOS]);
void *runOneScenario(void *args);
void cleanScenarios(RunSpecsType *scenarios[NUM_SCENARIOS]);
void cleanPirates(DequeType p[NUM_SCENARIOS]);


#endif

