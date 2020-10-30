#include "priority_queue.h"
#include "stdlib.h"


typedef struct item {
	int key,		//priority level. Higher = higher priority
		data;
} Item;

typedef struct queue {
	int size,
		capacity;
	Item *heap;
} Priority_queue;


PRIORITY_QUEUE priority_queue_init_default(void)
{
	Priority_queue *pQueue = (Priority_queue*)malloc(sizeof(Priority_queue));
	if (pQueue != NULL) {
		pQueue->size = 0;
		pQueue->capacity = 8;
		pQueue->heap = (Item*)malloc(sizeof(Item) * pQueue->capacity);
		if (pQueue->heap == NULL) {
			free(pQueue);
			return NULL;
		}
	}
	return (PRIORITY_QUEUE)pQueue;
}


Status priority_queue_insert(PRIORITY_QUEUE hQueue, int priority_level, int data_item)
{
	Priority_queue *pQueue = (Priority_queue*)hQueue;
	Item *temp_heap;
	Item temp_item;
	int index_of_parent, index_of_item;

	//check if it needs resizing
	if (pQueue->size >= pQueue->capacity) {
		temp_heap = (Item*)malloc(sizeof(Item) * pQueue->capacity * 2);
		if (temp_heap == NULL)
			return FAILURE;
		for (int i = 0; i < pQueue->size; i++)
			temp_heap[i] = pQueue->heap[i];
		free(pQueue->heap);
		pQueue->heap = temp_heap;
		pQueue->capacity *= 2;
	}

	/*either resizing was not necessary or it successfully resized.
	Put it at the very end and then fix up accordingly*/
	pQueue->heap[pQueue->size].data = data_item;
	pQueue->heap[pQueue->size++].key = priority_level;
	//fix up
	/*index of parent in heap represented by an array is (k - 1) / 2 where k
	is index of the item. Since we increased size by 1 we must do size - 1
	for the current index*/
	index_of_item = pQueue->size - 1;
	index_of_parent = (index_of_item - 1) / 2;
	while (index_of_item != 0 && pQueue->heap[index_of_parent].key < pQueue->heap[index_of_item].key) {
		temp_item = pQueue->heap[index_of_parent];
		pQueue->heap[index_of_parent] = pQueue->heap[index_of_item];
		pQueue->heap[index_of_item] = temp_item;
		index_of_item = index_of_parent;
		index_of_parent = (index_of_item - 1) / 2;
	}
	return SUCCESS;
}


Status priority_queue_service(PRIORITY_QUEUE hQueue)
{
	Priority_queue *pQueue = (Priority_queue*)hQueue;
	Item temp_item;
	int index_of_left_child, index_of_right_child,
		index_of_higher_priority_child, 
		index_of_item;	//index of item to fix down

	//queue is empty
	if (pQueue->size <= 0)
		return FAILURE;
	//queue is not empty
	/*The strategy to service is as follows: swap the first and last items,
	service the first item (now stored in the last index), fix down the last item
	(now stored in first index) until it's in the proper place*/
	//swap first and last
	temp_item = pQueue->heap[0];
	pQueue->heap[0] = pQueue->heap[pQueue->size - 1];
	pQueue->heap[--pQueue->size] = temp_item;
	//fix down the item now stored in the first index (which was previously the last item)
	index_of_item = 0;
	index_of_left_child = 1;
	index_of_right_child = 2;
	//case 1: queue now empty
	if (index_of_left_child > pQueue->size)
		return SUCCESS;
	//case 2: no children
	else if (index_of_left_child == pQueue->size) {
		return SUCCESS;
	}
	//case 3: 1 child (index_of_left_child guaranteed to be larger than pQueue->size)
	else if (index_of_right_child == pQueue->size) {
		if (pQueue->heap[index_of_item].key < pQueue->heap[index_of_left_child].key) {
			temp_item = pQueue->heap[index_of_item];
			pQueue->heap[index_of_item] = pQueue->heap[index_of_left_child];
			pQueue->heap[index_of_left_child] = temp_item;
			return SUCCESS;
		}
	}
	//case 4: 2 children
	else if (index_of_right_child < pQueue->size) {
		//get index of larger child
		index_of_higher_priority_child =
			pQueue->heap[index_of_left_child].key > pQueue->heap[index_of_right_child].key ?
			index_of_left_child : index_of_right_child;
		//fix down while not at end of heap or has lower priority than one of the children
		while ((index_of_item < pQueue->size - 1) &&
			pQueue->heap[index_of_item].key < pQueue->heap[index_of_higher_priority_child].key) {
			//swap
			temp_item = pQueue->heap[index_of_item];
			pQueue->heap[index_of_item] = pQueue->heap[index_of_higher_priority_child];
			pQueue->heap[index_of_higher_priority_child] = temp_item;
			//get new indexes of item and the children
			index_of_item = index_of_higher_priority_child;
			index_of_left_child = 2 * index_of_item + 1;
			index_of_right_child = 2 * index_of_item + 2;
			//case 1: no more children. Do nothing, will break out of while
			if (index_of_left_child == pQueue->size)
				return SUCCESS;
			//case 2: 1 child
			else if (index_of_left_child < pQueue->size &&
				index_of_right_child >= pQueue->size)
				index_of_higher_priority_child = index_of_left_child;
			//case 3: 2 children
			else if (index_of_right_child < pQueue->size) {
				index_of_higher_priority_child =
					pQueue->heap[index_of_left_child].key > pQueue->heap[index_of_right_child].key ?
					index_of_left_child : index_of_right_child;
			}
		}
	}


	return SUCCESS;
}


int priority_queue_front(PRIORITY_QUEUE hQueue, Status* pStatus)
{
	Priority_queue *pQueue = (Priority_queue*)hQueue;

	if (priority_queue_is_empty(hQueue)) {
		if (pStatus != NULL)
			*pStatus = FAILURE;
		return EMPTY_CODE;
	}
	if (pStatus != NULL)
		*pStatus = SUCCESS;
	return pQueue->heap[0].data;
}


Boolean priority_queue_is_empty(PRIORITY_QUEUE hQueue)
{
	Priority_queue *pQueue = (Priority_queue*)hQueue;
	if (pQueue->size <= 0)
		return TRUE;
	return FALSE;
}


void priority_queue_destroy(PRIORITY_QUEUE* phQueue)
{
	Priority_queue *pPriority_queue = (Priority_queue*)*phQueue;
	free(pPriority_queue->heap);
	free(pPriority_queue);
	*phQueue = NULL;
}