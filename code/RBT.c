#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <math.h>
#include "RBT.h"

#define RED     true
#define BLACK   false

struct node {
    Key key;            // Sorted by key.
    RBT_STRING* val;    // Associated data.
    bool color;         // Bow color
    RBT *l, *r;         // Left and right subtrees.
};


RBT* create_node(Key key, Value val, bool color){
    RBT* h =  calloc(1, sizeof(RBT));
    h->key = strdup(key);
    h->val = RBT_STRING_init();
    h->val = RBT_STRING_insert(h->val, val);
    h->l = NULL;
    h->r = NULL;
    h->color = color;

    return h;
}

int compare( char* key1, char* key2 ){
    return strcasecmp(key1, key2);
}

bool is_red(RBT *rbt) {
    if (rbt == NULL){
        return BLACK;
    }
    return rbt->color; //RED == true
}

RBT* rotate_left(RBT *rbt) {
    RBT *x = rbt->r;
    rbt->r = x->l;
    x->l = rbt;
    x->color = x->l->color;
    x->l->color = RED;
    return x;
}

RBT* rotate_right(RBT *rbt) {
    RBT *x = rbt->l;
    rbt->l = x->r;
    x->r = rbt;
    x->color = x->r->color;
    x->r->color = RED;
    return x;
}

void flip_colors(RBT *rbt) {
    rbt->color = RED;
    rbt->l->color = BLACK;
    rbt->r->color = BLACK;
}

RBT* RBT_init(){
    return NULL;
}

RBT* RBT_insert(RBT *rbt, Key key, Value val) {
    // Insert at bottom and color it red.
    if (rbt == NULL) {
        return create_node(key, val, RED);
    }
    int cmp = compare(key, rbt->key);
    if (cmp < 0) {
        rbt->l = RBT_insert(rbt->l, key, val);
    }
    else if (cmp > 0) {
        rbt->r = RBT_insert(rbt->r, key, val);
    }
    else /*cmp == 0*/ {
        rbt->val = RBT_STRING_insert(rbt->val, val);
    }

    // Lean left.
    if (is_red(rbt->r) && !is_red(rbt->l)){
        rbt = rotate_left(rbt);
    }
    // Balance 4-node.
    if (is_red(rbt->l) && is_red(rbt->l->l)) {
        rbt = rotate_right(rbt);
    }
    // Split 4-node.
    if (is_red(rbt->l) && is_red(rbt->r)) {
        flip_colors(rbt);
    }

    return rbt;
}

static RBT_STRING* rec_get(RBT *rbt, Key key) {
    if (rbt == NULL) {
        return NULL;
    }
    int cmp = compare(key, rbt->key);
    if (cmp < 0) {
        return rec_get(rbt->l, key);
    }
    else if (cmp > 0) {
        return rec_get(rbt->r, key);
    }
    else /*cmp == 0*/ {
        return rbt->val;
    }
}

RBT_STRING* RBT_get(RBT* rbt, Key key) {
    return rec_get(rbt, key);
}

static RBT* rec_libera(RBT* rbt){
    if( rbt != NULL ){
        rec_libera(rbt->l);
        rec_libera(rbt->r);
        RBT_STRING_finish(rbt->val);
        free(rbt->key);
        free(rbt);
    }
    return NULL;
}

void RBT_finish(RBT* rbt){
    rbt = rec_libera(rbt);
}