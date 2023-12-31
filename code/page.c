#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "page.h"

int compare_page_rank(const void * a, const void * b);

struct page {
    char* name;
    double prev_page_rank;
    double page_rank;
    int outgoing_links_amount;
    char** influenced_pages; // Set of pages that link to this one
    int influenced_pages_amount;
    int current_index_influenced_pages;
};

Page* init_page(char *name, double page_rank, int outgoing_links_amount) {
    Page* new = malloc(sizeof(Page));
    new->name = strdup(name);
    new->prev_page_rank = 0;
    new->page_rank = page_rank;
    new->outgoing_links_amount = outgoing_links_amount;
    new->influenced_pages = NULL;
    new->influenced_pages_amount = 0;
    new->current_index_influenced_pages = 0;

    return new;
}

char* get_page_name(Page *page) {
    return page->name;
}

double get_prev_page_rank(Page *page) {
    return page->prev_page_rank;
}

void set_page_rank(Page *page, double page_rank) {
    page->page_rank = page_rank;
}

void set_prev_page_rank(Page *page) {
    page->prev_page_rank = get_page_rank(page);
}

void increment_influenced_pages_amount(Page *page) {
    page->influenced_pages_amount++;
}

void increment_current_index_influenced_pages(Page *page) {
    page->current_index_influenced_pages++;
}

double get_page_rank(Page *page) {
    return page->page_rank;
}

int get_influenced_pages_amount(Page *page) {
    return page->influenced_pages_amount;
}

int get_current_index_influenced_pages(Page *page) {
    return page->current_index_influenced_pages;
}

char* get_influenced_page(Page *page, int index) {
    if(page->influenced_pages_amount != 0)
        return page->influenced_pages[index];
    else
        return NULL;
}

int get_outgoing_links_amount(Page *page) {
    return page->outgoing_links_amount;
}

void init_influenced_pages(Page *page) {
    if(page->influenced_pages_amount != 0)
        page->influenced_pages = calloc(page->influenced_pages_amount, sizeof(char*));
}

void add_influenced_page(Page *page, char* page_name) {
    page->influenced_pages[page->current_index_influenced_pages] = strdup(page_name);
}

void destruct_page(Page *page) {
    free(page->name);
    int i = 0;
    for(i = 0; i < page->influenced_pages_amount; i++){
        free(page->influenced_pages[i]);
    }
    if(page->influenced_pages_amount != 0)
        free(page->influenced_pages);
    free(page);
}

void sort_pages_by_page_rank(Page** v_pages, int tam_v_pages) {
    qsort(v_pages, tam_v_pages, sizeof(Page*), compare_page_rank);
}

int compare_page_rank(const void * a, const void * b) {
    // Converter os void pointers para o tipo apropriado
    const Page* page1 = *(const Page**)a;
    const Page* page2 = *(const Page**)b;

    double pagerank1 = page1->page_rank;
    double pagerank2 = page2->page_rank;

    // Comparação decrescente de page rank
    if (pagerank1 < pagerank2) {
        return 1;
    } else if (pagerank1 > pagerank2) {
        return -1;
    } else {
        // Em caso de empate, ordem lexicográfica da string
        return strcmp(page1->name, page2->name);
    }
}