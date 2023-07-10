#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "RBT_PAGE.h"
#include "page.h"

#define RED     true
#define BLACK   false

struct node {
    Key key;            // Sorted by key.
    Page* val;          // Associated data.
    bool color;         // Bow color
    RBT_PAGE *l, *r;    // Left and right subtrees.
};


static RBT_PAGE* create_node(Key key, Value_p val, bool color){
    RBT_PAGE* h =  calloc(1, sizeof(RBT_PAGE));
    h->key = get_page_name(val);
    h->val = val;
    h->l = NULL;
    h->r = NULL;
    h->color = color;

    return h;
}

static int compare( char* key1, char* key2 ){
    return strcasecmp(key1, key2);
}

static bool is_red(RBT_PAGE *rbt) {
    if (rbt == NULL){
        return BLACK;
    }
    return rbt->color; //RED == true
}

static RBT_PAGE* rotate_left(RBT_PAGE *rbt) {
    RBT_PAGE *x = rbt->r;
    rbt->r = x->l;
    x->l = rbt;
    x->color = x->l->color;
    x->l->color = RED;
    return x;
}

static RBT_PAGE* rotate_right(RBT_PAGE *rbt) {
    RBT_PAGE *x = rbt->l;
    rbt->l = x->r;
    x->r = rbt;
    x->color = x->r->color;
    x->r->color = RED;
    return x;
}

static void flip_colors(RBT_PAGE *rbt) {
    rbt->color = RED;
    rbt->l->color = BLACK;
    rbt->r->color = BLACK;
}

RBT_PAGE* RBT_PAGE_init(){
    return NULL;
}

RBT_PAGE* RBT_PAGE_insert(RBT_PAGE *rbt, Key key, Value_p val) {
    // Insert at bottom and color it red.
    if (rbt == NULL) {
        return create_node(key, val, RED);
    }
    int cmp = compare(key, rbt->key);
    if (cmp < 0) {
        rbt->l = RBT_PAGE_insert(rbt->l, key, val);
    }
    else if (cmp > 0) {
        rbt->r = RBT_PAGE_insert(rbt->r, key, val);
    }
    else /*cmp == 0*/ {
        rbt->val = val;
    }

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

static Page* rec_get(RBT_PAGE*rbt, Key key) {
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

Page* RBT_PAGE_get(RBT_PAGE* rbt, Key key) {
    return rec_get(rbt, key);
}

static RBT_PAGE* rec_libera(RBT_PAGE* rbt){
    if( rbt != NULL ){
        rec_libera(rbt->l);
        rec_libera(rbt->r);
        destruct_page(rbt->val);
        free(rbt);
    }
    return NULL;
}

void RBT_PAGE_finish(RBT_PAGE* rbt){
    rbt = rec_libera(rbt);
}