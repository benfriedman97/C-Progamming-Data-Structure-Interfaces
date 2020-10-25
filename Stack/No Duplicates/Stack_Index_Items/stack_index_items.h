/*Header file for positive integer stack interface (index items interface).*/

#ifndef STACK_INDEX_ITEMS_H
#define STACK_INDEX_ITEMS_H

#include "status.h"

typedef void* STACK;

/*Precondition: capacity the the size of the array to be initialized for the stack
  Postcondition: returns a handle to a stack or NULL if any memory allocation failure.
  Checks for duplicates by creating a second array of 0's and 1's in which each
  item inserted becomes it's own index i.e. if 43 is inserted, then a[43] becomes
  1 or is ignored if it's already 1*/
STACK stackInitDefault(int capacity);

/*Precondition: hStack is a handle to a stack, item is item to be inserted, pStatus
  lets user know if item is already in the stack
  Postcondition: pushes item onto the top of the stack and returns SUCCESS.
  Returns FAILURE if item was not pushed onto the stack due to memory allocation
  failure during resizing or if item was not a positive integer*/
Status stackPush(STACK hStack, int item, Status *pStatus);

/*Precondition: hStack is a handle to a stack
  Postcondition: pops item off the stack and returns SUCCESS. Returns FAILURE
  if the stack was empty*/
Status stackPop(STACK hStack);

/*Precondition: hStack is a handle to a stack.
  Postcondition: returns TRUE if the stack is empty, else FALSE*/
Boolean stackIsEmpty(STACK hStack);

/*Precondition: hStack is a handle to a stack
  Postcondition: returns the item at the top of the stack and sets pStatus to SUCCESS.
  If the stack was empty, it returns 0 (or \0 if item is char) and sets pStatus to FAILURE.
  pStatus is ignored if it's NULL*/
int stackGetTopItem(STACK hStack, Status *pStatus);

Status stackPrintTopToBottom(STACK hStack);

/*Precondition: phStack is a pointer to a handle to a a stack
  Postcondition: all memory for the stack has been free, and handle for the
  stack points to NULL to prevent a dangling pointer*/
void stackDestroy(STACK *phStack);

#endif
