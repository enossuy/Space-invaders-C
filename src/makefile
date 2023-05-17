CC=clang
TARGET=spaceinvader
CFLAGS=-g -W -Wall -Wextra
LDFLAGS=-l graph -L Graphique -l SDL -l SDL_ttf 
OBJECTS= main.o Listechainee.o Graphique/libgraph.a
default: $(TARGET)

	
main.o : main.c  Listechainee/Listechainee.h Graphique/libgraph.a
	$(CC) $(CFLAGS) -c main.c

Listechainee.o : Listechainee/Listechainee.c Listechainee/Listechainee.h
	$(CC) $(CFLAGS) -c Listechainee/Listechainee.c
	
Graphique/libgraph.a:
	cd Graphique/ && $(MAKE)
	cd ..
	
$(TARGET) :  $(OBJECTS)
	$(CC) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

.PHONY: clean
clean:
	rm -f *.o
	rm -f $(TARGET)	

tidy:
	$(CC)-tidy -checks="*" main.c--
	$(CC)-tidy -checks="*" Listechainee.c--

format:
	$(CC)-format -i main.c--
	$(CC)-format -i Listechainee.c--
