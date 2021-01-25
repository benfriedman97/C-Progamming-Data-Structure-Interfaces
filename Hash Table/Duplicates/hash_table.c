#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash_table.h"

typedef struct hash_table {
	NODE* hash_table;
	unsigned capacity;
} Hash_table;


HASH_TABLE ht_create(unsigned capacity) {
	Hash_table* ht = (Hash_table*)malloc(sizeof(Hash_table));
	if (ht != NULL) {
		ht->hash_table = (NODE*)malloc(sizeof(NODE) * capacity);
		if (ht->hash_table == NULL) {
			free(ht);
			return NULL;
		}
		for (unsigned i = 0; i < capacity; i++)
			ht->hash_table[i] = NULL;
		ht->capacity = capacity;
	}
	return (HASH_TABLE)ht;
}


Status ht_insert(HASH_TABLE hTable, char* key, int data) {
	Hash_table* ht = (Hash_table*)hTable;
	unsigned index = ht_hash(key, ht->capacity);
	return list_head_insert(&(ht->hash_table[index]), key, data);
}

void ht_update_element(HASH_TABLE hTable, char* key, unsigned index, int data) {
	Hash_table* ht = (Hash_table*)hTable;
	NODE nodeToUpdate = NULL;
	list_key_exists(ht->hash_table[index], key, &nodeToUpdate, NULL);
	list_update_existing_node(nodeToUpdate, data);
}

Status ht_remove(HASH_TABLE hTable, char* key) {
	Hash_table* ht = (Hash_table*)hTable;
	unsigned index = ht_hash(key, ht->capacity);
	return list_remove(&(ht->hash_table[index]), key);
}


void ht_destroy(HASH_TABLE* phTable) {
	Hash_table* ht = (Hash_table*)*phTable;
	for (unsigned i = 0; i < ht->capacity; i++) {
		list_destroy(&(ht->hash_table[i]));
	}
	free(ht->hash_table);
	free(ht);
	*phTable = NULL;
}


unsigned ht_hash(char* key, unsigned capacity) {
	unsigned sum = 0;
	unsigned keyLen = strlen(key);
	for (unsigned i = 0; i < keyLen; i++)
		sum += key[i];
	return sum % capacity;
}


Boolean ht_key_exists(HASH_TABLE hTable, char* key, unsigned *pIndex, int* pData) {
	Hash_table* ht = (Hash_table*)hTable;
	unsigned index = ht_hash(key, ht->capacity);
	if (ht->hash_table[index] == NULL)
		return FALSE;
	if (list_key_exists(ht->hash_table[index], key, NULL, pData)) {
		if (pIndex != NULL)
			*pIndex = index;
		return TRUE;
	}
	if (pIndex != NULL)
		*pIndex = -1;
	return FALSE;
}


Status ht_get_data_by_key(HASH_TABLE hTable, char* key, int* data) {
	Hash_table* ht = (Hash_table*)hTable;
	unsigned index = ht_hash(key, ht->capacity);
	if (ht->hash_table[index] == NULL) {
		*data = 0;
		return FAILURE;
	}
	return list_get_data_by_key(ht->hash_table[index], key, data);
}


void ht_print(HASH_TABLE hTable) {
	Hash_table* ht = (Hash_table*)hTable;
	for (unsigned i = 0; i < ht->capacity; i++) {
		printf("Index: %-5d", i);
		if (ht->hash_table[i] == NULL)
			printf("NULL\n");
		else {
			list_print_head_to_tail_one_line(ht->hash_table[i]);
		}
	}

}
