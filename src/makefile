CC=clang
TARGET=spaceinvader
CFLAGS=-g -W -Wall -Wextra
LDFLAGS=-l graph -L Graphique -l SDL -l SDL_ttf 

default: $(TARGET)

	
main.o : main.c  ../Listechainee/Listechainee.h
	clang $(CFLAGS) -c main.c

Listechainee.o : ../Listechainee/Listechainee.c ../Listechainee/Listechainee.h
	clang $(CFLAGS) -c ../Listechainee/Listechainee.c
	
$(TARGET) :  main.o Listechainee.o
	clang main.o  Listechainee.o -o $(TARGET) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *.o
	rm -f $(TARGET)
