/*index items stack (0 or greater integers only) using a forget-the-old item policy. Uses
a doubly linked list and the array to keep track if an item is present in the stack uses
pointers to Nodes instead of 0 or 1*/

#ifndef STACK_LINKED_LIST_H
#define STACK_LINKED_LIST_H

#include "status.h"

typedef void* STACK;

/*Precondition: none
  Postcondition: initializes a stack object (holds an empty linked list).
  Returns a handle to the stack or NULL on memory allocation failure*/
STACK stackInitDefault(void);

/*Precondition: hStack is a handle to a stack, item is item to be inserted
  Postcondition: pushes item onto the top of the stack and returns SUCCESS.
  Returns FAILURE if the item failed to be put onto the stack due to memory
  allocation failure or if the item was not a positive integer*/
Status stackPush(STACK hStack, int item, Boolean *pInstack);

/*Precondition: hStack is a handle to a stack
  Postcondition: pops item off the stack and returns SUCCESS. Returns FAILURE
  if the stack was empty*/
Status stackPop(STACK hStack);

/*Precondition: hStack is a handle to a stack
  Postcondition: returns the item at the top of the stack and sets pStatus to SUCCESS.
  If the stack was empty, it returns 0 (or \0 if item is char) and sets pStatus to FAILURE.
  pStatus is ignored if it's NULL*/
int stackGetTopItem(STACK hStack, Status *pStatus);

/*Precondition: hStack is a handle to a stack, type specifices the item type.
  Postcondition: prints the items from the top to the bottom of the stack and returns SUCCESS.
  Returns FAILURE if the stack is empty*/
Status stackPrintTopToBottom(STACK hStack);

/*Precondition: hStack is a handle to a stack.
  Postcondition: returns TRUE if the stack is empty, else FALSE*/
Boolean stackIsEmpty(STACK hStack);

/*Precondition: phStack is a pointer to a handle to a stack
  Postcondition: that stack has been destroyed*/
void stackDestroy(STACK *phStack);

#endif
