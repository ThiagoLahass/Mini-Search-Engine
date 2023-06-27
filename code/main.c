#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ST.h"

#define MAX_DIRNAME_SIZE 500
#define MAX_FILENAME_SIZE 500
#define MAX_WORD_SIZE 500
#define MAX_INDEX_SIZE 500
#define MAX_PAGENAME_SIZE 500

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

    strcpy(dir, argv[1]);
    sprintf(file_name, "%s/stopwords.txt", dir);

    printf("%s\n", file_name);

    FILE* stopwords_file = utility_openFile(file_name, "r");

    while ( fscanf(stopwords_file,"%s\n", word) == 1 ) {
        printf("%s\n", word);
    }
    
    fclose(stopwords_file);

    /*=============== FIM LEITURA DAS STOP WORDS ===============*/


    /*================== LEITURA DAS PAGINAS ===================*/
    
    sprintf(file_name, "%s/index.txt", dir);

    printf("%s\n", file_name);

    FILE* index_file = utility_openFile(file_name, "r");

    while ( fscanf(index_file,"%s\n", index) == 1 ) {
        sprintf(page, "%s/pages/%s", dir, index);

        printf("\n%s\n\n", page);

        FILE* page_file = utility_openFile(page, "r");
        
        while ( fscanf(page_file, "%s", word ) == 1 ){
            printf("%s ", word);
        }

        printf("\n\n");
        
        fclose(page_file);
    }
    
    fclose(index_file);

    /*================= FIM LEITURA DAS PAGINAS =================*/

    
    
    
    // char str1[] = "Hello";
    // char str2[] = "hello";

    // int result = strcasecmp(str1, str2);

    // if (result == 0) {
    //     printf("As strings são iguais.\n");
    // } else if (result < 0) {
    //     printf("str1 é menor que str2.\n");
    // } else {
    //     printf("str1 é maior que str2.\n");
    // }




    // int num = 1000;

    // printf("Inicializando...\n");
    // ST* st = ST_init();
    // ST_print(st);

    // printf("Preenchendo com alguns valores...\n");
    // for(int i = 0; i < num; i++){
    //     ST_put(st, 2*i, i+100);
    // }

    // printf("Percorrendo e imprimindo...\n");
    // // ST_print(st);

    // printf("Testando funções ST...\n\n");

    // printf("Get ST...\n");
    // printf("ST_get(st, 2) = %d\n", ST_get(st, 2));
    // printf("ST_get(st, 7) = %d\n", ST_get(st, 7));
    // printf("ST_get(st, 100) = %d\n\n", ST_get(st, 100));

    // printf("Contains ST...\n");
    // printf("ST_contains(st, 2) = %d\n", ST_contains(st, 2));
    // printf("ST_contains(st, 7) = %d\n", ST_contains(st, 7));
    // printf("ST_contains(st, 100) = %d\n\n", ST_contains(st, 100));

    // // printf("Delete ST...\n");
    // // printf("Antes...\n");
    // // ST_print(st);
    // // printf("ST_contains(st, 2) = %d\n", ST_contains(st, 2));
    // // printf("ST_delete(st,2)\n");
    // // ST_delete(st, 2);
    // // printf("ST_contains(st, 2) = %d\n", ST_contains(st, 2));
    // // printf("Depois...\n");
    // // ST_print(st);

    // printf("Empty ST...\n");
    // printf("ST_empty(st) = %d\n\n", ST_empty(st));

    // printf("Min ST...\n");
    // printf("ST_min(st) = %d\n\n", ST_min(st));

    // printf("Max ST...\n");
    // printf("ST_max(st) = %d\n\n", ST_max(st));

    // printf("Floor ST...\n");
    // printf("ST_floor(st,3) = %d\n\n", ST_floor(st, 3));

    // printf("Ceiling ST...\n");
    // printf("ST_ceiling(st,3) = %d\n\n", ST_ceiling(st, 3));

    // printf("Rank ST...\n");
    // printf("ST_rank(st,5) = %d\n\n", ST_rank(st, 5));

    // printf("Liberando ST...\n");
    // ST_finish(st);

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