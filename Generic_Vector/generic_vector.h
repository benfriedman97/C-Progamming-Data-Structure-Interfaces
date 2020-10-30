#ifndef GENERIC_VECTOR_H
#define GENERIC_VECTOR_H

#include "status.h"
#include "generic.h"

//Generic vector handle
typedef void* GENERIC_VECTOR;


/*Precondition: item_assignment is a function that creates a deep copy of the item to
  be stored in the vector. item_destroy destroys items stored in the vector.
  Postcondition: returns a handle to an empty vector*/
GENERIC_VECTOR generic_vector_init_default(
	Status(*item_assignment)(ITEM* pLeft, ITEM right),
	void(*item_destroy)(ITEM* phItem));


/*Precondition: phVector is a pointer to a handle to a vector or pointer to NULL
  Postcondition: the vector has been destroyed. If the handle to the vector didn't actually
  point to a vector and pointed to NULL, then nothing happens*/
void generic_vector_destroy(GENERIC_VECTOR* phVector);


/*Precondition: hVector is a handle to a vector and value is an item corresponding
  to the type of object that that particular vector stores
  Postcondition: a deep copy of value has been inserted into the vector and SUCCESS
  is returned. If it fails to insert a deep copy due to any memory allocation failure,
  it returns FAILURE*/
Status generic_vector_push_back(GENERIC_VECTOR hVector, ITEM value);


/*Precondition: hVector is a handle to a vector
  Postcondition: returns the size of the vector*/
int generic_vector_get_size(GENERIC_VECTOR hVector);


/*Precondition: hVector is a handle to a vector
  Postcondition: returns the capacity of the vector*/
int generic_vector_get_capacity(GENERIC_VECTOR hVector);


/*Precondition: hVector is a handle to a vector. index is an index of an item stored in the vector.
  Postcondition: returns the address of the item object stored at that index. If the index is out
  of bounds, it returns NULL.*/
ITEM generic_vector_at(GENERIC_VECTOR hVector, int index);


/*Precondition: hVector is a handle to a vector.
  Postcondition: destroys the last item stored in vector, decreases the vector size by 1, and returns
  SUCCESS. Returns FAILURE if the vector was empty*/
Status generic_vector_pop_back(GENERIC_VECTOR hVector);


/*Precondition: hVector is a handle to a vector.
  Postcondition: returns TRUE is the vector is empty, else FALSE.*/
Boolean generic_vector_empty(GENERIC_VECTOR hVector);

#endif
