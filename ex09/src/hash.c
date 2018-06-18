#include "../include/hash.h"
#include "../include/linked_list.h"
#include <stdlib.h>
#include <stddef.h>

hashtable_t     *hash_create(unsigned int size)
{
  if (size <= 0)
    return NULL;
  hashtable_t *tbl = (hashtable_t *) malloc(sizeof(hashtable_t));
  tbl->size = size;
  tbl->table = (void **) malloc(sizeof(void *) * size);
  for (int i = 0; i < size; i++)
    tbl->table[i] = NULL;
  return tbl;
}

void 			hash_destroy(hashtable_t *ht, void (*fp)(void *data))
{
  node_t *tmp;
	for(int i = 0; i < ht->size; i++)
	  if(ht->table[i] != NULL)
		{
			tmp = ht->table[i];
			list_destroy(&tmp, fp);
		}
	free(ht->table);
	ht->table = NULL;
	free(ht);
}

unsigned int 		hash_func(char *key)
{
	if(key == NULL)
		return 0;
	int res = 0;
	for(int i = 0; *key != '\0'; i++, key++)
		res += *(key);
	return res;
}

void 			hash_set(hashtable_t *ht, char *key, void *ptr, void (*fp)(void *data))
{
	unsigned int i = hash_func(key) % ht->size;
	if(ht->table[i] == NULL)
		ht->table[i] = list_create(ptr);
	else	list_push(ht->table[i], ptr);
	fp(key);
}

void 			*hash_get(hashtable_t *ht, char *key)
{
	int i = hash_func(key) % ht->size;
	if(ht->table[i] == NULL)
		return NULL;
	node_t *tmp = ht->table[i];
	return tmp->data;
}
