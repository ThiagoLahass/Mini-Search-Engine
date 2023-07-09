#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "RBT_PAGE.h"
#include "page.h"

#define NULL_Key ((char*)NULL)
#define NULL_Value ((Page*)NULL)

#define RED     true
#define BLACK   false

struct node {
    Key key;        // Sorted by key.
    Page* val;      // Associated data.
    bool color;     // Bow color
    RBT_PAGE *l, *r;     // Left and right subtrees.
    int size;       // Number of nodes in subtree
};


static RBT_PAGE* create_node(Key key, Value_p val, bool color){
    RBT_PAGE* h =  calloc(1, sizeof(RBT_PAGE));
    h->key = get_page_name(val);
    h->val = val;
    h->l = NULL;
    h->r = NULL;
    h->size = 1;
    h->color = color;

    return h;
}

static int size(RBT_PAGE *rbt) {
    if (rbt == NULL){
        return 0;
    }
    else{
        return rbt->size;
    }
}

int RBT_PAGE_size( RBT_PAGE* rbt ) {
    return size(rbt);
}


int RBT_PAGE_get_left_size( RBT_PAGE* rbt ){
    return size(rbt->l);
}

int RBT_PAGE_get_right_size( RBT_PAGE* rbt ){
    return size(rbt->r);
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
        // printf("Inserindo na esquerda..\n");
        rbt->l = RBT_PAGE_insert(rbt->l, key, val);
    }
    else if (cmp > 0) {
        // printf("Inserindo na direita..\n");
        rbt->r = RBT_PAGE_insert(rbt->r, key, val);
    }
    else /*cmp == 0*/ {
        rbt->val = val;
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

static Page* rec_get(RBT_PAGE*rbt, Key key) {
    if (rbt == NULL) {
        return NULL_Value;
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

bool RBT_PAGE_contains(RBT_PAGE* rbt, Key key){
    return rec_get(rbt, key) != NULL_Value;
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

void RBT_PAGE_print(RBT_PAGE* rbt){
    printf("< ");
    if( rbt != NULL ){
        printf("%s", rbt->key);
        printf(" pg = %.8f", get_page_rank(rbt->val));
        RBT_PAGE_print(rbt->l);
        RBT_PAGE_print(rbt->r);
    }
    printf("> ");
}

static void rec_traverse(RBT_PAGE *rbt, void (*visit)(Page*)) {
    if (rbt == NULL) {
        return;
    }
    rec_traverse(rbt->l, visit);
    visit(rbt->val);
    rec_traverse(rbt->r, visit);
}

void RBT_PAGE_traverse(RBT_PAGE* rbt, void (*visit)(Page*)) {
    rec_traverse(rbt, visit);
}