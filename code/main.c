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

    // printf("%s\n", file_name);

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

    /*================= FIM ALGORITMO PAGE RANK =================*/

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