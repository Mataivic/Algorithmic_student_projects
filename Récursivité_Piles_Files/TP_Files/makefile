CC=gcc
OPT=-Wall -Werror -Wconversion -Wextra -pedantic -std=c99
SRC=file_main
FCT=files_fct

all: $(FCT)
	$(CC) $(OPT) $(FCT).o $(SRC).c

files_fct:
	$(CC) $(OPT) -c $(FCT).c