/*Generic stack using an array, no duplicates with push function options for ignore-new-item
or replace-old-item policy*/

#ifndef STACK_ARRAY_H
#define STACK_ARRAY_H

#include "status.h"

typedef void* STACK;
typedef double Item;
typedef enum itemType { IS_CHAR, IS_INT, IS_FLOAT, IS_DOUBLE } ItemType;

/*Precondition: capacity the the size of the array to be initialized for the stack
  Postcondition: returns a handle to a stack or NULL if any memory allocation failure*/
STACK stackInitDefault(int capacity);

/*Precondition: hStack is a handle to a stack, item is item to be inserted
  Postcondition: pushes item onto the top of the stack and returns SUCCESS.
  Returns FAILURE if item was not pushed onto the stack due to memory allocation
  failure during resizing*/
Status stackPush(STACK hStack, Item item, Boolean *pInstack);

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
Item stackGetTopItem(STACK hStack, Status *pStatus);

/*Precondition: hStack is a handle to a stack
  Postcondition: prints the stack from top to bottom and returns SUCCESS. Returns FAILURE
  if stack is empty*/
Status stackPrintStackTopToBottom(STACK hStack, ItemType type);

/*Precondition: phStack is a pointer to a handle to a a stack
  Postcondition: all memory for the stack has been free, and handle for the
  stack points to NULL to prevent a dangling pointer*/
void stackDestroy(STACK *phStack);

#endif
