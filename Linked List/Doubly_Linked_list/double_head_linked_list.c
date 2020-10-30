#include <stdio.h>
#include <stdlib.h>
#include "double_head_linked_list.h"

typedef struct node {
	Item item;
	struct node *previous, *next;
} Node;

typedef struct linkedList {
	Node *head, *tail;
} LinkedList;

LINKED_LIST linkedlistCreate(void)
{
	LinkedList *pList = (LinkedList*)malloc(sizeof(LinkedList));
	if (pList != NULL) {
		pList->head = NULL;
		pList->tail = NULL;
	}
	return (LINKED_LIST)pList;
}


Status linkedlistHeadInsert(LINKED_LIST hList, Item item)
{
	if (hList == NULL)
		return FAILURE;

	Status status;
	LinkedList *pList = (LinkedList*)hList;
	Node *newHead = (Node*)malloc(sizeof(Node)), *temp;
	if (newHead == NULL)
		return FAILURE;
	newHead->item = item;
	newHead->previous = NULL;

	//empty list
	if (linkedlistIsEmpty(hList, &status)) {
		pList->tail = newHead;
		newHead->next = NULL;
	}
	//non-empty list
	else {
		pList->head->previous = newHead;
		newHead->next = pList->head;
	}
	
	pList->head = newHead;
	return SUCCESS;
}


Status linkedlistTailInsert(LINKED_LIST hList, Item item)
{
	if (hList == NULL)
		return FAILURE;

	Status status;
	LinkedList *pList = (LinkedList*)hList;
	Node *newTail = (Node*)malloc(sizeof(Node));
	if (newTail == NULL)
		return FAILURE;
	newTail->item = item;
	newTail->next = NULL;

	//empty list
	if (linkedlistIsEmpty(hList, &status)) {
		pList->head = newTail;
		newTail->previous = NULL;
	}
	//non-empty list
	else {
		pList->tail->next = newTail;
		newTail->previous = pList->tail;
	}
	
	pList->tail = newTail;
	return SUCCESS;
}


Status linkedlistDeleteHead(LINKED_LIST hList)
{
	Status status;
	//Non-existent or empty list
	if (linkedlistIsEmpty(hList, &status))
		return FAILURE;
	
	LinkedList *pList = (LinkedList*)hList;
	Node *temp;
	//size 1
	if (pList->head->next == NULL) {
		free(pList->head);
		pList->head = pList->tail = NULL;
	}
	//size 2 or greater
	else {
		temp = pList->head->next;
		temp->previous = NULL;
		free(pList->head);
		pList->head = temp;
		//size was 2 and is now 1
		if (pList->head->next == NULL)
			pList->tail = temp;
	}
	return SUCCESS;
}


Status linkedlistDeleteTail(LINKED_LIST hList)
{
	Status status;
	//Non-existent or empty list
	if (linkedlistIsEmpty(hList, &status))
		return FAILURE;

	LinkedList *pList = (LinkedList*)hList;
	Node *temp;
	//size 1
	if (pList->tail->previous == NULL) {
		free(pList->tail);
		pList->head = pList->tail = NULL;
	}
	//size 2 or greater
	else {
		temp = pList->tail->previous;
		temp->next = NULL;
		free(pList->tail);
		pList->tail = temp;
		//size was 2 and is now 1
		if (pList->tail->previous == NULL)
			pList->head = temp;
	}
	return SUCCESS;
}


Status linkedlistPrintHeadToTail(LINKED_LIST hList, ItemType type)
{
	Status status;
	//Non-existent or empty list
	if (linkedlistIsEmpty(hList, &status))
		return FAILURE;

	LinkedList *pList = (LinkedList*)hList;
	Node *temp = pList->head;
	while (temp != NULL) {
		if (type == IS_CHAR)
			printf("%c\n", temp->item);
		else if (type == IS_INT)
			printf("%d\n", temp->item);
		else if (type == IS_DOUBLE || IS_FLOAT)
			printf("%f\n", temp->item);
		temp = temp->next;
	}
	return SUCCESS;
}


Status linkedlistPrintTailToHead(LINKED_LIST hList, ItemType type)
{
	Status status;
	//Non-existent or empty list
	if (linkedlistIsEmpty(hList, &status))
		return FAILURE;

	LinkedList *pList = (LinkedList*)hList;
	Node *temp = pList->tail;
	while (temp != NULL) {
		if (type == IS_CHAR)
			printf("%c\n", temp->item);
		else if (type == IS_INT)
			printf("%d\n", temp->item);
		else if (type == IS_DOUBLE || IS_FLOAT)
			printf("%f\n", temp->item);
		temp = temp->previous;
	}
	return SUCCESS;
}


Item linkedlistGetHeadItem(LINKED_LIST hList, Status *pStatus)
{
	//non-existent or empty list
	Status status;
	if (linkedlistIsEmpty(hList, &status)) {
		if (pStatus != NULL)
			*pStatus = FAILURE;
		return 0;
	}
	//non-empty list
	LinkedList *pList = (LinkedList*)hList;
	if (pStatus != NULL)
		*pStatus = SUCCESS;
	return pList->head->item;
}


Item linkedlistGetTailItem(LINKED_LIST hList, Status *pStatus)
{
	//non-existent or empty list
	Status status;
	if (linkedlistIsEmpty(hList, &status)) {
		if (pStatus != NULL)
			*pStatus = FAILURE;
		return 0;
	}

	//non-empty list
	LinkedList *pList = (LinkedList*)hList;
	if (pStatus != NULL)
		*pStatus = SUCCESS;
	return pList->tail->item;
}


Boolean linkedlistIsEmpty(LINKED_LIST hList, Status *pStatus)
{
	if (hList == NULL) {
		if (pStatus != NULL)
			*pStatus = FAILURE;
		return TRUE;
	}
	LinkedList *pList = (LinkedList*)hList;
	if (pStatus != NULL)
		*pStatus = SUCCESS;
	if (pList->head == NULL)
		return TRUE;
	return FALSE;
}


void linkedlistDestroy(LINKED_LIST *phList)
{
	if (phList != NULL && *phList != NULL) {
		LinkedList *pList = (LinkedList*)*phList;
		Node *head = pList->head;
		//account for empty list
		if (head != NULL) {
			Node *next = head->next;
			free(head);
			while (next != NULL) {
				head = next;
				next = next->next;
				free(head);
			}
		}
		free(pList);
		*phList = NULL;
	}
}