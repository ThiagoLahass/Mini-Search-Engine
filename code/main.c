#include <stdio.h>
#include <stdlib.h>
#include "ST.h"


int main(int argc, char* argv[]){

    int num = 1000;

    printf("Inicializando...\n");
    ST* st = ST_init();
    ST_print(st);

    printf("Preenchendo com alguns valores...\n");
    for(int i = 0; i < num; i++){
        ST_put(st, 2*i, i+100);
    }

    printf("Percorrendo e imprimindo...\n");
    // ST_print(st);

    printf("Testando funções ST...\n\n");

    printf("Get ST...\n");
    printf("ST_get(st, 2) = %d\n", ST_get(st, 2));
    printf("ST_get(st, 7) = %d\n", ST_get(st, 7));
    printf("ST_get(st, 100) = %d\n\n", ST_get(st, 100));

    printf("Contains ST...\n");
    printf("ST_contains(st, 2) = %d\n", ST_contains(st, 2));
    printf("ST_contains(st, 7) = %d\n", ST_contains(st, 7));
    printf("ST_contains(st, 100) = %d\n\n", ST_contains(st, 100));

    // printf("Delete ST...\n");
    // printf("Antes...\n");
    // ST_print(st);
    // printf("ST_contains(st, 2) = %d\n", ST_contains(st, 2));
    // printf("ST_delete(st,2)\n");
    // ST_delete(st, 2);
    // printf("ST_contains(st, 2) = %d\n", ST_contains(st, 2));
    // printf("Depois...\n");
    // ST_print(st);

    printf("Empty ST...\n");
    printf("ST_empty(st) = %d\n\n", ST_empty(st));

    printf("Min ST...\n");
    printf("ST_min(st) = %d\n\n", ST_min(st));

    printf("Max ST...\n");
    printf("ST_max(st) = %d\n\n", ST_max(st));

    printf("Floor ST...\n");
    printf("ST_floor(st,3) = %d\n\n", ST_floor(st, 3));

    printf("Ceiling ST...\n");
    printf("ST_ceiling(st,3) = %d\n\n", ST_ceiling(st, 3));

    printf("Rank ST...\n");
    printf("ST_rank(st,5) = %d\n\n", ST_rank(st, 5));

    printf("Liberando ST...\n");
    ST_finish(st);

    return 0;
}