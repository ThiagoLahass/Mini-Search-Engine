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

// Clean up the rbt memory.
void RBT_finish(RBT* rbt);

#endif /* RBT_H */