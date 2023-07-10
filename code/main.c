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
#define MAX_SEARCH_SIZE 1000

FILE* utility_openFile(char *nameFile, char *action);
int intersection_of_Pages(char **vetor1, int tam1, char **vetor2, int tam2);

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
    
    char search[MAX_SEARCH_SIZE];
    char search_aux[MAX_SEARCH_SIZE];

    while(fgets(search, MAX_SEARCH_SIZE, stdin) != NULL) {
        // Removendo o caractere nova linha ('\n') do final do comando e substitui por \0
        search[strcspn(search, "\n")] = '\0';
        // Salvar vetor original do search para imprimir posteriormente
        strcpy(search_aux, search);
        
        char str[MAX_WORD_SIZE];
        char * aux;
        int tam_vetor_intersecao = 0;
        char** v_intersecao_pages;
        
        if( (aux = strtok(search," ")) != NULL ){                               // Pega primeiro termo da pesquisa
            
            // Se o termo buscado for uma stopword, devemos ignora-la
            while ( RBT_STRING_contains(stopwords, aux) ){
                if( (aux = strtok(NULL," ")) == NULL) break;
            }

            RBT_STRING* rbt_s = ST_get(st, aux);                                // Busca a RBT de paginas que contem aquele termo  
            tam_vetor_intersecao = RBT_STRING_size(rbt_s);                      // Pega a quantidade de paginas para criar um vetor desse tamanho
            v_intersecao_pages = calloc(tam_vetor_intersecao, sizeof(char*));   // Cria um vetor para podermos salvar os NOMES das paginas
            RBT_STRING_traverse(rbt_s, v_intersecao_pages);                     // Percorre a RBT e salva os nomes das paginas no vetor acima
        
            while ( (aux = strtok(NULL," ")) != NULL ){                         // Enquanto houverem termos na linha
                if( RBT_STRING_contains(stopwords, aux) ){                      // Se for uma stopword, ignorar
                    continue;
                }
                RBT_STRING* rbt_s2 = ST_get(st, aux);                           // Mesmo procedimento visto acima
                int tam_vetor_2 = RBT_STRING_size(rbt_s2);
                char* v_pages_2[tam_vetor_2];
                RBT_STRING_traverse(rbt_s2, v_pages_2);

                // Calculamos a interseção entre os dois vetores
                // Atualizamos a quantidade de paginas na interseção
                tam_vetor_intersecao = intersection_of_Pages(v_intersecao_pages, tam_vetor_intersecao, v_pages_2, tam_vetor_2);
            }

        }

        // Vetor em que sera salvo as pages das intersecoes
        Page* v_pages[tam_vetor_intersecao];

        for(int i = 0; i < tam_vetor_intersecao; i++){
            v_pages[i] = RBT_PAGE_get(pages, v_intersecao_pages[i]);
        }
        free(v_intersecao_pages);
        
        // Ordenar Pages por page rank
        sort_pages_by_page_rank(v_pages, tam_vetor_intersecao);

        printf("search:%s\n",search_aux);

        printf("pages:");
        for(int i = 0; i < tam_vetor_intersecao; i++){
            printf("%s", get_page_name(v_pages[i]));
            if(i < tam_vetor_intersecao-1)
                printf(" ");
        }

        printf("\npr:");
        for(int i = 0; i < tam_vetor_intersecao; i++){
            printf("%f", get_page_rank(v_pages[i]));
            if(i < tam_vetor_intersecao-1)
                printf(" ");
        }
        printf("\n");
    }
    /*================= FIM ALGORITMO DE BUSCA ==================*/

    RBT_PAGE_finish(pages);
    RBT_STRING_finish(stopwords);
    ST_finish(st);

    return 0;
}


int intersection_of_Pages(char **vetor1, int tam1, char **vetor2, int tam2) {
    int index1 = 0; // Índice para percorrer o vetor1
    int index2 = 0; // Índice para percorrer o vetor2
    int intersectionIndex = 0; // Índice para preencher o vetor1 com a interseção
    int intersectionCounter = 0; // Contador para armazenar a quantidade de elementos na interseção
    
    // Percorre os vetores enquanto houver elementos em ambos
    while (index1 < tam1 && index2 < tam2) {
        int com = strcmp(vetor1[index1], vetor2[index2]);
        
        if (com < 0) {
            index1++; // O elemento em vetor1 é menor, avança o índice em vetor1
        } else if (com > 0) {
            index2++; // O elemento em vetor2 é menor, avança o índice em vetor2
        } else {
            // Encontrou um elemento em comum (interseção)
            vetor1[intersectionIndex++] = vetor1[index1]; // Adiciona no vetor1 (sobrescrevendo)
            index1++; // Avança o índice em ambos os vetores
            index2++;
            intersectionCounter++; // Incrementa o contador de interseção
        }
    }
    return intersectionCounter;
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

