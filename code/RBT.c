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
    int size;           // Number of nodes in subtree
};


RBT* create_node(Key key, Value val, bool color){
    RBT* h =  calloc(1, sizeof(RBT));
    h->key = strdup(key);
    h->val = RBT_STRING_init();
    h->val = RBT_STRING_insert(h->val, val);
    h->l = NULL;
    h->r = NULL;
    h->size = 1;
    h->color = color;

    return h;
}

static int size(RBT *rbt) {
    if (rbt == NULL){
        return 0;
    }
    else{
        return rbt->size;
    }
}

int RBT_size( RBT* rbt ) {
    return size(rbt);
}


int RBT_get_left_size( RBT* rbt ){
    return size(rbt->l);
}

int RBT_get_right_size( RBT* rbt ){
    return size(rbt->r);
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
        // printf("Inserindo na esquerda..\n");
        rbt->l = RBT_insert(rbt->l, key, val);
    }
    else if (cmp > 0) {
        // printf("Inserindo na direita..\n");
        rbt->r = RBT_insert(rbt->r, key, val);
    }
    else /*cmp == 0*/ {
        rbt->val = RBT_STRING_insert(rbt->val, val);
    }

    // puts("\n\n");
    // RBT_print(rbt);
    // puts("\n\n");

    // Lean left.
    // printf("\nrbt: %d, color: %d\n", rbt->key, rbt->color );
    if (is_red(rbt->r) && !is_red(rbt->l)){
        // printf("Rotate left before (%d)\n", rbt->key);
        rbt = rotate_left(rbt);
        // printf("Rotate left after (%d)\n", rbt->key);
        rbt->l->size = size(rbt->l->l) + size(rbt->l->r) + 1;
    }
    // Balance 4-node.
    if (is_red(rbt->l) && is_red(rbt->l->l)) {
        // printf("Rotate right before (%d)\n", rbt->key);
        rbt = rotate_right(rbt);
        // printf("Rotate right after (%d)\n", rbt->key);
        rbt->r->size = size(rbt->r->l) + size(rbt->r->r) + 1;

    }
    // Split 4-node.
    if (is_red(rbt->l) && is_red(rbt->r)) {
        // printf("Color flip (%d)\n", rbt->key);
        flip_colors(rbt);
    }

    // puts("\n\nAntes de refazer os sizes...\n");
    // RBT_print(rbt);
    // puts("\n\n");

    rbt->size = size(rbt->l) + size(rbt->r) + 1;

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

bool RBT_contains(RBT* rbt, Key key){
    return rec_get(rbt, key) != NULL;
}


static RBT* rec_min(RBT *rbt) {
    if (rbt->l == NULL) {
        return rbt;
    }
    return rec_min(rbt->l);
}

Key RBT_min(RBT* rbt){
    RBT* min = rec_min(rbt);
    return min->key;
}


static RBT* rec_max(RBT *rbt) {
    if (rbt->r == NULL) {
        return rbt;
    }
    return rec_max(rbt->r);
}

Key RBT_max(RBT* rbt){
    RBT* max = rec_max(rbt);
    return max->key;
}


bool RBT_empty(RBT* rbt){
    return rbt == NULL;
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

static RBT* rec_floor(RBT *rbt, Key key) {
    if (rbt == NULL) {
        return NULL;
    }
    int cmp = compare(key, rbt->key);
    if (cmp == 0) {
        return rbt;
    }
    if (cmp < 0) {
        return rec_floor(rbt->l, key);
    }
    RBT *t = rec_floor(rbt->r, key);
    if (t != NULL){
        return t;
    }
    else{
        return rbt;
    }
}

Key RBT_floor(RBT* rbt, Key key) {
    RBT *n = rec_floor(rbt, key);
    if (n == NULL) {
        return NULL;
    }
    else{ 
        return n->key;
    }
}


static RBT* rec_ceiling(RBT *rbt, Key key) {
    if (rbt == NULL) {
        return NULL;
    }
    int cmp = compare(key, rbt->key);
    if (cmp == 0) {
        return rbt;
    }
    if (cmp > 0) {
        return rec_ceiling(rbt->r, key);
    }
    RBT *t = rec_ceiling(rbt->l, key);
    if (t != NULL){
        return t;
    }
    else{
        return rbt;
    }
}

Key RBT_ceiling(RBT* rbt, Key key) {
    RBT *n = rec_ceiling(rbt, key);
    if (n == NULL) {
        return NULL;
    }
    else{ 
        return n->key;
    }
}


static int rec_rank(RBT *rbt, Key key) {
    if (rbt == NULL) {
        return 0;
    }
    int cmp = compare(key, rbt->key);
    if (cmp < 0) {
        return rec_rank(rbt->l, key);
    }
    else if (cmp > 0) {
        return 1+size(rbt->l)+rec_rank(rbt->r, key);
    }
    else /*cmp == 0*/ {
        return size(rbt->l);
    }
}

int RBT_rank(RBT* rbt, Key key) {
    return rec_rank(rbt, key);
}


static void rec_traverse(RBT *rbt, void (*visit)(RBT*)) {
    if (rbt == NULL) {
        return;
    }
    rec_traverse(rbt->l, visit);
    visit(rbt);
    rec_traverse(rbt->r, visit);
}

void RBT_traverse(RBT* rbt, void (*visit)(RBT*)) {
    rec_traverse(rbt, visit);
}

void RBT_print(RBT* rbt){
    printf("< ");
    if( rbt != NULL ){
        // printf("key: %s | Color: %d | size: %d", rbt->key, rbt->color, rbt->size);
        printf("%s", rbt->key);
        // printf(" | Pages:\n");
        // RBT_STRING_print(rbt->val);
        // printf("\n");
        RBT_print(rbt->l);
        RBT_print(rbt->r);
    }
    printf("> ");
}