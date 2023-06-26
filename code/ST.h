#ifndef ST_H
#define ST_H

#include <stdbool.h>
#include "RBT.h"

typedef int Value;
typedef int Key;

typedef struct st ST;

// Create an empty symbol table.
ST* ST_init();

// Put key-value pair into the table: a[key] = val; .
void ST_put(ST* st, Key key, Value val);

// Value paired with key: a[key] .
Value ST_get(ST* st, Key key);

// Is there a value paired with key?
bool ST_contains(ST* st, Key key);

// Remove key (and its value) from table.
void ST_delete(ST* st, Key key);

// Is the table empty?
bool ST_empty(ST* st);

// Number of key-value pairs in the table.
int ST_size( ST* st );

// Clean up the table memory.
void ST_finish(ST* st);

// Smallest key.
Key ST_min(ST* st);

// Largest key.
Key ST_max(ST* st);

// Largest key less than or equal to key.
Key ST_floor(ST* st, Key key);

// Smallest key greater than to equal to key.
Key ST_ceiling(ST* st, Key key);

// Number of keys less than key.
int ST_rank(ST* st, Key key);

// Delete smallest key.
void ST_delmin(ST* st);

// Delete largest key.
void ST_delmax(ST* st);

// Visit all the key-value pairs in the order of their keys.
void ST_traverse(ST* st, void (*visit)(RBT*));

// Print ST
void ST_print(ST* st);


#endif /* ST_H */