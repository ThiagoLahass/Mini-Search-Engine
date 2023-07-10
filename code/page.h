#ifndef PAGE_H
#define PAGE_H

typedef struct page Page;

Page* init_page(char* name, double page_rank, int outgoing_links_amount);

char* get_page_name(Page* page);

double get_prev_page_rank(Page* page);

double get_page_rank(Page* page);

int get_influenced_pages_amount(Page* page);

int get_current_index_influenced_pages(Page* page);

char* get_influenced_page(Page* page, int index);

int get_outgoing_links_amount(Page* page);

void set_page_rank(Page* page, double page_rank);

void set_prev_page_rank(Page* page);

void increment_influenced_pages_amount(Page* page);

void increment_current_index_influenced_pages(Page* page);

void init_influenced_pages(Page* page);

void add_influenced_page(Page* page, char* page_name);

void destruct_page(Page* page);

void sort_pages_by_page_rank(Page** v_pages, int tam_v_pages);

#endif /* PAGE_H */