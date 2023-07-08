/* RBT DO TIPO (CHAVE(char*), VALUE(PAGE*)) */

#ifndef RBT_PAGE_H
#define RBT_PAGE_H

#include <stdbool.h>
#include "page.h"

typedef char* Key;
typedef Page* Value_p;
typedef struct node RBT_PAGE;

// Create an empty Red-Black-Tree.
RBT_PAGE* RBT_PAGE_init();

// Put key-value pair into rbt
RBT_PAGE* RBT_PAGE_insert(RBT_PAGE *rbt, Key key, Value_p val);

// Value paired with key: a->key
Page* RBT_PAGE_get(RBT_PAGE* rbt, Key key);

// Is there a value paired with key?
bool RBT_PAGE_contains(RBT_PAGE* rbt, Key key);

// Clean up the rbt memory.
void RBT_PAGE_finish(RBT_PAGE* rbt);

#endif /* RBT_PAGE_H */