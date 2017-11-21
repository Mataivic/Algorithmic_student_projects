CC=gcc
OPT=-Wall -Werror -Wconversion -Wextra -pedantic -std=c99
SRC=arbrebin_main
FCT=arbrebin
FCT2=files_fct

all: $(FCT)
	$(CC) $(OPT) $(FCT).o $(SRC).c

arbrebin:
	$(CC) $(OPT) -c $(FCT).c

files_fct:
	$(CC) $(OPT) -c $(FCT2).c
