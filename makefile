SRCS = main.cpp game.hpp constants.hpp draw.hpp
EXE = game

BIN = bin

CC = g++
CFLAGS = -g -lsfml-graphics -lsfml-window -lsfml-system

all:
	test -d $(BIN) || mkdir $(BIN)
	$(CC) $(SRCS) -o $(BIN)/$(EXE) $(CFLAGS)

clean:
	rm $(BIN)/*
