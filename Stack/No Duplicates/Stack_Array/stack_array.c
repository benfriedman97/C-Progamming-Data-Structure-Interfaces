#include <stdlib.h>
#include <stdio.h>
#include "stack_array.h"

typedef struct stack_array {
	int size;
	int capacity;
	Item *stack;
} Stack;

STACK stackInitDefault(int capacity)
{
	Stack *pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack != NULL) {
		pStack->stack = (Item*)malloc(sizeof(Item) * capacity);
		if (pStack->stack == NULL) {
			free(pStack);
			return NULL;
		}
		pStack->capacity = capacity;
		pStack->size = 0;
	}
	return (STACK)pStack;
}

/*Ignore-new-item*/
//Status stackPush(STACK hStack, Item item, Boolean *pInstack)
//{
//	Item *temp; 
//	int i;
//	Stack *pStack = (Stack*)hStack;
//
//	//check for duplicate (only modification from stackPush with duplicates)
//	for (i = 0; i < pStack->size; i++)
//		if (pStack->stack[i] == item) {
//			if (pInstack != NULL)
//				*pInstack = TRUE;
//			return SUCCESS;
//		}
//	//resize if necessary
//	if (pStack->size >= pStack->capacity) {
//		temp = (Item*)malloc(sizeof(Item) * pStack->size);
//		if (temp == NULL)
//			return FAILURE;
//		for (i = 0; i < pStack->size; i++)
//			temp[i] = pStack->stack[i];
//		free(pStack->stack);
//		pStack->stack = (Item*)malloc(sizeof(Item) * pStack->capacity * 2);
//		if (pStack->stack == NULL) {
//			pStack->stack = temp;
//			return FAILURE;
//		}
//		for (i = 0; i < pStack->size; i++)
//			pStack->stack[i] = temp[i];
//		pStack->capacity *= 2;
//	}
//	//add to stack
//	pStack->stack[pStack->size++] = item;
//	if (pInstack != NULL)
//		*pInstack = FALSE;
//	return SUCCESS;
//}

/*Forget-the-old*/
Status stackPush(STACK hStack, Item item, Boolean *pInstack)
{
	Item *temp;
	int i;
	Stack *pStack = (Stack*)hStack;

	//check for duplicate (only modification from stackPush with duplicates)
	for (i = 0; i < pStack->size; i++)
		if (pStack->stack[i] == item) {
			pStack->stack[i] = item;
			if (pInstack != NULL)
				*pInstack = TRUE;
			return SUCCESS;
		}
	//resize if necessary
	if (pStack->size >= pStack->capacity) {
		temp = (Item*)malloc(sizeof(Item) * pStack->size);
		if (temp == NULL)
			return FAILURE;
		for (i = 0; i < pStack->size; i++)
			temp[i] = pStack->stack[i];
		free(pStack->stack);
		pStack->stack = (Item*)malloc(sizeof(Item) * pStack->capacity * 2);
		if (pStack->stack == NULL) {
			pStack->stack = temp;
			return FAILURE;
		}
		for (i = 0; i < pStack->size; i++)
			pStack->stack[i] = temp[i];
		pStack->capacity *= 2;
	}
	//add to stack
	pStack->stack[pStack->size++] = item;
	if (pInstack != NULL)
		*pInstack = FALSE;
	return SUCCESS;
}


Status stackPop(STACK hStack)
{
	if (stackIsEmpty(hStack))
		return FAILURE;
	Stack *pStack = (Stack*)hStack;
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


Item stackGetTopItem(STACK hStack, Status *pStatus)
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


Status stackPrintStackTopToBottom(STACK hStack, ItemType type)
{
	Stack *pStack = (Stack*)hStack;
	if (stackIsEmpty(hStack))
		return FAILURE;
	for (int i = 0; i < pStack->size; i++)
		if (type == IS_CHAR)
			printf("%c\n", pStack->stack[i]);
		else if (type == IS_INT)
			printf("%d\n", pStack->stack[i]);
		else
			printf("%f\n", pStack->stack[i]);
	return SUCCESS;
}


void stackDestroy(STACK *phStack)
{
	Stack *pStack = (Stack*)*phStack;
	free(pStack->stack);
	free(pStack);
	*phStack = NULL;
}
