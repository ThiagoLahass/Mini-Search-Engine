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
RBT_STRING* RBT_STRING_insert(RBT_STRING *rbt, Key_s key);

// Is there a value paired with key?
bool RBT_STRING_contains(RBT_STRING* st, Key_s key);

// Number of key-value pairs in the rbt
int RBT_STRING_size( RBT_STRING* st );

// Clean up the rbt memory.
void RBT_STRING_finish(RBT_STRING* st);

// Visit all the key-value pairs in the order of their keys.
void RBT_STRING_traverse(RBT_STRING* st, char ** pag);

#endif /* RBTRBT_STRING_H */