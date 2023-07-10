#ifndef ST_H
#define ST_H

#include <stdbool.h>
#include "RBT.h"

typedef struct st ST;

// Create an empty symbol table.
ST* ST_init();

// Put key-value pair into the table: a[key] = val; .
void ST_put(ST* st, Key key, Value val);

// Value paired with key: a[key] .
RBT_STRING* ST_get(ST* st, Key key);

// Clean up the table memory.
void ST_finish(ST* st);

#endif /* ST_H */