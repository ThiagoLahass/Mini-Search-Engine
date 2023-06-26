PROJ_NAME = trab3
CC_FLAGS=-c -w -Wall -g -lm

# all: clean compile runAll diffAll # valAll

compile: RBT ST
	@ gcc -o $(PROJ_NAME) *.o main.c -lm 
# -lm é usado para linkar a biblioteca math.h

RBT:
	@ gcc -c RBT.c
	
ST: RBT
	@ gcc -c ST.c

run: clean compile
	@ ./$(PROJ_NAME)

clean:
	@ rm -f *.o $(PROJ_NAME)

val: clean compile
	@ valgrind --leak-check=full ./$(PROJ_NAME)

# run1pdf: clean compile
# 	@ ./$(PROJ_NAME) ${DIR_ENTRADA_1_PDF} ${DIR_SAIDA_1_PDF}

# run1: clean compile
# 	@ ./trab1 ${DIR_ENTRADA_1} ${DIR_SAIDA_1}

# run2: clean compile
# 	@ ./trab1 ${DIR_ENTRADA_2} ${DIR_SAIDA_2}

# run3: clean compile
# 	@ ./trab1 ${DIR_ENTRADA_3} ${DIR_SAIDA_3}

# runAll: run1 run2 run3

# val1pdf: clean compile
# 	@ valgrind --leak-check=full ./trab1 ${DIR_ENTRADA_1_PDF} ${QTD_GRUPOS} ${DIR_SAIDA_1_PDF}

# val1: clean compile
# 	@ valgrind --leak-check=full ./trab1 ${DIR_ENTRADA_1} ${DIR_SAIDA_1}

# val2: clean compile
# 	@ valgrind --leak-check=full ./trab1 ${DIR_ENTRADA_2} ${DIR_SAIDA_2}

# val3: clean compile
# 	@ valgrind --leak-check=full ./trab1 ${DIR_ENTRADA_3} ${DIR_SAIDA_3}

# valAll: val1 val2 val3

# diff1: clean compile
# 	@ ./trab1 ${DIR_ENTRADA_1} 2 ${DIR_SAIDA_1}
# 	@ diff ${DIR_SAIDA_1} ${DIR_RESP_1}

# diff2: clean compile
# 	@ ./trab1 ${DIR_ENTRADA_2} 4 ${DIR_SAIDA_2}
# 	diff ${DIR_SAIDA_2} ${DIR_RESP_2}

# diff3: clean compile
# 	@ ./trab1 ${DIR_ENTRADA_3} 5 ${DIR_SAIDA_3}
# 	diff ${DIR_SAIDA_3} ${DIR_RESP_3}

# diffAll: diff1 diff2 diff3
	