/*Generic stack interface using a singly linked list as the stack. The stack itself
  is represented with the head node which points to the first node. That means
  an empty stack is just a stack structure with head and rear pointers to NULL
  Does not store duplicates. stackPush offers two options of either ignore-new-item
  policy or replace-old-item policy*/

#ifndef STACK_LINKED_LIST_H
#define STACK_LINKED_LIST_H

#include "status.h"

typedef void* STACK;
typedef double Item;
typedef enum itemType { IS_CHAR, IS_INT, IS_FLOAT, IS_DOUBLE } ItemType;

/*Precondition: none
  Postcondition: initializes a stack object (holds an empty linked list).
  Returns a handle to the stack or NULL on memory allocation failure*/
STACK stackInitDefault(void);

/*Precondition: hStack is a handle to a stack, item is item to be inserted
  Postcondition: pushes item onto the top of the stack and returns SUCCESS.
  Returns FAILURE if the item failed to be put onto the stack due to memory
  allocation failure*/
Status stackPush(STACK hStack, Item item, Boolean *pInstack);

/*Precondition: hStack is a handle to a stack
  Postcondition: pops item off the stack and returns SUCCESS. Returns FAILURE
  if the stack was empty*/
Status stackPop(STACK hStack);

/*Precondition: hStack is a handle to a stack
  Postcondition: returns the item at the top of the stack and sets pStatus to SUCCESS.
  If the stack was empty, it returns 0 (or \0 if item is char) and sets pStatus to FAILURE.
  pStatus is ignored if it's NULL*/
Item stackGetTopItem(STACK hStack, Status *pStatus);

/*Precondition: hStack is a handle to a stack, type specifices the item type.
  Postcondition: prints the items from the top to the bottom of the stack and returns SUCCESS.
  Returns FAILURE if the stack is empty*/
Status stackPrintTopToBottom(STACK hStack, ItemType type);

/*Precondition: hStack is a handle to a stack.
  Postcondition: returns TRUE if the stack is empty, else FALSE*/
Boolean stackIsEmpty(STACK hStack);

/*Precondition: phStack is a pointer to a handle to a stack
  Postcondition: that stack has been destroyed*/
void stackDestroy(STACK *phStack);

#endif
