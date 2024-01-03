#include "hash.h"
#include "speck.h"

#include <assert.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//
// Constructor for a HashTable.
//
// length: Length of the HashTable.
// salt:   Salt for the HashTable.
//
HashTable *ht_create(uint32_t length) {
  HashTable *ht = (HashTable *)malloc(sizeof(HashTable));
  if (ht) {
    ht->salt[0] = 0x85ae998311115ae3; // Il nome  della  rosa
    ht->salt[1] = 0xb6fac2ae33a40089;
    ht->length = length;
    ht->heads = (ListNode **)calloc(length, sizeof(ListNode *));
    return ht;
  }
  return (HashTable *)NIL;
}

//
// Destructor for a HashTable.
//
// ht: The HashTable
//
void ht_delete(HashTable *ht) {
  for (uint32_t i = 0; i < ht->length; i++) {
    if (ht->heads[i] != NIL) {
      ll_delete(ht->heads[i]);
    }
  }
  free(ht->heads);
  free(ht);
}

//
//Searches a HashTable for a key
//Returns the ListNode if found and returns NULL otherwise
//This should call the ll_lookup() function.
//
//ht: The HashTable.
//key: The key to search for
//
ListNode *ht_lookup(HashTable *ht, char *key) {
  assert(key);
  uint32_t position = (hash(ht->salt, key) % ht->length);
  return ll_lookup(&ht->heads[position], key);
}

//
//First creates a new ListNod from Goodspeak.
//The created ListNode is then inserted into a HashTable.
//This should call the ll_insert() function.
//
//ht: The HashTable
//gs: The GoodSpeak to add to the HashTable.
//
void ht_insert(HashTable *ht, GoodSpeak *gs) {
  assert(gs);
  uint32_t position = (hash(ht->salt, gs->old_speak) % ht->length);
  ht->heads[position] = ll_insert(&ht->heads[position], gs);
  return;
}
