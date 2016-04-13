# Rafael Hengen Ribeiro, Ricardo Parizotto
# Makefile para o jogo de trilha
FLAGS=-fpermissive -O2
DEBUG=-Wall -pedantic -g
CPP=g++
BIN_DIR=bin/
LIBS_DIR=obj/
NAME=trilha
SOURCE_DIR=src/
all:
	$(CPP) $(SOURCE_DIR)utils.cpp $(SOURCE_DIR)jogo.cpp $(SOURCE_DIR)main.cpp -o $(BIN_DIR)$(NAME) $(FLAGS)

debug:
	$(CPP) $(SOURCE_DIR)utils.cpp $(SOURCE_DIR)jogo.cpp $(SOURCE_DIR)main.cpp -o $(BIN_DIR)$(NAME)_debug $(DEBUG)
	
obj:
	$(CPP) -c $(SOURCE_DIR)jogo.cpp -o $(LIBS_DIR)jogo.o

clean:
	rm $(BIN_DIR)*
	rm $(LIBS_DIR)*
	
