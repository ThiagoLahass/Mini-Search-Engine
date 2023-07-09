#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RBT_STRING.h"
#include "RBT_PAGE.h"
#include "ST.h"
#include "PageRank.h"

#define MAX_DIRNAME_SIZE 500
#define MAX_FILENAME_SIZE 1000
#define MAX_WORD_SIZE 500
#define MAX_INDEX_SIZE 500
#define MAX_PAGENAME_SIZE 1050

FILE* utility_openFile(char *nameFile, char *action);

typedef struct inter {
    char** pages;
    int tam;
}Inter;


int main(int argc, char* argv[]){

    /*
    == Execução do programa ===

    ********Entrada********

    ./trab3 [nome_diretório]
    
    Onde o diretório deve conter:
        - index.txt
            Possui os nomes, um por linha, de todos as páginas/documentos a serem considerados.
        - stopwords.txt
            Possui todas as stop words, uma por linha.
        - graph.txt
            Possui a estrutura de links entre as páginas.
            Cada linha possui:
                - nome página de origem
                - número de links de saída dessa página
                - lista de páginas para qual ela aponta
        -pages
            Diretório que contém todos os arquivos de texto listados em index.txt
    
    Após iniciar, o programa deve ler uma sequencia de consultas, uma por linha, da entrada padrão.
    Cada consulta será uma lista de termos separados por caracteres de espaço.
    O programa deve continuar lendo consultas até que o caractere de fim de arquivo seja lido.

    ************************
    */

    if( argc < 2 ){
        perror("Uso: ./trab3 [diretório que contém os arquivos de entrada]\n");
        return -1;
    }

    char dir[MAX_DIRNAME_SIZE];
    char file_name[MAX_FILENAME_SIZE];
    char word[MAX_WORD_SIZE];
    char index[MAX_INDEX_SIZE];
    char page[MAX_PAGENAME_SIZE];

    /*================= LEITURA DAS STOP WORDS =================*/
    /* STATUS: OK */
    RBT_STRING* stopwords = RBT_STRING_init();

    strcpy(dir, argv[1]);
    sprintf(file_name, "%s/stopwords.txt", dir);

    // printf("%s\n\n", file_name);
     
    FILE* stopwords_file = utility_openFile(file_name, "r");
    
    while ( fscanf(stopwords_file,"%s\n", word) == 1 ) {
        // printf("%s\n", word);
        stopwords = RBT_STRING_insert(stopwords, word);
        // printf("Contains %s ? = %d\n", word, RBT_STRING_contains(stopwords, word));        
        // RBT_STRING_print(stopwords);
        // printf("\n\n");
    }

    // printf("\nContains %s ? = %d\n", "through", RBT_STRING_contains(stopwords, "through"));
    fclose(stopwords_file);

    // RBT_STRING_print(stopwords);
    // printf("%d\n", RBT_STRING_size(stopwords));

    /*=============== FIM LEITURA DAS STOP WORDS ===============*/


    /*================== LEITURA DAS PAGINAS ===================*/
    /* STATUS: OK */

    ST* st = ST_init();

    sprintf(file_name, "%s/index.txt", dir);
    FILE* index_file = utility_openFile(file_name, "r");
    // printf("%s\n", file_name);

    int pages_amount = 0;

    while ( fscanf(index_file,"%s\n", index) == 1 ) {
        pages_amount++;

        sprintf(page, "%s/pages/%s", dir, index);
        FILE* page_file = utility_openFile(page, "r");
        // printf("\n%s\n\n", page);
        
        while ( fscanf(page_file, "%s", word ) == 1 ){
            // printf("%s: %d\n", word, RBT_STRING_contains(stopwords, word));
            if( !RBT_STRING_contains(stopwords, word) ){
                ST_put(st, word, index);
                
                // ST_print(st);
                // printf("\nST_contains %s ? = %d\n\n", word, ST_contains(st, word));
            }
        }
        
        fclose(page_file);
    }
    
    fclose(index_file);
    /*================= FIM LEITURA DAS PAGINAS =================*/

    // ST_print(st);

    /*=================== ALGORITMO PAGE RANK ===================*/
    
    sprintf(file_name, "%s/graph.txt", dir);
    RBT_PAGE* pages = RBT_PAGE_init();
    pages = page_rank_algorithm(pages, file_name, pages_amount);

    // RBT_PAGE_print(pages);
    // printf("\nSIze: %d\n", RBT_PAGE_size(pages));

    // RBT_PAGE_traverse(pages, page_print);

    /*================= FIM ALGORITMO PAGE RANK =================*/


    /*=================== ALGORITMO DE BUSCA ====================*/

    /*  
        1.  Buscar primeiro termo da busca na ST
        2.  Essa busca vai retornar uma RBT_STRING que contem todas as paginas em que esse termo é encontrado
        3.  Criar um vetor de 'Page*' do tamanho da RBT_STRING retornada (RBT_STRING_size)
        4.  Agora, percorrer essa RBT_STRING usando a funcao RBT_STRING_traverse, que percorre a RBT_STRING em ordem crescente
        5.  Ao percorrer a RBT_STRING, pegar cada pagina, fazer sua busca na RBT_PAGE, e adicionar essa 'Page* no vetor criado acima
        6.  Fazer o mesmo para o segundo termo
        7.  Criar outro vetor auxiliar, com tamanho igual ao menor vetor dos criados acima, e fazer a interseção deles (Igual o Merge)
        8.  Buscar terceiro termo da busca (se houver) na ST
        9.  ...

        x.  Depois de ter o vetor com todas as paginas, fazer a ordenação do vetor usando qsort, por ordem decrescente de PageRank 
    */
    
    sprintf(file_name, "%s/searches.txt", dir);

    // printf("%s\n\n", file_name);
     
    FILE* searches_file = utility_openFile(file_name, "r");
    //===============================================================
    while(!feof(searches_file)) {
        fscanf(searches_file,"%[^\n]\n",dir);
        //printf("%s\n",dir);
        char * aux = strtok(dir," ");
        
        // RBT_STRING* rbt_s = ST_get(st, aux); //retorna a arvore que em cada nó contem a pagina que possui o nome thiago
        // char ** pag1 = calloc(RBT_STRING_size(rbt_s),sizeof(char *)); //paginas
        // RBT_STRING_traverse(rbt_s, pag1);



        Inter* inter = malloc(2*sizeof(Inter));
        //Inter inter[2];
        int qtd=0;
        while (aux){
            if(qtd==0) {
                RBT_STRING* rbt_s = ST_get(st, aux);
                inter[0].pages = calloc(RBT_STRING_size(rbt_s),sizeof(char *));
                RBT_STRING_traverse(rbt_s, inter[0].pages);
                inter[0].tam=RBT_STRING_size(rbt_s);
                qtd++; 
            } else {
                RBT_STRING* rbt_s = ST_get(st, aux);
                inter[1].pages = calloc(RBT_STRING_size(rbt_s),sizeof(char *));
                RBT_STRING_traverse(rbt_s, inter[1].pages);
                inter[1].tam=RBT_STRING_size(rbt_s);

                Inter auxiliar;
                auxiliar.tam=0;

                if (inter[0].tam>=inter[1].tam) {
                    auxiliar.pages=calloc(inter[1].tam,sizeof(char *));
                    auxiliar.tam=inter[1].tam;
                } else {
                    auxiliar.pages=calloc(inter[0].tam,sizeof(char *));
                    auxiliar.tam=inter[0].tam;
                }

                int i=0, j=0, count=0;
                while(i<inter[0].tam && j<inter[1].tam) {
                    int cmp = strcmp(inter[0].pages[i], inter[1].pages[j]);

                    if(cmp == 0) {
                        auxiliar.pages[count++]=strdup(inter[0].pages[i]);
                        i++; j++;
                    } else if(cmp<0) {
                        i++;
                    } else {
                        j++;
                    }
                    
                }
                
                for(int x=0;x<inter[0].tam;x++) {
                    free(inter[0].pages[x]);
                }

                inter[0].tam=count;

                for(int x=0;x<inter[0].tam;x++) {
                    inter[0].pages[x]=strdup(auxiliar.pages[x]);
                }
            }
            aux = strtok(NULL," ");
        }

        for(int x=0;x<inter[0].tam;x++) {
            printf("%s\n", inter[0].pages[x]);
        }
        printf("--------------------\n");
    }
    //===============================================================

    // RBT_STRING* rbt_s = ST_get(st, "gatti");
    // Page** v_page2[RBT_STRING_size(rbt_s)];
    // RBT_STRING_traverse(rbt_s, );
    // Page* pg = RBT_PAGE_get(pages, nome_pagina);

    fclose(searches_file);


    /*================= FIM ALGORITMO DE BUSCA ==================*/


    RBT_PAGE_finish(pages);
    RBT_STRING_finish(stopwords);
    ST_finish(st);

    return 0;
}


FILE* utility_openFile(char *nameFile, char *action){
    //Abrir o arquivo
    FILE *file = fopen(nameFile, action);

    //Testar o arquivo
    if(file == NULL){
        printf("\n Erro 001: Função Open_File: Erro Ao abrir arquivo\n");
        exit(0);
    }

    return file; 
}

void intersecao() {

}