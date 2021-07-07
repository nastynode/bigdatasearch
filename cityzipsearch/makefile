CC = gcc
#CFLAGS = -ggdb -Wall -pedantic
CFLAGS = -O -Wall -pedantic


all: createfile searchfiles

run:
	make clean
	make all
	./createfile input/cz1.txt new
	./createfile input/cz2.txt append
	./searchfiles

runnew:
	make all
	./createfile input/cz1.txt new
	./searchfiles

runappend:
	make all
	./createfile input/cz2.txt append
	./searchfiles

search:
	./searchfiles

clean:
	rm -f *.o core createfile searchfiles all
