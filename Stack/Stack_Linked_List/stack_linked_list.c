#include <stdlib.h>
#include "stack_linked_list.h"

typedef struct node {
	Item item;
	struct node *next;
} Node;

typedef struct stack {
	Node *head;
} Stack;

STACK stackInitDefault(void)
{
	Stack *pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack != NULL)
		pStack->head = NULL;
	return (STACK)pStack;
}


Status stackPush(STACK hStack, Item item)
{
	Stack *pStack = (Stack*)hStack;
	Node *temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL)
		return FAILURE;
	temp->item = item;
	temp->next = pStack->head;
	pStack->head = temp;
	return SUCCESS;
}


Status stackPop(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;
	Node *temp;
	if (!stackIsEmpty(hStack)) {
		temp = pStack->head->next;
		free(pStack->head);
		pStack->head = temp;
		return SUCCESS;
	}
	return FAILURE;
}


Item stackGetTopItem(STACK hStack, Status *pStatus)
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


Status stackPrintTopToBottom(STACK hStack, ItemType type)
{
	Status status;
	if (stackIsEmpty(hStack, &status))
		return FAILURE;
	Stack *pStack = (Stack*)hStack;
	Node *temp = pStack->head;
	while (temp != NULL) {
		if (type == IS_CHAR)
			printf("%c\n", temp->item);
		else if (type == IS_INT)
			printf("%d\n", temp->item);
		else if (type == IS_DOUBLE || IS_FLOAT)
			printf("%f\n", temp->item);
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
	free(pStack);
	*phStack = NULL;
}
