#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "string.h"
#include "RBT_STRING.h"
#include "RBT_PAGE.h"

#define RED     true
#define BLACK   false
struct node {
    Key_s key;          // Sorted by key.
    bool color;         // Bow color
    RBT_STRING *l, *r;  // Left and right subtrees.
    int size;           // Number of nodes in subtree
};

static RBT_STRING* create_node(Key_s key, bool color){
    RBT_STRING* h =  calloc(1, sizeof(RBT_STRING));
    h->key = strdup(key);
    h->l = NULL;
    h->r = NULL;
    h->size = 1;
    h->color = color;

    return h;
}

static int size(RBT_STRING *rbt) {
    if (rbt == NULL){
        return 0;
    }
    else{
        return rbt->size;
    }
}

int RBT_STRING_size( RBT_STRING* rbt ) {
    return size(rbt);
}

static int compare( char* key1, char* key2 ){
    return strcasecmp(key1, key2);
}

static bool is_red(RBT_STRING *rbt) {
    if (rbt == NULL){
        return BLACK;
    }
    return rbt->color; //RED == true
}

static RBT_STRING* rotate_left(RBT_STRING *rbt) {
    RBT_STRING *x = rbt->r;
    rbt->r = x->l;
    x->l = rbt;
    x->color = x->l->color;
    x->l->color = RED;
    return x;
}

static RBT_STRING* rotate_right(RBT_STRING *rbt) {
    RBT_STRING *x = rbt->l;
    rbt->l = x->r;
    x->r = rbt;
    x->color = x->r->color;
    x->r->color = RED;
    return x;
}

static void flip_colors(RBT_STRING *rbt) {
    rbt->color = RED;
    rbt->l->color = BLACK;
    rbt->r->color = BLACK;
}

RBT_STRING* RBT_STRING_init(){
    return NULL;
}

RBT_STRING* RBT_STRING_insert(RBT_STRING *rbt, Key_s key) {
    // Insert at bottom and color it red.
    if (rbt == NULL) {
        return create_node(key, RED);
    }
    int cmp = compare(key, rbt->key);
    if (cmp < 0) {
        rbt->l = RBT_STRING_insert(rbt->l, key);
    }
    else if (cmp > 0) {
        rbt->r = RBT_STRING_insert(rbt->r, key);
    }
    else /*cmp == 0*/ {
        //Not to-do
    }

    if (is_red(rbt->r) && !is_red(rbt->l)){
        rbt = rotate_left(rbt);
        rbt->l->size = size(rbt->l->l) + size(rbt->l->r) + 1;
    }
    // Balance 4-node.
    if (is_red(rbt->l) && is_red(rbt->l->l)) {
        rbt = rotate_right(rbt);
        rbt->r->size = size(rbt->r->l) + size(rbt->r->r) + 1;

    }
    // Split 4-node.
    if (is_red(rbt->l) && is_red(rbt->r)) {
        flip_colors(rbt);
    }

    rbt->size = size(rbt->l) + size(rbt->r) + 1;
    return rbt;
}

static bool rec_contains(RBT_STRING *rbt, Key_s key) {
    if (rbt == NULL) {
        return false;
    }
    int cmp = compare(key, rbt->key);
    if (cmp < 0) {
        return rec_contains(rbt->l, key);
    }
    else if (cmp > 0) {
        return rec_contains(rbt->r, key);
    }
    else /*cmp == 0*/ {
        return true;
    }
}

bool RBT_STRING_contains(RBT_STRING* rbt, Key_s key){
    return rec_contains(rbt, key);
}

static RBT_STRING* rec_libera(RBT_STRING* rbt){
    if( rbt != NULL ){
        rec_libera(rbt->l);
        rec_libera(rbt->r);
        free(rbt->key);
        free(rbt);
    }
    return NULL;
}

void RBT_STRING_finish(RBT_STRING* rbt){
    rbt = rec_libera(rbt);
}

static void rec_traverse(RBT_STRING* rbt, char ** pag, int * aux ) {
    if (rbt == NULL) {
        return;
    }
    rec_traverse(rbt->l, pag, aux);
    pag[(*aux)++] = rbt->key;
    rec_traverse(rbt->r, pag, aux);
}

void RBT_STRING_traverse(RBT_STRING* rbt, char ** pag) {
    int aux = 0;
    rec_traverse(rbt, pag, &aux);

}