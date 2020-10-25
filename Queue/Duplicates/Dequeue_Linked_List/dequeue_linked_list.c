#include <stdlib.h>
#include <stdio.h>
#include "dequeue_linked_list.h"

typedef struct node {
	struct node *next, *prev;
	Item item;
} Node;

typedef struct queue {
	Node *head, *tail;
	int size;
} Queue;

QUEUE queueInitDefault(void)
{
	Queue *pQ = (Queue*)malloc(sizeof(Queue));
	if (pQ != NULL) {
		pQ->head = NULL;
		pQ->tail = NULL;
	}
	pQ->size = 0;
	return (QUEUE)pQ;
}


Status queueEnqueueFront(QUEUE hQ, Item item)
{
	Queue *pQ = (Queue*)hQ;
	Node *newHead = (Node*)malloc(sizeof(Node));
	if (newHead == NULL)
		return FAILURE;
	newHead->item = item;
	newHead->prev = NULL;

	//empty list
	if (queueIsEmpty(hQ)) {
		pQ->tail = newHead;
		newHead->next = NULL;
	}
	//non-empty list
	else {
		pQ->head->prev = newHead;
		newHead->next = pQ->head;
	}

	pQ->head = newHead;
	pQ->size++;
	return SUCCESS;
}


Status queueEnqueueRear(QUEUE hQ, Item item)
{
	Queue *pQ = (Queue*)hQ;
	Node *newTail = (Node*)malloc(sizeof(Node));
	if (newTail == NULL)
		return FAILURE;
	newTail->item = item;
	newTail->next = NULL;

	//empty list
	if (queueIsEmpty(hQ)) {
		pQ->head = newTail;
		newTail->prev = NULL;
	}
	//non-empty list
	else {
		pQ->tail->next = newTail;
		newTail->prev = pQ->tail;
	}

	pQ->tail = newTail;
	pQ->size++;
	return SUCCESS;
}


Status queueServiceFront(QUEUE hQ)
{
	Queue *pQ = (Queue*)hQ;
	//queue is empty
	if (queueIsEmpty(hQ))
		return FAILURE;
	//size is 1
	if (pQ->head->next == NULL) {
		free(pQ->head);
		pQ->head = pQ->tail = NULL;
	}
	//size is 2 or greater
	else {
		Node *temp = pQ->head->next;
		temp->prev = NULL;
		free(pQ->head);
		pQ->head = temp;
		/*If size had been two*/
		if (pQ->head->next == NULL)
			pQ->tail = temp;
	}
	pQ->size--;
	return SUCCESS;
}


Status queueServiceRear(QUEUE hQ)
{
	Queue *pQ = (Queue*)hQ;
	//queue is empty
	if (queueIsEmpty(hQ))
		return FAILURE;
	//size is 1
	if (pQ->tail->prev == NULL) {
		free(pQ->tail);
		pQ->tail = pQ->head = NULL;
	}
	//size is 2 or greater
	else {
		Node *temp = pQ->tail->prev;
		temp->next = NULL;
		free(pQ->tail);
		pQ->tail = temp;
		/*If size had been two*/
		if (pQ->tail->prev == NULL)
			pQ->head = temp;
	}
	pQ->size--;
	return SUCCESS;
}


Item queueGetFrontItem(QUEUE hQ, Status *pStatus)
{
	Queue *pQ = (Queue*)hQ;
	//queue is empty
	if (queueIsEmpty(hQ)) {
		if (pStatus != NULL)
			*pStatus = FAILURE;
		return 0;
	}
	if (pStatus != NULL)
		*pStatus = SUCCESS;
	return pQ->head->item;
}


Item queueGetRearItem(QUEUE hQ, Status *pStatus)
{
	Queue *pQ = (Queue*)hQ;
	//queue is empty
	if (queueIsEmpty(hQ)) {
		if (pStatus != NULL)
			*pStatus = FAILURE;
		return 0;
	}
	if (pStatus != NULL)
		*pStatus = SUCCESS;
	return pQ->tail->item;
}


Status queuePrintFrontToRear(QUEUE hQ, ItemType type)
{
	Queue *pQ = (Queue*)hQ;
	if (queueIsEmpty(hQ))
		return FAILURE;
	Node *temp = pQ->head;
	while (temp != NULL) {
		if (type == IS_CHAR)
			printf("%c\n", temp->item);
		else if (type == IS_INT)
			printf("%d\n", temp->item);
		else
			printf("%f\n", temp->item);
		temp = temp->next;
	}
	return SUCCESS;
}


Status queuePrintRearToFront(QUEUE hQ, ItemType type)
{
	Queue *pQ = (Queue*)hQ;
	if (queueIsEmpty(hQ))
		return FAILURE;
	Node *temp = pQ->tail;
	while (temp != NULL) {
		if (type == IS_CHAR)
			printf("%c\n", temp->item);
		else if (type == IS_INT)
			printf("%d\n", temp->item);
		else
			printf("%f\n", temp->item);
		temp = temp->prev;
	}
	return SUCCESS;
}


Boolean queueIsEmpty(QUEUE hQ)
{
	Queue* pQ = (Queue*)hQ;
	if (pQ->head == NULL)
		return TRUE;
	return FALSE;
}


void queueDestroy(QUEUE *phQ)
{
	Queue* pQ = (Queue*)*phQ;
	Node *temp = pQ->head, *temp2;
	while (temp != NULL) {
		temp2 = temp->next;
		free(temp);
		temp = temp2;
	}
	free(pQ);
	*phQ = NULL;
}
