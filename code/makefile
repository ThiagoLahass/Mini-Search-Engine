PROJ_NAME = trab3
CC_FLAGS=-c -w -Wall -g -lm

compile: PAGE PAGE_RANK RBT_PAGE RBT_STRING RBT ST
	@ gcc -o $(PROJ_NAME) *.o main.c -lm 
# -lm é usado para linkar a biblioteca math.h

PAGE:
	@ gcc -c page.c

PAGE_RANK:
	@ gcc -c PageRank.c

RBT_PAGE:
	@ gcc -c RBT_PAGE.c

RBT_STRING:
	@ gcc -c RBT_STRING.c

RBT:
	@ gcc -c RBT.c
	
ST: RBT
	@ gcc -c ST.c

run1: clean compile
	@ ./$(PROJ_NAME) ../Exemplo_mini < ../Exemplo_mini/searches.txt > ../saidas/saida_mini.txt

run2: clean compile
	@ ./$(PROJ_NAME) ../Exemplo_pequeno_e_simples < ../Exemplo_pequeno_e_simples/searches.txt > ../saidas/saida_pequeno.txt

run3: clean compile
	@ ./$(PROJ_NAME) ../Exemplo_medio_grande < ../Exemplo_medio_grande/searches.txt > ../saidas/saida_medio.txt

val1: clean compile
	@ valgrind --leak-check=full ./$(PROJ_NAME) ../Exemplo_mini < ../Exemplo_mini/searches.txt

val2: clean compile
	@ valgrind --leak-check=full ./$(PROJ_NAME) ../Exemplo_pequeno_e_simples < ../Exemplo_pequeno_e_simples/searches.txt

val3: clean compile
	@ valgrind --leak-check=full ./$(PROJ_NAME) ../Exemplo_medio_grande < ../Exemplo_medio_grande/searches.txt

runAll: run1 run2 run3

valAll: val1 val2 val3

clean:
	@ rm -f *.o $(PROJ_NAME) ../saidas/*