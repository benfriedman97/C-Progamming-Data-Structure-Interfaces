/*FIFO queue using a linked list*/
#ifndef FIFO_QUEUE_LINKED_LIST_H
#define FIFO_QUEUE_LINKED_LIST_H

#include "status.h"

typedef void* QUEUE;
typedef double Item;
typedef enum itemType { IS_CHAR, IS_INT, IS_FLOAT, IS_DOUBLE } ItemType;

/*Precondition: none
  Postcondition: returns a handle to an emtpy queue. Returns NULL on memory allocation failure*/
QUEUE queueInitDefault(void);

/*Precondition: hQ is a handle to a queue object, item is the item to be inserted
  Postcondition: inserts the item at the rear of the queue and returns SUCCESS. Returns
  FAILURE if item fails to insert due to memory allocation failure*/
Status queueEnqueue(QUEUE hQ, Item item);

/*Precondition: hQ is a handle to a queue object.
  Postcondition: item at the front of the queue has been removed and returns SUCCESS.
  Returns FAILURE if the queue is empty*/
Status queueService(QUEUE hQ);

/*Precondition: hQ is a handle to a queue object
  Postcondition: returns the item at the front of the queue (char, double, int, or float) and
  sets pStatus to SUCCESS. If queue is empty, returns 0 and sets pStatus to FAILURE. In both
  cases, if pStatus is NULL then it is ignored*/
Item queueFront(QUEUE hQ, Status *pStatus);

/*Precondition: hQ is a handle to a queue object
  Postcondition: returns TRUE if the queue is empty, else false*/
Boolean queueIsEmpty(QUEUE hQ);

/*Precondition: phQ is a pointer to a handle to a queue object
  Postcondition: the queue object has been destroyed*/
void queueDestroy(QUEUE *phQ);

#endif
