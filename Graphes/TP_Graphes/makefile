CC=gcc
OPT=-Wall -Werror -Wconversion -Wextra -pedantic -std=c99
SRC=main
FCT=listes
FCT2=graphe
FCT3=files

all: $(FCT) $(FCT2) $(FCT3)
	$(CC) $(OPT) $(FCT).o $(FCT2).o $(FCT3).o $(SRC).c

listes:
	$(CC) $(OPT) -c $(FCT).c

graphe:
	$(CC) $(OPT) -c $(FCT2).c

files:
	$(CC) $(OPT) -c $(FCT3).c