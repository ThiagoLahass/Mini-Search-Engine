# Mini-Search-Engine

## Objetivo
  O objetivo é aplicar o conceito de Tabela de Símbolos para o desenvolvimento de uma mini máquina de busca.

## A anatomia de uma maquina de busca
  Não vai parecer novidade para nenhum de vocês que desenvolver uma máquina de busca para a Web é uma tarefa complexa.
E não apenas é uma tarefa complexa hoje, como também era quando as primeiras máquinas de busca surgiram.

Minimamente, uma maquina de busca deve ter os seguintes componentes:
1. Web Crawler: responsável por, constantemente, explorar a Web e obter o conteúdo das páginas;
2. Indexador: responsável por mapear os termos (ou combinações de termos) para as páginas que os contém;
3. Ordenador de páginas: responsável por ordenar as páginas/documentos de acordo com usas respectivas
importâncias. Esse componente é essencial para definir a ordem de apresentação das páginas que contém
um certo termo buscado.
4. Processador de consultas: dada uma consulta realizada por um usuário, este componente é responsável por
identificar os documentos relacionados ao termo (de acordo com o indexador) e apresenta-los em ordem
decrescente de importância (de acordo com o ordenador).
