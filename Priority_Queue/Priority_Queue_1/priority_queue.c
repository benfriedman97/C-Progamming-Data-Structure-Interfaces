#include "stdlib.h"
#include "priority_queue.h"

typedef struct item {
	int key,		//priority level. Higher = higher priority
		data;
} Item;

typedef struct queue {
	int size,
		capacity;
	Item *heap;
} Priority_queue;

void fix_up(Priority_queue *pQueue, int index);
void fix_down(Priority_queue *pQueue, int index);
int check_priority(Priority_queue *pQueue, int index);
int get_size_by_counting(Priority_queue *pQueue, int index, int *pCalls);
void print_keys(Priority_queue *pQueue);

PRIORITY_QUEUE priority_queue_init_default(void)
{
	Priority_queue *pQueue = (Priority_queue*)malloc(sizeof(Priority_queue));
	if (pQueue != NULL) {
		pQueue->size = 0;
		pQueue->capacity = 4;
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
	int i;

	/*Resize if necessary*/
	if (pQueue->size >= pQueue->capacity) {
		temp_heap = (Item*)malloc(sizeof(Item) * pQueue->capacity * 2);
		if (temp_heap == NULL)
			return FAILURE;
		for (i = 0; i < pQueue->size; i++)
			temp_heap[i] = pQueue->heap[i];
		free(pQueue->heap);
		pQueue->heap = temp_heap;
		pQueue->capacity *= 2;
	}

	/*Either resizing was not necessary or it successfully resized*/
	pQueue->heap[pQueue->size].key = priority_level;
	pQueue->heap[pQueue->size].data = data_item;

	/*Now it is placed as the last item in the heap. Fixup as necessary*/
	fix_up(pQueue, pQueue->size);
	pQueue->size++;
	return SUCCESS;
}

void fix_up(Priority_queue *pQueue, int index)
{
	/*math formula for the index of a nodes parent in a top-down left-right heap*/
	int index_of_parent = (index - 1) / 2,
		temp_key, temp_data;
	/*If index is zero, it's at the root and it can't go any higher. If not,
	check if it's larger than the parent and insert accordingly*/
	if (index != 0 && pQueue->heap[index_of_parent].key < pQueue->heap[index].key) {
		temp_key = pQueue->heap[index_of_parent].key;
		temp_data = pQueue->heap[index_of_parent].data;
		pQueue->heap[index_of_parent].key = pQueue->heap[index].key;
		pQueue->heap[index_of_parent].data = pQueue->heap[index].data;
		pQueue->heap[index].key = temp_key;
		pQueue->heap[index].data = temp_data;
		fix_up(pQueue, index_of_parent);
	}
}

Status priority_queue_service(PRIORITY_QUEUE hQueue)
{
	Priority_queue *pQueue = (Priority_queue*)hQueue;
	int temp_key, temp_data;

	/*The strategy to service is as follows: swap the first and last items,
	service the first item (now stored in the last index), fix down the last item
	(now stored in first index) until it's in the proper place*/
	if (pQueue->size > 0) {
		/*Item temp = pQueue->heap[0];
		pQueue->heap[0] = pQueue->heap[pQueue->size - 1];
		pQueue->heap[pQueue->size - 1] = temp;*/

		temp_key = pQueue->heap[0].key;
		temp_data = pQueue->heap[0].data;
		pQueue->heap[0].key = pQueue->heap[pQueue->size - 1].key;
		pQueue->heap[0].data = pQueue->heap[pQueue->size - 1].data;
		pQueue->heap[pQueue->size - 1].key = temp_key;
		pQueue->heap[--pQueue->size].data = temp_data;
		fix_down(pQueue, 0);
		return SUCCESS;
	}
	return FAILURE;
}

void fix_down(Priority_queue *pQueue, int index)
{
	int index_of_left_child = 2 * index + 1,
		index_of_right_child = 2 * index + 2,
		index_of_larger_child = -1,
		temp_key, temp_data;
	/*3 at index 1
			left child: 3
			right child: 4
			size: 5
	*/
	//1 child exists (left)
	if (index_of_left_child < pQueue->size &&
		index_of_right_child >= pQueue->size)
		index_of_larger_child = index_of_left_child;
	/*index of left child is guaranteed to be less than size of heap
	due to short circuit evaluation in above statement*/
	else if (index_of_right_child < pQueue->size) {
		/*if (pQueue->heap[index_of_left_child].key > pQueue->heap[index_of_right_child].key)
			index_of_larger_child = index_of_left_child;
		else
			index_of_larger_child = index_of_right_child;*/
		
		index_of_larger_child =
			pQueue->heap[index_of_left_child].key > pQueue->heap[index_of_right_child].key ?
			index_of_left_child : index_of_right_child;
	}

	//if index_of_larger child were -1, that means queue would be empty
	if (index_of_larger_child != -1) {
		if (pQueue->heap[index_of_larger_child].key > pQueue->heap[index].key) {
			temp_key = pQueue->heap[index_of_larger_child].key;
			temp_data = pQueue->heap[index_of_larger_child].data;
			pQueue->heap[index_of_larger_child].key = pQueue->heap[index].key;
			pQueue->heap[index_of_larger_child].data = pQueue->heap[index].data;
			pQueue->heap[index].key = temp_key;
			pQueue->heap[index].data = temp_data;
			fix_down(pQueue, index_of_larger_child);
		}
	}
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




//my functions
int priority_queue_get_size(PRIORITY_QUEUE hQueue)
{
	Priority_queue *pQueue = (Priority_queue*)hQueue;
	return pQueue->size;
}

int priority_queue_get_capacity(PRIORITY_QUEUE hQueue)
{
	Priority_queue *pQueue = (Priority_queue*)hQueue;
	return pQueue->capacity;
}

int priority_queue_get_key_front(PRIORITY_QUEUE hQueue)
{
	Priority_queue *pQueue = (Priority_queue*)hQueue;
	return pQueue->heap[0].key;
}

Status priority_queue_check_proper_priority(PRIORITY_QUEUE hQueue)
{
	Priority_queue *pQueue = (Priority_queue*)hQueue;

	return check_priority(pQueue, 0) > 1 ? FAILURE : SUCCESS;

}

int check_priority(Priority_queue *pQueue, int index)
{
	int index_of_left_child = 2 * index + 1,
		index_of_right_child = 2 * index + 1;

	//no children
	if (index_of_right_child >= pQueue->size &&
		index_of_left_child >= pQueue->size)
		return 0;
	//left child only (1)
	else if (index_of_right_child >= pQueue->size &&
		index_of_left_child < pQueue->size)
		return pQueue->heap[index].key > pQueue->heap[index_of_left_child].key ?
		0 : 1;
	//no right child only since this would never happen
	//both children
	else {
		if (pQueue->heap[index].key < pQueue->heap[index_of_left_child].key ||
			pQueue->heap[index].key < pQueue->heap[index_of_right_child].key)
			return 1;
		return check_priority(pQueue, index_of_left_child) +
			check_priority(pQueue, index_of_right_child);
	}
}

int priority_queue_get_size_by_counting(PRIORITY_QUEUE hQueue, int *pCalls)
{
	Priority_queue *pQueue = (Priority_queue*)hQueue;
	return get_size_by_counting(pQueue, 0, pCalls);
}

int get_size_by_counting(Priority_queue *pQueue, int index, int *pCalls)
{
	int index_of_left_child = 2 * index + 1,
		index_of_right_child = 2 * index + 2;
	
	(*pCalls)++;

	/*if (index >= pQueue->size)
		return 0;*/
	//no children
	if (index_of_left_child >= pQueue->size)
		return 1;
	//left child only (1)
	else if (index_of_right_child >= pQueue->size)
		return 1 + get_size_by_counting(pQueue, index_of_left_child, pCalls);	//itself and left child
	//no right child only since this would never happen
	//both children
	else {
		return 1 + get_size_by_counting(pQueue, index_of_left_child, pCalls) +
			get_size_by_counting(pQueue, index_of_right_child, pCalls);
	}
}

void priority_queue_print_keys(PRIORITY_QUEUE hQueue)
{
	Priority_queue *pQueue = (Priority_queue*)hQueue;

}

void print_keys(Priority_queue *pQueue)
{

}