#ifndef PAGE_RANK_H
#define PAGE_RANK_H

#include "RBT_PAGE.h"
#include "page.h"

RBT_PAGE* page_rank_algorithm(RBT_PAGE* rbt, char* graph_file_name, int pages_amount);

#endif /* PAGE_RANK_H */