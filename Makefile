lex.cpp :
	flex++ -osrc/lex.cpp lex/hc.flex

lex : lex.cpp
	g++ -g -Wall -lfl -o lex src/lex.cpp