CC=gcc
FLAG=-Wall -g -std=c99


main : main.o graphes-chevauchement.o
	${CC} main.o graphes-chevauchement.o -o main

main.o : main.c
	${CC} -c main.c ${FLAG}


graphes-chevauchement.o : graphes-chevauchement.c
	${CC} -c graphes-chevauchement.c ${FLAG}

