#include <stdio.h>
#include <stdlib.h>
#include "ST.h"

struct st {
    RBT* rbt;
    // int size;
};


int ST_size( ST* st ) {
    if (st == NULL){
        return 0;
    }
    else{
        return RBT_size(st->rbt);
    }
}


ST* ST_init(){
    ST* new = calloc(1, sizeof(ST));
    // new->size = 1;
    new->rbt = RBT_init();

    return new;
}


void ST_put(ST* st, Key key, Value val){
    st->rbt = RBT_insert(st->rbt, key, val);
    // st->size = ST_size(st);
}

RBT_STRING* ST_get(ST* st, Key key) {
    return RBT_get(st->rbt, key);
}


bool ST_contains(ST* st, Key key){
    return RBT_contains(st->rbt, key);
}


bool ST_empty(ST* st){
    return RBT_empty(st->rbt);
}


void ST_finish(ST* st){
    RBT_finish(st->rbt);
    free(st);
}


Key ST_min(ST* st){
    return RBT_min(st->rbt);
}


Key ST_max(ST* st){
    return RBT_max(st->rbt);
}


Key ST_floor(ST* st, Key key) {
    return RBT_floor(st->rbt, key);
}


Key ST_ceiling(ST* st, Key key) {
    return RBT_ceiling(st->rbt, key);
}


int ST_rank(ST* st, Key key) {
    return RBT_rank(st->rbt, key);
}


void ST_traverse(ST* st, void (*visit)(RBT*)) {
    RBT_traverse(st->rbt, visit);
}

void ST_print(ST* st){
    RBT_print(st->rbt);
}