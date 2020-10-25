#include <stdlib.h>
#include <stdio.h>
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

/*Ignore-new-item policy*/
Status stackPush(STACK hStack, Item item, Boolean *pInstack)
{
	Stack *pStack = (Stack*)hStack;
	Boolean inStack = FALSE;
	if (pInstack != NULL)
		*pInstack = FALSE;

	//check if already in the stack
	Node *temp = pStack->head;
	while (temp != NULL) {
		if (temp->item == item) {
			inStack = TRUE;
			if (pInstack != NULL)
				*pInstack = TRUE;
			break;
		}
		temp = temp->next;
	}
	//insert if not in the stack
	if (!inStack) {
		temp = (Node*)malloc(sizeof(Node));
		if (temp == NULL)
			return FAILURE;
		temp->item = item;
		temp->next = pStack->head;
		pStack->head = temp;
	}
	return SUCCESS;
}


/*Replace-the-old-item policy*/
Status stackPush(STACK hStack, Item item, Boolean *pInstack)
{
	Stack *pStack = (Stack*)hStack;
	Boolean inStack = FALSE;
	Node *temp, *temp2, *newNode;
	if (pInstack != NULL)
		*pInstack = FALSE;
	//stack is empty
	if (stackIsEmpty(hStack)) {
		newNode = (Node*)malloc(sizeof(Node));
		if (newNode == NULL)
			return FAILURE;
		newNode->item = item;
		newNode->next = NULL;
		pStack->head = newNode;
		return SUCCESS;
	}
	/*Stack is not empty. Check if already in the stack. Replace if it is.*/
	temp = pStack->head, temp2 = NULL;
	while (temp != NULL) {
		if (temp->item == item) {
			inStack = TRUE;
			if (pInstack != NULL)
				*pInstack = TRUE;
			newNode = (Node*)malloc(sizeof(Node));
			if (newNode == NULL)
				return FAILURE;
			newNode->item = item;
			newNode->next = temp->next;
			if (temp2 != NULL)	//if NULL, node was first node
				temp2->next = newNode;
			else
				pStack->head = newNode;
			free(temp);
			break;
		}
		temp2 = temp;
		temp = temp->next;
	}
	//insert if not in the stack
	if (!inStack) {
		newNode = (Node*)malloc(sizeof(Node));
		if (newNode == NULL)
			return FAILURE;
		newNode->item = item;
		newNode->next = pStack->head;
		pStack->head = newNode;
	}
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
	if (stackIsEmpty(hStack))
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
