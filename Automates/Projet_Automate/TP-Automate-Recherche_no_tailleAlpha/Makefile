CC=gcc
FLAG=-Wall -g 


main : main.o automates_D.o 
	${CC} main.o automates_D.o  -o main

main.o : main.c
	${CC} -c main.c ${FLAG}


automates_D.o : automates_D.c
	${CC} -c automates_D.c ${FLAG}

