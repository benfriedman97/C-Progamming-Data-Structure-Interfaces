#include <stdlib.h>
#include <stdio.h>
#include "stack_index_items.h"
#define STACK_IS_EMPTY -99
typedef struct stack_array {
	int size;
	int capacity;
	int *stack;
	//all 0's or 1's, so using char saves space instead of int
	char *duplicates;
	int dupCapacity;
} Stack;

STACK stackInitDefault(int capacity)
{
	Stack *pStack = (Stack*)malloc(sizeof(Stack)); 
	int i;
	if (pStack != NULL) {
		pStack->stack = (int*)malloc(sizeof(int) * capacity);
		if (pStack->stack == NULL) {
			free(pStack);
			return NULL;
		}
		pStack->size = 0;
		pStack->capacity = capacity;

		pStack->duplicates = (char*)malloc(sizeof(char) * capacity);
		if (pStack->duplicates == NULL) {
			free(pStack->stack);
			free(pStack);
			return NULL;
		}
		for (i = 0; i < capacity; i++)
			pStack->duplicates[i] = 0;
		pStack->dupCapacity = capacity;	
	}
	return (STACK)pStack;
}


Status stackPush(STACK hStack, int item, Status *pStatus)
{
	if (item < 0)
		return FAILURE;

	int *temp, i;
	char *temp2;
	Stack *pStack = (Stack*)hStack;

	//resize duplicates if necessary
	if (item >= pStack->dupCapacity) {
		temp2 = (char*)malloc(sizeof(char) * (item + 1));
		if (temp2 == NULL)
			return FAILURE;
		for (i = 0; i < pStack->dupCapacity; i++)
			temp2[i] = pStack->duplicates[i];
		for (; i < item + 1; i++)
			temp2[i] = 0;
		free(pStack->duplicates);
		pStack->duplicates = temp2;
		pStack->dupCapacity = item + 1;
	}

	//resize stack if necessary
	if (pStack->size >= pStack->capacity) {
		temp = (int*)malloc(sizeof(int) * pStack->capacity * 2);
		if (temp == NULL)
			return FAILURE;
		for (i = 0; i < pStack->size; i++)
			temp[i] = pStack->stack[i];
		free(pStack->stack);
		pStack->stack = temp;
		pStack->capacity *= 2;
	}
	//insert item
	if (pStack->duplicates[item] == 0) {
		pStack->duplicates[item] = 1;
		pStack->stack[pStack->size++] = item;
		if (pStatus != NULL)
			*pStatus = SUCCESS;
	}
	else
		if (pStatus != NULL)
			*pStatus = FAILURE;
	return SUCCESS;
}


Status stackPop(STACK hStack)
{
	if (stackIsEmpty(hStack))
		return FAILURE;
	Stack *pStack = (Stack*)hStack;
	Status status;
	pStack->duplicates[stackGetTopItem(hStack, &status)] = 0;
	pStack->size--;
	return SUCCESS;
}


Boolean stackIsEmpty(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;
	if (pStack->size <= 0)
		return TRUE;
	return FALSE;
}


int stackGetTopItem(STACK hStack, Status *pStatus)
{
	if (stackIsEmpty(hStack)) {
		if (pStatus != NULL)
			*pStatus = FAILURE;
		return 0;
	}
	Stack *pStack = (Stack*)hStack;
	if (pStatus != NULL)
		*pStatus = SUCCESS;
	return pStack->stack[pStack->size - 1];
}


Status stackPrintTopToBottom(STACK hStack)
{
	Stack *pStack = (Stack*)hStack;
	if (stackIsEmpty(hStack))
		return FAILURE;
	for (int i = 0; i < pStack->size; i++)
		printf("%d\n", pStack->stack[i]);
	return SUCCESS;
}


void stackDestroy(STACK *phStack)
{
	Stack *pStack = (Stack*)*phStack;
	free(pStack->stack);
	free(pStack->duplicates);
	free(pStack);
	*phStack = NULL;
}
