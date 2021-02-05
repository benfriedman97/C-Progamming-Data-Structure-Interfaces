/*Interface for a generic (char, int, float, double) doubly linked list 
(next and previous pointers) with a headmeaning there is a structure for the whole list
the exists even if the list is empty.The structure has a pointer to the first node, and 
if the list is empty that pointer points to NULL
*/

#ifndef DOUBLE_HEAD_LINKED_LIST
#define DOUBLE_HEAD_LINKED_LIST

#include "status.h"

typedef void* LINKED_LIST;
typedef double Item;

typedef enum itemType { IS_CHAR, IS_INT, IS_FLOAT, IS_DOUBLE } ItemType;

/* Precondition: none
   Postcondition: returns a handle to an empty doubly linked list object. Both
   the head and tail pointer point to NULL */
LINKED_LIST linkedlistCreate(ItemType itemType);

/* Precondition: hList is a handle to a linked list.
   Postcondition: inserts an item at the head and returns SUCCESS. Returns
   FAILURE on any memory allocation failure. */
Status linkedlistHeadInsert(LINKED_LIST hList, Item item);

/* Precondition: hList is a handle to a linked list.
   Postcondition: inserts an item at the tail and returns SUCCESS. Returns
   FAILURE on any memory allocation failure. */
Status linkedlistTailInsert(LINKED_LIST hList, Item item);

/* Precondition: hList is a handle to a linked list.
   Postcondition: deletes the head node and returns SUCCESS.
   Returns FAILURE if list was empty. */
Status linkedlistDeleteHead(LINKED_LIST hList);

/* Precondition: hList is a handle to a linked list.
   Postcondition: deletes the tail node and returns SUCCESS. 
   Returns FAILURE if list was empty. */
Status linkedlistDeleteTail(LINKED_LIST hList);

/* Precondition: hList or a handle to a linked list.
   Postcondition: prints items from head to tail and returns SUCCESS.
   Returns FAILURE if list was empty. */
Status linkedlistPrintHeadToTail(LINKED_LIST hList);

/* Precondition: hList or a handle to a linked list.
   Postcondition: prints items from tail to head and returns SUCCESS. 
   Returns FAILURE if list was empty. */
Status linkedlistPrintTailToHead(LINKED_LIST hList);

/* Precondition: hList is a handle to a linked list
   Postcondition: returns item at the head of the list and sets *pStatus
   to SUCCESS. If list is empty, returns 0 and sets *pStatus to FAILURE. */
Item linkedlistGetHeadItem(LINKED_LIST hList, Status *pStatus);

/* Precondition: hList is a handle to a linked list
   Postcondition: returns item at the tail of the list and sets *pStatus
   to SUCCESS. If list is empty, returns 0 and sets *pStatus to FAILURE. */
Item linkedlistGetTailItem(LINKED_LIST hList, Status *pStatus);

/* Precondition: hList is a handle to a linked list.
   Postcondition: returns the item type of the linked list */
ItemType linkedListGetItemType(LINKED_LIST hList);

/* Precondition: hList is a handle to a valid linked list.
   Postcondition: returns TRUE if empty, or if hList was accidentally NULL.
   Returns FALSE if the list exists but is empty. Sets pStatus to FAILURE
   if hList was accidentally NULL which is how it distinguishes between
   a non-existent list and an empty list. Else, sets it to SUCCESS. If pStatus 
   was accidentally NULL it just ignores it. */
Boolean linkedlistIsEmpty(LINKED_LIST hList, Status *pStatus);

/* Precondition: phList is a pointer to a handle to a valid linked list
   Postcondition: all memory associated with the linked list has been destroyed. 
   Sets the list handle to NULL to avoid a dangling pointer. */
void linkedlistDestroy(LINKED_LIST *phList);

#endif
