# Hash Table - Separate Chaining
This folder implements a hash table for entries whose key-data pair is a string an integer. It implements the hash table using
separate chaining with a doubly linked list. The size of the hash table is decided upon initialization. The "ht_insert" function
to insert something in the hash table allows for duplicates. However, duplicates can also be ignored by using the ht_key_exists
function to see if a key already exists, and then calling ht_update_element to update the already existing entry instead of
inserting a new entry with the same key.

The main.c is a sample program where all possible keys of size 2 are inserted in the hash table. The example_output.txt file then
shows the contents of the hash table by displaying the contents of each linked list
