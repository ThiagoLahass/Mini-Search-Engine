/* RBT DO TIPO (CHAVE(char*)) */
#ifndef RBT_STRING_H
#define RBT_STRING_H

#include <stdbool.h>

// typedef int Value_s;
typedef char* Key_s;

typedef struct node RBT_STRING;

// Create an empty Red-Black-Tree.
RBT_STRING* RBT_STRING_init();

// Put key-value pair into rbt
// RBT_STRING* RBT_STRING_insert(RBT_STRING *rbt, Key_s key, Value_s val);
RBT_STRING* RBT_STRING_insert(RBT_STRING *rbt, Key_s key);

// Is there a value paired with key?
bool RBT_STRING_contains(RBT_STRING* st, Key_s key);

// Is the rbt empty?
bool RBT_STRING_empty(RBT_STRING* st);

// Number of key-value pairs in the rbt
int RBT_STRING_size( RBT_STRING* st );

// Clean up the rbt memory.
void RBT_STRING_finish(RBT_STRING* st);

// Smallest key.
Key_s RBT_STRING_min(RBT_STRING* st);

// Largest key.
Key_s RBT_STRING_max(RBT_STRING* st);

// Largest key less than or equal to key.
Key_s RBT_STRING_floor(RBT_STRING* st, Key_s key);

// Smallest key greater than to equal to key.
Key_s RBT_STRING_ceiling(RBT_STRING* st, Key_s key);

// Number of keys less than key.
int RBT_STRING_rank(RBT_STRING* st, Key_s key);

// Visit all the key-value pairs in the order of their keys.
void RBT_STRING_traverse(RBT_STRING* st, char ** pag);

// Print RBT
void RBT_STRING_print(RBT_STRING* st);


#endif /* RBTRBT_STRING_H */