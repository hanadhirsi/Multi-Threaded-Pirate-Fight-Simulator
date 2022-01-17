#include "defs.h"

/*
  Function: initDeque
  Purpose: initialzies the head and tail of a deque
  in: deque
  out: initialized deque
*/
void initDeque(DequeType *dq){
  
  dq->head = NULL;
  dq->tail = NULL;
}

/*
  Function: DqAddToBack
  Purpose: adds the fighter f to the back of the deque dq
  in: deque to be added to
  in: fighter to be added
*/
void DqAddToBack(DequeType *dq, FighterType *f){
  
  NodeType *currNode;
  NodeType *prevNode;
  NodeType *newNode;
  
  currNode = dq->head;
  prevNode = NULL;
  
  while(currNode != NULL){
    prevNode = currNode;
    currNode = currNode->next;
  }
  
  newNode = malloc(sizeof(NodeType));
  newNode->data = f;
  newNode->next = NULL;
  
  if(prevNode == NULL){
    dq->head = newNode;
  }
  else{
    prevNode->next = newNode;
  }
  
  newNode->next = currNode;
  dq->tail = newNode;

}


/*
  Function: DqRmvFromFront
  Purpose: removes the front node from the deque and returns the fighter tied to it
  in: deque to be removed from
  in: fighter to return value of removed fighter
  out: removed fighter
*/
void DqRmvFromFront(DequeType *dq, FighterType **f){
  NodeType *removedNode;
  if(dq->head == NULL){
    *f = NULL;
    return;
  }
  
  *f = dq->head->data;

  removedNode = dq->head;
  
  if(dq->head == dq->tail){
    dq->tail = NULL;
    dq->head = NULL;
    free(dq->head);
  }
  else{
    dq->head = dq->head->next;
    free(removedNode);
  }  
  
  
  
}

/*
  Function: DqRmvFromFront
  Purpose: removes the back node from the deque and returns the fighter tied to it
  in: deque to be removed from
  in: fighter to return value of removed fighter
  out: removed fighter
*/
void DqRmvFromBack(DequeType *dq, FighterType **f){
  
  NodeType *currNode;
  NodeType *prevNode;
  
  if(dq->head == NULL){
    *f = NULL;
    return;
  }
  
  if(dq->head == dq->tail){
    *f = dq->head->data;
    free(dq->head);
    dq->tail = NULL;
    dq->head = NULL;
  }
  else{
    currNode = dq->head;
    prevNode = NULL;
  
    while(currNode->next != NULL){
      prevNode = currNode;
      currNode = currNode->next;
    }
    
    *f = prevNode->next->data;
    free(prevNode->next);
    prevNode->next = NULL;
    dq->tail = prevNode;
  }
  
  
  
    
}

/*
  Function: DqDeepCopy
  Purpose: copies the values in the first dq to a copy, the new values in the copy are allocated dynamically
  in: deque to be copied
  in: deque to be copied to
  out: deep copy of the first deque
*/
void DqDeepCopy(DequeType *dq, DequeType *dqCopy){
  NodeType *currNode;
  NodeType *prevNode;
  FighterType *f;
  
  
  currNode = dq->head;
  prevNode = NULL;
  
  while(currNode != NULL){
    initFighter(currNode->data->strength , currNode->data->armour, currNode->data->health, &f);
    DqAddToBack(dqCopy, f);
    prevNode = currNode;
    currNode = currNode->next;
  }
  
  
  
  
  
}


/*
  Function: printDq
  Purpose: prints the fighters inside of a given deque
  in: given deque
  out: printed out contents of fighters in deque
*/
void printDq(DequeType *dq){

  NodeType *currNode =  dq->head;
  NodeType *prevNode = NULL;
  
  
  while(currNode != NULL){
   printFighter(currNode->data);
   printf("\n");
   prevNode = currNode;
   currNode = currNode->next;
  } 
  
  printf("LIST HEAD: ");
  printFighter(dq->head->data);
  printf("\n");
  
  printf("LIST TAIL: ");
  printFighter(dq->tail->data);
  printf("\n");
}


/*
  Function: cleanupDq
  Purpose: cleans the deque nodes and the fighters in the deque
  in: given deque
  out: cleaned deque
*/
void cleanupDq(DequeType *dq){
  NodeType *currNode;
  NodeType *nextNode;
  
  currNode = dq->head;
  
  
  while(currNode != NULL){
    nextNode = currNode->next;
    free(currNode->data);
    free(currNode);
    currNode = nextNode;
  }
}


