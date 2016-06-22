all : hcc

DIR_SRC = ./src
DIR_LEX = ./lex
DIR_OBJ = ./obj
DIR_TEST = ./test
DIR_OUT = ./bin
DIR_H = ./include

FLEX_INCLUDE = "C:\GnuWin32\include"

CC = g++
CPPFLAGS = -Wall -std=gnu++0x -I$(DIR_H) -I$(FLEX_INCLUDE) -g
LDFLAGS = -lpthread -static 

SRC = $(wildcard ${DIR_SRC}/*.c)  
OBJS = $(DIR_OBJ)/parser.o $(DIR_OBJ)/hc.o

$(DIR_SRC)/hc.cpp : $(DIR_LEX)/hc.flex $(DIR_H)/parser.hpp
	flex -o$@ $<

$(DIR_H)/parser.hpp : $(DIR_SRC)/parser.cpp

$(DIR_SRC)/parser.cpp : $(DIR_LEX)/parser.y
	bison --defines=$(DIR_H)/parser.hpp -o $@ $^

$(DIR_OBJ)/%.o : $(DIR_SRC)/%.cpp
	$(CC) -c $(CPPFLAGS) -o $@ $<

hcc : $(OBJS) 
	$(CC) -o $(DIR_OUT)/$@ $(OBJS) $(LDFLAGS)

lextest : $(OBJS) $(DIR_TEST)/lex_test.cpp
	$(CC) -o $(DIR_OUT)/$@ $^ $(LDFLAGS) $(CPPFLAGS)

cleanauto:
	$(RM) $(DIR_SRC)/lex.cpp $(DIR_SRC)/parser.cpp

.PHONY : all clean cleanauto