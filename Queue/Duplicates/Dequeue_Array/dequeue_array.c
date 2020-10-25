#include <stdlib.h>
#include <stdio.h>
#include "dequeue_array.h"

typedef struct queue {
	int size, capacity,
		indexOfFront,
		indexOfRear;
	Item *data;
} Queue;

QUEUE queueInitDefault(void)
{
	Queue *pQ = (Queue*)malloc(sizeof(Queue));
	if (pQ != NULL) {
		pQ->size = 0;
		pQ->capacity = 5;	//arbitrary
		pQ->indexOfFront = pQ->indexOfRear = 0;
		pQ->data = (Item*)malloc(sizeof(Item) * pQ->capacity);
		if (pQ->data == NULL) {
			free(pQ);
			return NULL;
		}
	}
	return (QUEUE)pQ;
}


Status queueEnqueueFront(QUEUE hQ, Item item)
{
	Queue *pQ = (Queue*)hQ;
	Item *temp;
	int i;

	if (pQ->size >= pQ->capacity) {
		temp = (Item*)malloc(sizeof(Item) * pQ->capacity * 2);
		if (temp == NULL)
			return FAILURE;
		for (i = 0; i < pQ->size; i++)
			temp[i] = pQ->data[(pQ->indexOfFront + i) % pQ->capacity];
		free(pQ->data);
		pQ->data = temp;
		pQ->indexOfFront = 0;
		pQ->indexOfRear = pQ->size - 1;
		pQ->capacity *= 2;
	}
	if (!queueIsEmpty(hQ))
		pQ->indexOfFront = (pQ->indexOfFront + pQ->capacity - 1) % pQ->capacity;
	pQ->data[(pQ->indexOfRear + pQ->capacity - pQ->size++) % pQ->capacity] = item;
	//alternative way (simpler to read but more lines of code)
	/*if (!queueIsEmpty(hQ)) {
		if (pQ->indexOfFront == 0)
			pQ->indexOfFront = pQ->capacity - 1;
		else
			pQ->indexOfFront--;
	}
	pQ->data[pQ->indexOfFront] = item;
	pQ->size++;*/
	return SUCCESS;
}


Status queueEnqueueRear(QUEUE hQ, Item item)
{
	Queue *pQ = (Queue*)hQ;
	Item *temp;
	int i;
	
	if (pQ->size >= pQ->capacity) {
		temp = (Item*)malloc(sizeof(Item) * pQ->capacity * 2);
		if (temp == NULL)
			return FAILURE;
		for (i = 0; i < pQ->size; i++)
			temp[i] = pQ->data[(pQ->indexOfFront + i) % pQ->capacity];
		free(pQ->data);
		pQ->data = temp;
		pQ->indexOfFront = 0;
		pQ->indexOfRear = pQ->size - 1;
		pQ->capacity *= 2;
	}
	if (!queueIsEmpty(hQ))
		pQ->indexOfRear = (pQ->indexOfRear + pQ->capacity + 1) % pQ->capacity;
	pQ->data[(pQ->indexOfFront + pQ->size++) % pQ->capacity] = item;
	return SUCCESS;
	//alternative way (simpler to read but more lines of code)
	/*if (!queueIsEmpty(hQ)) {
		if (pQ->indexOfRear == pQ->capacity - 1)
			pQ->indexOfRear = 0;
		else
			pQ->indexOfRear++;
	}
	pQ->data[pQ->indexOfRear] = item;
	pQ->size++;*/
}


Status queueServiceFront(QUEUE hQ)
{
	Queue* pQ = (Queue*)hQ;
	if (queueIsEmpty(hQ))
		return FAILURE;
	pQ->size--;
	if (!queueIsEmpty(hQ))
		pQ->indexOfFront = (pQ->indexOfFront + 1) % pQ->capacity;
	//alternative way (simpler to read but more lines of code)
	/*if (pQ->size > 1) {
		if (pQ->indexOfFront == pQ->capacity - 1)
			pQ->indexOfFront = 0;
		else
			pQ->indexOfFront++;
	}
	pQ->size--;*/
	return SUCCESS;
}


Status queueServiceRear(QUEUE hQ)
{
	Queue* pQ = (Queue*)hQ;
	if (queueIsEmpty(hQ))
		return FAILURE;
	pQ->size--;
	if (!queueIsEmpty(hQ))
		pQ->indexOfRear = (pQ->indexOfRear + pQ->capacity - 1) % pQ->capacity;
	//alternative way (simpler to read but more lines of code)
	/*if (pQ->size > 1) {
		if (pQ->indexOfRear == 0)
			pQ->indexOfRear = pQ->capacity - 1;
		else
			pQ->indexOfRear--;
	}
	pQ->size--;*/
	return SUCCESS;
}


Item queueGetFrontItem(QUEUE hQ, Status *pStatus)
{
	Queue* pQ = (Queue*)hQ;
	//queue is empty
	if (queueIsEmpty(hQ)) {
		if (pStatus != NULL)
			*pStatus = FAILURE;
		return 0;
	}
	//queue is not empty
	if (pStatus != NULL)
		*pStatus = SUCCESS;
	return pQ->data[pQ->indexOfFront];
}


Item queueGetRearItem(QUEUE hQ, Status *pStatus)
{
	Queue* pQ = (Queue*)hQ;
	//queue is empty
	if (queueIsEmpty(hQ)) {
		if (pStatus != NULL)
			*pStatus = FAILURE;
		return 0;
	}
	//queue is not empty
	if (pStatus != NULL)
		*pStatus = SUCCESS;
	return pQ->data[pQ->indexOfRear];
}


Status queuePrintFrontToRear(QUEUE hQ, ItemType type)
{
	if (queueIsEmpty(hQ))
		return FAILURE;
	Queue *pQ = (Queue*)hQ;
	int i, atRear = 0;
	for (i = pQ->indexOfFront; !atRear;
		i = (i + pQ->capacity + 1) % pQ->capacity) {
		if (i == pQ->indexOfRear)
			atRear = 1;
		if (type == IS_CHAR)
			printf("%c\n", pQ->data[i]);
		else if (type == IS_INT)
			printf("%d\n", pQ->data[i]);
		else
			printf("%f\n", pQ->data[i]);
	}
	return SUCCESS;
}


Status queuePrintRearToFront(QUEUE hQ, ItemType type)
{
	if (queueIsEmpty(hQ))
		return FAILURE;
	Queue *pQ = (Queue*)hQ;
	int i, atFront = 0;
	for (i = pQ->indexOfRear; !atFront;
		i = (i + pQ->capacity - 1) % pQ->capacity) {
		if (i == pQ->indexOfFront)
			atFront = 1;
		if (type == IS_CHAR)
			printf("%c\n", pQ->data[i]);
		else if (type == IS_INT)
			printf("%d\n", pQ->data[i]);
		else
			printf("%f\n", pQ->data[i]);
	}
	return SUCCESS;
}


Boolean queueIsEmpty(QUEUE hQ)
{
	Queue* pQ = (Queue*)hQ;
	return (Boolean)(pQ->size <= 0);
}


void queueDestroy(QUEUE *phQ)
{
	Queue *pQ = (Queue*)*phQ;
	free(pQ->data);
	free(pQ);
	*phQ = NULL;
}
