#include <stdlib.h>
#include "FIFO_queue_array.h"

typedef struct queue {
	int size,
		capacity,
		index_of_front;
	Item *data;
} Queue;


QUEUE queueInitDefault(void)
{
	Queue *pQ = (Queue*)malloc(sizeof(Queue));
	if (pQ != NULL) {
		pQ->size = 0;
		pQ->capacity = 10;	//arbitrary
		pQ->index_of_front = 0;
		pQ->data = (Item*)malloc(sizeof(Item) * pQ->capacity);
		if (pQ->data == NULL) {
			free(pQ);
			return NULL;
		}
	}
	return (QUEUE)pQ;
}


Status queueEnqueue(QUEUE hQ, Item item)
{
	Queue *pQ = (Queue*)hQ; 
	Item *temp;
	int i;
	//resize if necessary
	if (pQ->size >= pQ->capacity) {
		temp = (Item*)malloc(sizeof(Item) * pQ->capacity * 2);
		if (temp == NULL)
			return FAILURE;
		for (i = 0; i < pQ->size; i++)
			temp[i] = pQ->data[(pQ->index_of_front + i) % pQ->capacity];
		pQ->index_of_front = 0;
		free(pQ->data);
		pQ->data = temp;
		pQ->capacity *= 2;
	}
	//Was enough room or made room
	pQ->data[(pQ->index_of_front + pQ->size++) % pQ->capacity] = item;
	return SUCCESS;
}


Status queueService(QUEUE hQ)
{
	Queue* pQ = (Queue*)hQ;
	if (queueIsEmpty(hQ))
		return FAILURE;
	pQ->size--;
	/*In all cases index_of_front moves up by 1 except when
	it's in the last index which is why we need this code
	instead of pQ->index_of_front++*/
	pQ->index_of_front = (pQ->index_of_front + 1) % pQ->capacity;
	return SUCCESS;
}


Item queueFront(QUEUE hQ, Status *pStatus)
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
	return pQ->data[pQ->index_of_front];
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
