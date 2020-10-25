/*next means next item in the queue (front to rear, for 1 2 3, 2 is the next of 1)
  previous means previous item in the queue (rear to front, for 1 2 3, 1 is the previous of 2)*/
#include <stdlib.h>
#include "FIFO_queue_linked_list.h"

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
		pQ->size = 0;
	}
	return (QUEUE)pQ;
}


Status queueEnqueue(QUEUE hQ, Item item)
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


Status queueService(QUEUE hQ)
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

Item queueFront(QUEUE hQ, Status *pStatus)
{
	Queue *pQ = (Queue*)hQ;
	if (queueIsEmpty(hQ)) {
		if (pStatus != NULL)
			*pStatus = FAILURE;
		return 0;
	}
	if (pStatus != NULL)
		*pStatus = SUCCESS;
	return pQ->head->item;
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
	Node *current, *next;
	if (!queueIsEmpty(*phQ)) {
		current = pQ->head;		
		next = pQ->head->next;	
		free(current);			
		while (next != NULL) {	
			current = next;		
			next = next->next;	
			free(current);		
		}
	}
	free(pQ);
	*phQ = NULL;
}
