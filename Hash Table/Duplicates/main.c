#include <stdio.h>
#include <vld.h>
#include "hash_table.h"

int main(int argc, char** argv) {
	HASH_TABLE ht = ht_create(10);
	
	char key[] = "AA";
	for (unsigned i = 0; i < 26; i++) {
		for (unsigned j = 0; j < 26; j++) {
			ht_insert(ht, key, i + j + 1);
			key[1]++;
		}
		key[1] = 'A';
		key[0]++;
	}

	ht_print(ht);
	ht_destroy(&ht);
	return 0;
}
