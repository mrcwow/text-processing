all: main.o treatment.o getputtext.o 
	gcc main.o getputtext.o treatment.o -o cw
main.o: main.c getputtext.h treatment.h main.h
	gcc -c main.c
treatment.o: treatment.c treatment.h main.h
	gcc -c treatment.c
getputtext.o: getputtext.c getputtext.h main.h
	gcc -c getputtext.c
clean:
	rm -f *.o