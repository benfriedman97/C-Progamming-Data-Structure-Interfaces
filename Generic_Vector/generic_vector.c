#include <stdio.h>
#include <stdlib.h>
#include "generic_vector.h"

typedef struct generic_vector {
	int size,
		capacity;
	ITEM *data;
	void(*item_destroy)(ITEM* phItem);
	Status(*item_assignment)(ITEM* pLeft, ITEM right);
	// void(*item_print)(ITEM item);
} Generic_vector;


GENERIC_VECTOR generic_vector_init_default(
	Status(*item_assignment)(ITEM* pLeft, ITEM right),
	void(*item_destroy)(ITEM* phItem))
	//void(*item_print)(ITEM item))
{
	//allocate space for memory footprint
	Generic_vector* pVector = (Generic_vector*)malloc(sizeof(Generic_vector));
	//check for malloc failure. If not, set up the vector
	if (pVector != NULL) {
		pVector->size = 0;
		pVector->capacity = 1;
		pVector->data = (ITEM*)malloc(sizeof(ITEM) * pVector->capacity);
		//check if this malloc failed as well. Destroy things if so
		if (pVector->data == NULL) {
			free(pVector);
			return NULL;
		}
		//Set the remaining indexes to NULL indicating that no object is stored there.
		for (int i = 0; i < pVector->capacity; i++)
			pVector->data[i] = NULL;
		//
		pVector->item_assignment = item_assignment;
		pVector->item_destroy = item_destroy;
		//pVector->item_print = item_print;
	}
	return (GENERIC_VECTOR)pVector;
}


void generic_vector_destroy(GENERIC_VECTOR* phVector)
{
	Generic_vector* pVector = (Generic_vector*)*phVector;	//cast to known type
	int i;

	if (pVector != NULL) {
		for (i = 0; i < pVector->size; i++)	    //free objects one by one
			pVector->item_destroy(&(pVector->data[i]));
		free(pVector->data);	//free the array
		free(pVector);	    //free the memory footprint
		*phVector = NULL;	//avoid dangling pointer (see previous lecture notes for explanation)
	}
}


Status generic_vector_push_back(GENERIC_VECTOR hVector, ITEM value)
{
	Generic_vector* pVector = (Generic_vector*)hVector;	//cast to the known type
	ITEM *temp;
	int i;

	//if there's not enough room, make room
	if (pVector->size >= pVector->capacity) {
		//create new array of correct size, check for failure
		temp = (ITEM*)malloc(sizeof(ITEM) * pVector->capacity * 2);
		if (temp == NULL)
			return FAILURE;
		//copy addresses of objects into new array
		for (i = 0; i < pVector->size; i++)
			temp[i] = pVector->data[i];
		//initialize the unused indexes as NULL indicating there's no objects
		pVector->capacity *= 2;
		for (; i < pVector->capacity; i++)
			temp[i] = NULL;
		free(pVector->data);	//free the old array w/o the new item
		pVector->data = temp;	//assign pVector->data the array with new correct size
	}

	pVector->item_assignment(&(pVector->data[pVector->size]), value);
	pVector->size++;
	return SUCCESS;
}


int generic_vector_get_size(GENERIC_VECTOR hVector)
{
	Generic_vector* pVector = (Generic_vector*)hVector; //cast to the known type
	return pVector->size;
}


int generic_vector_get_capacity(GENERIC_VECTOR hVector)
{
	Generic_vector* pVector = (Generic_vector*)hVector; //cast to the known type
	return pVector->capacity;
}


ITEM generic_vector_at(GENERIC_VECTOR hVector, int index)
{
	Generic_vector* pVector = (Generic_vector*)hVector; //cast to known type

	//Return failure if out of bounds
	if (index >= pVector->size || index < 0)
		return NULL;
	//Return address if not out of bounds
	return pVector->data[index];
}


Status generic_vector_pop_back(GENERIC_VECTOR hVector)
{
	Generic_vector* pVector = (Generic_vector*)hVector;	//cast to known type

	//if it's empty, return failure status
	if (generic_vector_empty(hVector))
		return FAILURE;
	pVector->item_destroy(&(pVector->data[--pVector->size]));
	return SUCCESS;
}


Boolean generic_vector_empty(GENERIC_VECTOR hVector)
{
	Generic_vector* pVector = (Generic_vector*)hVector;	//cast to known type
	if (pVector->size <= 0)
		return TRUE;
	return FALSE;
}
