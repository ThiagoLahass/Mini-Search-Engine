#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "PageRank.h"
#include "RBT_PAGE.h"

#define ALPHA 0.85

static RBT_PAGE* read_graph_file(RBT_PAGE* rbt, char* graph_file_name, int pages_amount, char** page_names_vector);
static void compute_page_pr(RBT_PAGE* rbt, char* page_name, int pages_amount);

RBT_PAGE* page_rank_algorithm(RBT_PAGE* rbt, char* graph_file_name, int pages_amount){
    char** page_names_vector = calloc(pages_amount, sizeof(char*));
    
    // Sets up the rbt of pages
    rbt = read_graph_file(rbt, graph_file_name, pages_amount, page_names_vector);

    double stop_value = 1;
    // Updates
    while(stop_value > 0.000001){
        int i = 0;
        for(i=0; i<pages_amount; i++){
            set_prev_page_rank(RBT_PAGE_get(rbt, page_names_vector[i]));
        }
        for(i=0; i<pages_amount; i++){
            compute_page_pr(rbt, page_names_vector[i], pages_amount);
        }

        // Calculate E(k)
        double summation = 0.0;
        for(i=0; i<pages_amount; i++){
            Page* current_page = RBT_PAGE_get(rbt, page_names_vector[i]);
            summation += fabs(get_page_rank(current_page) - get_prev_page_rank(current_page));
        }
        stop_value = (double)summation / pages_amount;
    }
    
    for(int i=0;i<pages_amount;i++){
        free(page_names_vector[i]);
    }
    free(page_names_vector);

    return rbt;
}


static RBT_PAGE* read_graph_file(RBT_PAGE* rbt, char* graph_file_name, int pages_amount, char** page_names_vector){
    FILE *graph_file = fopen(graph_file_name, "r");
    if(graph_file == NULL){
        printf("\n Erro 001: Função page_rank_algorithm: Erro Ao abrir arquivo\n");
        exit(0);
    }

    int current_index_vector = 0;

    char* page_name = NULL;
    int links_amount = 0;
    char* token = NULL;
    char* line = NULL;
    size_t sizeLine = 0;
    while(getline(&line, &sizeLine, graph_file) != -1){
        token = strtok(line, " \t\n");                          // Reading page name
        page_name = strdup(token);

        page_names_vector[current_index_vector] = page_name;
        current_index_vector++;

        token = strtok(NULL, " \t\n");                          // Reading the amount of outgoing links
        links_amount = atoi(token);

        // Initializing the page being read
        Page* page = init_page(page_name, (double)1/pages_amount, links_amount);

        // Insert page in the rbt
        rbt = RBT_PAGE_insert(rbt, get_page_name(page), page);
        
    }

    fseek(graph_file, 0, SEEK_SET);                             // move o ponteiro do arquivo para a posição inicial

    while(getline(&line, &sizeLine, graph_file) != -1){
        token = strtok(line, " \t\n");                          // Reading influenced page name

        token = strtok(NULL, " \t\n");                          // Reading the amount of outgoing links
        links_amount = atoi(token);

        // Reading the outgoing links and incrementing the number of influenced pages for each one
        int i = 0;
        for(i = 0; i<links_amount; i++){
            token = strtok(NULL, " \t\n");
            Page* influencer_page = RBT_PAGE_get(rbt, token);
            increment_influenced_pages_amount(influencer_page);
        }
    }

    fseek(graph_file, 0, SEEK_SET);                             // move o ponteiro do arquivo para a posição inicial

    while(getline(&line, &sizeLine, graph_file) != -1){
        token = strtok(line, " \t\n");                          // Reading influenced page name
        page_name = token;
        
        token = strtok(NULL, " \t\n");                          // Reading the amount of outgoing links
        links_amount = atoi(token);

        // Reading the outgoing links and inserting the current influenced page into their vectors
        int i = 0;
        for(i = 0; i<links_amount; i++){
            token = strtok(NULL, " \t\n");
            Page* influencer_page = RBT_PAGE_get(rbt, token);
            if(get_current_index_influenced_pages(influencer_page) == 0)    // Checks if the vector has already been initialized
                init_influenced_pages(influencer_page);
            add_influenced_page(influencer_page, page_name);
            increment_current_index_influenced_pages(influencer_page);   
        }
    }

    free(line);
    fclose(graph_file);
    return rbt;
}

void compute_page_pr(RBT_PAGE* rbt, char* page_name, int pages_amount){
    Page* current_page = RBT_PAGE_get(rbt, page_name);

    // Summation
    double summation = 0.0;
    int outgoing_links_amount = get_outgoing_links_amount(current_page);
    int i = 0;
    int influenced_pages_amount = get_influenced_pages_amount(current_page);
    for(i = 0; i<influenced_pages_amount; i++){
        Page* current_influenced_page = RBT_PAGE_get(rbt, get_influenced_page(current_page, i));
        summation += get_prev_page_rank(current_influenced_page) / (double)get_outgoing_links_amount(current_influenced_page);
    }
    double new_pr = (summation*ALPHA) + ((double)(1-ALPHA) / pages_amount);

    if(get_outgoing_links_amount(current_page) == 0)
        new_pr += ALPHA*get_prev_page_rank(current_page);

    set_page_rank(current_page, new_pr);
}
