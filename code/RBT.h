#ifndef RBT_H
#define RBT_H

#include <stdbool.h>

typedef int Value;
typedef int Key;

typedef struct node RBT;

// Create an empty Red-Black-Tree.
RBT* RBT_init();

// Put key-value pair into rbt
RBT* RBT_insert(RBT *rbt, Key key, Value val);

// Value paired with key: a->key
Value RBT_get(RBT* st, Key key);

// Is there a value paired with key?
bool RBT_contains(RBT* st, Key key);

// Remove key (and its value) from rbt
void RBT_delete(RBT* st, Key key);

// Is the rbt empty?
bool RBT_empty(RBT* st);

// Number of key-value pairs in the rbt
int RBT_size( RBT* st );

// Clean up the rbt memory.
void RBT_finish(RBT* st);

// Smallest key.
Key RBT_min(RBT* st);

// Largest key.
Key RBT_max(RBT* st);

// Largest key less than or equal to key.
Key RBT_floor(RBT* st, Key key);

// Smallest key greater than to equal to key.
Key RBT_ceiling(RBT* st, Key key);

// Number of keys less than key.
int RBT_rank(RBT* st, Key key);

// Delete smallest key.
void RBT_delmin(RBT* st);

// Delete largest key.
void RBT_delmax(RBT* st);

// Visit all the key-value pairs in the order of their keys.
void RBT_traverse(RBT* st, void (*visit)(RBT*));

// Print RBT
void RBT_print(RBT* st);


#endif /* RBT_H */