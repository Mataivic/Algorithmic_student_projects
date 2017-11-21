CC=gcc
OPT=-Wall -Werror -Wconversion -Wextra -pedantic -std=c99
SRC=main
FCT=mots

all: $(FCT)
	$(CC) $(OPT) $(FCT).o $(SRC).c

mots:
	$(CC) $(OPT) -c $(FCT).c