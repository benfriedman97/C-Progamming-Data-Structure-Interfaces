#include <stdlib.h>
#include <stdio.h>
#include "stack_index_items2.h"

typedef struct node {
	int item;
	struct node *next, *prev;
} Node;

typedef struct stack {
	Node *head, *tail;
	Node** duplicates;
	int dupCapacity;
} Stack;

STACK stackInitDefault(void)
{
	Stack *pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack != NULL) {
		pStack->head = pStack->tail = NULL;
		pStack->duplicates = NULL;
		pStack->dupCapacity = 0;
	}
	return (STACK)pStack;
}

/*Replace-the-old-item policy*/
Status stackPush(STACK hStack, int item, Boolean *pInstack)
{
	Stack *pStack = (Stack*)hStack;
	int i;
	Node *newNode, *temp2;

	if (pInstack != NULL)
		*pInstack = FALSE;
	//stack is empty
	if (stackIsEmpty(hStack)) {
		newNode = (Node*)malloc(sizeof(Node));
		if (newNode == NULL)
			return FAILURE;
		newNode->item = item;
		newNode->prev = newNode->next = NULL;
		pStack->head = pStack->tail = newNode;
		pStack->duplicates = (Node**)malloc(sizeof(Node*) * (item + 1));
		if (pStack->duplicates == NULL) {
			free(newNode);
			pStack->tail = pStack->head = NULL;
			return FAILURE;
		}
		for (i = 0; i < item + 1; i++)
			pStack->duplicates[i] = NULL;
		pStack->duplicates[item] = newNode;
		pStack->dupCapacity = item + 1;
		return SUCCESS;
	}

	/*Stack is not empty. Check if item is beyond the range of the array. That means
	it's definitely not in the stack*/
	if (item >= pStack->dupCapacity) {
		//put at top of stack
		newNode = (Node*)malloc(sizeof(Node));
		if (newNode == NULL)
			return FAILURE;
		newNode->item = item;
		newNode->prev = NULL;
		newNode->next = pStack->head;
		pStack->head->prev = newNode;
		pStack->head = newNode;
		//resize the array
		Node **temp = (Node**)malloc(sizeof(Node*) * (item + 1));
		//it failed, free head node and put old head node back
		if (temp == NULL) {
			temp2 = pStack->head->next;
			temp2->prev = NULL;
			free(pStack->head);
			pStack->head = temp2;
			return FAILURE;
		}
		/*Copy duplicates array into new duplicates array, set rest to NULL except index of
		item to be inserted*/
		for (i = 0; i < pStack->dupCapacity; i++)
			temp[i] = pStack->duplicates[i];
		for (; i < item; i++)
			temp[i] = NULL;
		temp[item] = newNode;
		free(pStack->duplicates);
		pStack->duplicates = temp;
		pStack->dupCapacity = item + 1;
		return SUCCESS;
	}
	
	/*Stack is not empty and item is not beyond range of array. May or may not
	be in the stack. If it is, replace old item. If not, place it at top of stack*/
	//it's in the stack
	if (pStack->duplicates[item] != NULL) {
		if (pInstack != NULL)
			*pInstack = TRUE;
		newNode = (Node*)malloc(sizeof(Node));
		if (newNode == NULL)
			return FAILURE;
		newNode->item = item;
		newNode->next = (pStack->duplicates[item])->next;
		newNode->prev = (pStack->duplicates[item])->prev;
		if (newNode->next != NULL)
			newNode->next->prev = newNode;
		else
			pStack->tail = newNode;
		if (newNode->prev != NULL)
			newNode->prev->next = newNode;
		else
			pStack->head = newNode;
		free(pStack->duplicates[item]);
		pStack->duplicates[item] = newNode;
		return SUCCESS;
	}
	//it's not in the stack
	else {
		newNode = (Node*)malloc(sizeof(Node));
		if (newNode == NULL)
			return FAILURE;
		newNode->item = item;
		newNode->prev = NULL;
		newNode->next = pStack->head;
		pStack->head->prev = newNode;
		pStack->head = newNode;
		pStack->duplicates[item] = newNode;
		return SUCCESS;
	}
}


Status stackPop(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;
	Node *temp;
	if (!stackIsEmpty(hStack)) {
		pStack->duplicates[pStack->head->item] = NULL;
		temp = pStack->head->next;
		free(pStack->head);
		pStack->head = temp;
		if (stackIsEmpty(hStack)) {
			free(pStack->duplicates);
			pStack->duplicates = NULL;
			pStack->dupCapacity = 0;
			pStack->tail = NULL;
		}
		return SUCCESS;
	}
	return FAILURE;
}


int stackGetTopItem(STACK hStack, Status *pStatus)
{
	Stack* pStack = (Stack*)hStack;
	if (!stackIsEmpty(hStack)) {
		if (pStatus != NULL)
			*pStatus = SUCCESS;
		return pStack->head->item;
	}
	else {
		if (pStatus != NULL)
			*pStatus = FAILURE;
		return 0;
	}
}


Status stackPrintTopToBottom(STACK hStack)
{
	if (stackIsEmpty(hStack))
		return FAILURE;
	Stack *pStack = (Stack*)hStack;
	Node *temp = pStack->head;
	while (temp != NULL) {
		printf("%d\n", temp->item);
		temp = temp->next;
	}
	return SUCCESS;
}


Boolean stackIsEmpty(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;
	if (pStack->head == NULL)
		return TRUE;
	return FALSE;
}


void stackDestroy(STACK *phStack)
{
	Stack* pStack = (Stack*)*phStack;
	Node *temp1 = pStack->head, *temp2;
	while (temp1 != NULL) {
		temp2 = temp1;
		temp1 = temp1->next;
		free(temp2);
	}
	if (pStack->duplicates != NULL)
		free(pStack->duplicates);
	free(pStack);
	*phStack = NULL;
}
