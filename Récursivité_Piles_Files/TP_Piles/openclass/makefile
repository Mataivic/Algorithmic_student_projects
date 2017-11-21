CC=gcc
OPT=-Wall -Werror -Wconversion -Wextra -pedantic -std=c99
SRC=main_pile
FCT=fct_pile

all: $(FCT)
	$(CC) $(OPT) $(FCT).o $(SRC).c

fct_pile:
	$(CC) $(OPT) -c $(FCT).c
