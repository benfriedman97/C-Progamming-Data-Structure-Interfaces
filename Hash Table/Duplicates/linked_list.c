#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"


typedef struct node {
	int data;
	char* key;
	struct node *previous, *next;
} Node;

Node* merge_sort(Node* head);
Node* split(Node* head);
Node* merge(Node* first, Node* second);

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


Status list_copy_list(NODE hListToCopy, NODE* phNewList) {
	Node* copyHead = (Node*)hListToCopy;
	Node** pNewHead = (Node**)phNewList;

	if (*pNewHead != NULL) {
		list_destroy(phNewList);
	}

	// empty list
	if (copyHead == NULL) {
		*pNewHead = NULL;
		return SUCCESS;
	}
	else {
		Node* newHead = NULL;
		Node* current = copyHead;
		while (current != NULL) {
			if (!list_tail_insert(&newHead, current->key, current->data)) {
				list_destroy(&newHead);
				return FAILURE;
			}
			current = current->next;
		}
		*pNewHead = newHead;
		return SUCCESS;
	}
}


Status list_copy_list_modified(NODE hListToCopy, NODE* phNewList, NODE* phNewTail) {
	Node* copyHead = (Node*)hListToCopy;
	Node** pNewHead = (Node**)phNewList;
	Node** pNewTail = (Node**)phNewTail;

	if (*pNewHead != NULL) {
		list_destroy(phNewList);
	}

	// empty list
	if (copyHead == NULL) {
		*pNewHead = NULL;
		return SUCCESS;
	}
	else {
		Node* newHead = NULL;
		Node* newTail = NULL;
		Node* current = copyHead;
		while (current != NULL) {
			if (!list_tail_insert_modified(&newHead, &newTail, current->key, current->data)) {
				list_destroy(&newHead);
				return FAILURE;
			}
			current = current->next;
		}
		*pNewHead = newHead;
		*pNewTail = newTail;
		return SUCCESS;
	}
}


Status list_tail_insert_modified(NODE* phList, NODE* phNewTail, char* key, int data) {
	Node** pHead = (Node**)phList;
	Node** pTail = (Node**)phNewTail;

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
	*pTail = newTail;

	// empty list
	if (*pHead == NULL) {
		newTail->previous = NULL;
		*pHead = newTail;
	}
	else {
		// get the tail
		Node* current = *pHead;
		while (current->next != NULL)
			current = current->next;
		current->next = newTail;
		newTail->previous = current;
	}

	return SUCCESS;
}


Status list_combine_two_lists(NODE hList1, NODE hList2, NODE* phNewList, NODE* phNewListTail) {
	if (hList1 == NULL || hList2 == NULL) {
		printf("Failed to combine two lists. One was empty\n");
		return FAILURE;
	}

	// copy first list
	NODE hNewList1 = NULL;
	NODE hNewTail1 = NULL;
	if (!list_copy_list_modified(hList1, &hNewList1, &hNewTail1)) {
		return FAILURE;
	}

	// copy second list
	NODE hNewList2 = NULL;
	NODE hNewTail2 = NULL;
	if (!list_copy_list_modified(hList2, &hNewList2, &hNewTail2)) {
		list_destroy(&hNewList1);
		return FAILURE;
	}

	// append list 2 to list 1
	Node* list1Tail = (Node*)hNewTail1;
	Node* list2Head = (Node*)hNewList2;
	list1Tail->next = list2Head;
	list2Head->previous = list1Tail;
	
	Node** pNewList = (Node**)phNewList;
	*pNewList = (Node*)hNewList1;
	Node** pNewListTail = (Node**)phNewListTail;
	*pNewListTail = (Node*)hNewTail2;
	return SUCCESS;
}


Status list_mergeSort_LTG(NODE* phList) {
	Node** pList = (Node**)phList;
	if (*pList == NULL)
		return FAILURE;
	
	*pList = merge_sort(*pList);
	return SUCCESS;
}

Node* merge_sort(Node* head) {
	if (!head || !head->next)
		return head;
	Node* second = split(head);

	// recur for the left and right halves
	head = merge_sort(head);
	second = merge_sort(second);

	// merge the two sorted halves
	return merge(head, second);
}

Node* merge(Node* first, Node* second) {
	// first list is empty
	if (!first)
		return second;

	// second list is empty
	if (!second)
		return first;

	// choose smaller value
	if (strcmp(first->key, second->key) < 0) {
		first->next = merge(first->next, second);
		first->next->previous = first;
		first->previous = NULL;
		return first;
	}
	else {
		second->next = merge(first, second->next);
		second->next->previous = second;
		second->previous = NULL;
		return second;
	}
}


Node* split(Node* head) {
	Node* fast = head;
	Node* slow = head;

	while (fast->next && fast->next->next) {
		fast = fast->next->next;
		slow = slow->next;
	}

	Node* temp = slow->next;
	slow->next = NULL;
	return temp;
}
