#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"


typedef struct node {
	int data;
	char* key;
	struct node *previous, *next;
} Node;

Status list_head_insert(NODE* phList, char* key, int data) {
	Node** head = (Node**)phList;

	// Key doesn't already exist. Perform head insertion.
	Node* newHead = (Node*)malloc(sizeof(Node));
	if (newHead == NULL)
		return FAILURE;
	unsigned keyLen = strlen(key);
	newHead->key = (char*)malloc(sizeof(char) * (keyLen + 1));
	if (newHead->key == NULL) {
		free(newHead);
		return FAILURE;
	}
	for (unsigned i = 0; i < keyLen; i++)
		newHead->key[i] = key[i];
	newHead->key[keyLen] = '\0';
	newHead->data = data;
	newHead->previous = NULL;
	newHead->next = *head;
	
	if (*head != NULL)
		(*head)->previous = newHead;
	*head = newHead;
	return SUCCESS;
}


Status list_tail_insert(NODE* phList, char* key, int data) {
	Node** head = (Node**)phList;

	// create the node
	Node* newTail = (Node*)malloc(sizeof(Node));
	if (newTail == NULL)
		return FAILURE;
	unsigned keyLen = strlen(key);
	newTail->key = (char*)malloc(sizeof(char) * (keyLen + 1));
	if (newTail->key == NULL) {
		free(newTail);
		return FAILURE;
	}
	for (unsigned i = 0; i < keyLen; i++)
		newTail->key[i] = key[i];
	newTail->key[keyLen] = '\0';
	newTail->data = data;
	newTail->next = NULL;
	
	// empty list
	if (*head == NULL) {
		newTail->previous = NULL;
		*head = newTail;
	}
	else {
		// get the tail
		Node* current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = newTail;
		newTail->previous = current;
	}
	
	return SUCCESS;
}


void list_update_existing_node(NODE hNode, int data) {
	Node* node = (Node*)hNode;
	node->data = data;
}


Status list_remove(NODE* phList, char* key) {
	Node** head = (Node**)phList;

	// list size 0
	if (*head == NULL)
		return FAILURE;
	// list size 1
	else if ((*head)->next == NULL) {
		if (!strcmp((*head)->key, key)) {
			free((*head)->key);
			free(*head);
			*head = NULL;
			return SUCCESS;
		}
	}
	// list size > 1
	else {
		Node* previous = NULL;
		Node* current = *head;
		Node* next = (*head)->next;
		while (current != NULL) {
			// found node to be removed
			if (!strcmp(current->key, key)) {
				free(current->key);
				free(current);
				// node to be removed is head node
				if (previous == NULL) {
					next->previous = NULL;
					(*head) = next;
				}
				// node to be removed is tail node
				else if (next == NULL) {
					previous->next = NULL;
				}
				// node to be removed is in the middle
				else {
					previous->next = next;
					next->previous = previous;
				}
				return SUCCESS;
			}
			// continue searching for node to be removed
			else {
				previous = current;
				current = next;
				if (current != NULL)
					next = next->next;
			}
		}
		return FAILURE;
	}
	return FAILURE;
}


void list_destroy(NODE *phList) {
	Node** head = (Node**)phList;
	if (*head != NULL) {
		Node* current = *head;
		Node* next = current->next;
		free(current->key);
		free(current);
		while (next != NULL) {
			current = next;
			next = next->next;
			free(current->key);
			free(current);
		}
		*phList = NULL;
	}
}


Boolean list_is_empty(NODE hList, Status *pStatus) {
	Node* head = (Node*)hList;
	return head == NULL;
}


Boolean list_key_exists(NODE hList, char* key, NODE* pFoundNode, int* pData) {
	Node* head = (Node*)hList;
	Node** foundNode = (Node**)pFoundNode;
	Node* current = head;
	
	while (current != NULL) {
		if (!strcmp(current->key, key)) {
			if (foundNode != NULL)
				*foundNode = current;
			if (pData != NULL)
				*pData = current->data;
			return TRUE;
		}
		current = current->next;
	}

	if (foundNode != NULL)
		*foundNode = NULL;
	if (pData != NULL)
		*pData = 0;
	return FALSE;
}


Status list_get_data_by_key(NODE hList, char* key, int* pData) {
	Node* head = (Node*)hList;
	Node* current = head;
	while (current != NULL) {
		if (!strcmp(current->key, key)) {
			*pData = current->data;
			return SUCCESS;
		}
		current = current->next;
	}
	*pData = 0;
	return FAILURE;
}


Status list_print_head_to_tail(NODE hList) {
	Node* head = (Node*)hList;
	if (head == NULL) {
		printf("Error. List is empty. Cannot print.\n");
		return FAILURE;
	}

	Node* current = head;
	while (current != NULL) {
		printf("%-10s%d\n", current->key, current->data);
		current = current->next;
	}
	return SUCCESS;
}


Status list_print_head_to_tail_one_line(NODE hList) {
	Node* head = (Node*)hList;
	if (head == 0) {
		printf("Error. List is empty. Cannot print.\n");
		return FAILURE;
	}

	Node* current = head;
	char buffer[100];
	char spacing[] = "\n            ";
	unsigned count = 0;
	while (current != NULL) {
		sprintf_s(buffer, 50, "%s %d", current->key, current->data);
		printf("%-15s", buffer);
		count++;
		if (count == 5) {
			printf("%s", spacing);
			count = 0;
		}
		current = current->next;
	}
	printf("\n");
	return SUCCESS;
}

Status list_debug(NODE hList) {
	Node* head = (Node*)hList;
	if (head == NULL) {
		printf("Error. List is empty. Cannot print.\n");
		return FAILURE;
	}

	Node* current = head;
	while (current != NULL) {
		if (current->previous == NULL) printf("Previous: NULL\n");
		else printf("Previous: %p\n", current->previous);
		printf("Current: %p  Data: %d  Key: %s\n", current, current->data, current->key);
		if (current->next == NULL) printf("Next: NULL\n");
		else printf("Next: %p\n\n\n", current->next);
		current = current->next;
	}
	return SUCCESS;
}













