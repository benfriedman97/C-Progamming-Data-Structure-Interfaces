#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#include "status.h"
#include "linked_list.h"

typedef void* HASH_TABLE;

/* Precondition: none
   Postcondition: returns a handle to an empty hash table with the given capacity.
   Returns NULL upon any memory allocation failiures */
HASH_TABLE ht_create(unsigned capacity);

/* Precondition: hTable is a handle to a hash table, key and data are the key-data
   pair to be inserted into the hash table.
   Postcondition: returns SUCCESS if the data and key are successfully created. If they key
   already exists, the data will get overridden. Returns FAILURE for memory allocation failure */
Status ht_insert(HASH_TABLE hTable, char* key, int data);

/* Precondition: hTable is a handle to a hash table, key is the key of the entry to be updated,
   index is the index in the hash table where it's located, and data is the updated data
   Postcondition: the node with the key has had it's data updated. This function should be used
   in conjunction with ht_key_exists to first see if a key exists. If it does, you can call this
   to update the entry */
void ht_update_elemment(HASH_TABLE hTable, char* key, unsigned index, int data);

/* Precondition: hTable is a handle to a hash table, key is the key to be looked for
   Postcondition: if the key exists, returns SUCCESS and removes the key-data pair.
   Else returns FAILURE */
Status ht_remove(HASH_TABLE hTable, char* key);

/* Precondition: phTable is a pointer to a handle to a hash table.
   Postcondition: all memory associated with the hash table has been freed
   and the handle has been set to NULL */
void ht_destroy(HASH_TABLE* phTable);

/* Precondition: key is the key to be hashed, capacity is the capacity of the hash table
   Postcondition: returns an index formed from hashing */
unsigned ht_hash(char* key, unsigned capacity);

/* Precondition: hTable is a handle to a hash table, key is the key to be looked for
   Postcondition: returns true or false if the key exists in the hash table. If it does,
   it stores the index of the key-data pair in pIndex and it's data value in pData. If false,
   a -1 is stored in pIndex and a 0 in pData*/
Boolean ht_key_exists(HASH_TABLE hTable, char* key, unsigned * pIndex, int* pData);

/* Precondition: hTable is a handle to a hash table, key is the key to be looked for
   Postcondition: if the key exists, returns SUCCESS and stores the data value in "data".
   Else returns FAILURE and stores a 0 in data */
Status ht_get_data_by_key(HASH_TABLE hTable, char* key, int* data);

/* Prints the hash table for debugging purposes */
void ht_print(HASH_TABLE hTable);

#endif
