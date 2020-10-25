#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "random_queue_linked_list.h"

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


Status queueServiceRandom(QUEUE hQ)
{
	Queue *pQ = (Queue*)hQ;
	//queue is empty
	if (queueIsEmpty(hQ))
		return FAILURE;
	//size 1
	int random = rand(), i;
	if (pQ->size == 1) {
		free(pQ->head);
		pQ->head = pQ->tail = NULL;
	}
	//size 2
	else if (pQ->size == 2) {
		if (random % 2) {
			free(pQ->head);
			pQ->tail->prev = NULL;
			pQ->head = pQ->tail;
		}
		else {
			free(pQ->tail);
			pQ->head->next = NULL;
			pQ->tail = pQ->head;
		}
	}
	//size 3 or greater
	else {
		Node *temp, *tempPrev, *tempNext;
		int n = pQ->size * ((double)random / RAND_MAX);
		temp = pQ->head; tempPrev = temp->prev;
		tempNext = temp->next;
		for (i = 0; i < n; i++) {
			tempPrev = temp;
			temp = tempNext;
			tempNext = tempNext->next;
		}
		//still on head node
		if (temp == pQ->head) {
			free(pQ->head);
			tempNext->prev = NULL;
			pQ->head = tempNext;
		}
		//at tail node
		else if (temp == pQ->tail) {
			free(pQ->tail);
			tempPrev->next = NULL;
			pQ->tail = tempPrev;
		}
		//somewhere in the middle
		else {
			free(temp);
			tempPrev->next = tempNext;
			tempNext->prev = tempPrev;
		}
	}
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
