CC=clang
TARGET=spaceinvader
CFLAGS=-g -W -Wall -Wextra
LDFLAGS=-l graph -L Graphique -l SDL -l SDL_ttf 

default: $(TARGET)

	
main.o : main.c  ../Listechainee/Listechainee.h
	$(CC) $(CFLAGS) -c main.c

Listechainee.o : ../Listechainee/Listechainee.c ../Listechainee/Listechainee.h
	$(CC) $(CFLAGS) -c ../Listechainee/Listechainee.c
	
$(TARGET) :  main.o Listechainee.o
	$(CC) main.o  Listechainee.o -o $(TARGET) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *.o
	rm -f $(TARGET)
