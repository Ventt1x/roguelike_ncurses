CC = gcc
CFLAGS = -Wall -Iinclude
LIBS = -lncurses
SRC = $(wildcard src/*.c)

roguelike: $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o roguelike $(LIBS)

clean:
	rm -f 
#made by claude