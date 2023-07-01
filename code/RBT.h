/* RBT DO TIPO (CHAVE(char*), VALUE(RBT_STRING*)) */

#ifndef RBT_H
#define RBT_H

#include "RBT_STRING.h"

#include <stdbool.h>

typedef char* Key;
typedef char* Value;
typedef struct node RBT;

// Create an empty Red-Black-Tree.
RBT* RBT_init();

// Put key-value pair into rbt
RBT* RBT_insert(RBT *rbt, Key key, Value val);

// Value paired with key: a->key
RBT_STRING* RBT_get(RBT* rbt, Key key);

// Is there a value paired with key?
bool RBT_contains(RBT* rbt, Key key);

// Is the rbt empty?
bool RBT_empty(RBT* rbt);

// Number of key-value pairs in the rbt
int RBT_size( RBT* rbt );

// Clean up the rbt memory.
void RBT_finish(RBT* rbt);

// Smallest key.
Key RBT_min(RBT* rbt);

// Largest key.
Key RBT_max(RBT* rbt);

// Largest key less than or equal to key.
Key RBT_floor(RBT* rbt, Key key);

// Smallest key greater than to equal to key.
Key RBT_ceiling(RBT* rbt, Key key);

// Number of keys less than key.
int RBT_rank(RBT* rbt, Key key);

// Visit all the key-value pairs in the order of their keys.
void RBT_traverse(RBT* rbt, void (*visit)(RBT*));

// Print RBT
void RBT_print(RBT* rbt);


#endif /* RBT_H */