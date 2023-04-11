CC=clang
TARGET=spaceinvader
CFLAGS=-g -W -Wall -Wextra
LDFLAGS=-l graph -L Graphique -l SDL -l SDL_ttf 

default: $(TARGET)

main.o : main.c
	clang $(CFLAGS) -c main.c

$(TARGET) : main.o
	clang main.o -o $(TARGET) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *.o
	rm -f $(TARGET)
