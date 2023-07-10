#include <stdio.h>
#include <stdlib.h>
#include "ST.h"

struct st {
    RBT* rbt;
};

ST* ST_init(){
    ST* new = calloc(1, sizeof(ST));
    new->rbt = RBT_init();
    return new;
}

void ST_put(ST* st, Key key, Value val){
    st->rbt = RBT_insert(st->rbt, key, val);
}

RBT_STRING* ST_get(ST* st, Key key) {
    return RBT_get(st->rbt, key);
}

void ST_finish(ST* st){
    RBT_finish(st->rbt);
    free(st);
}