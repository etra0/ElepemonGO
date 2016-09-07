SRC = inih/ini.c
OBJ = $(SRC:.c=.o)
OUT = libinih.a
INCLUDES = -I..
CCFLAGS =-Wall -g -O2
EXEC=tarea1
CC=gcc

default: $(OUT)

compile: main.c elepemon.o
	$(CC) $(CFLAGS) -L./ main.c elepemon.o -linih -o bin/$(EXEC)

elepemon.o: elepemon.c
	$(CC) $(CFLAGS) elepemon.c -c

run:
	bin/$(EXEC)

.c.o:
	$(CC) $(INCLUDES) $(CCFLAGS) $(EXTRACCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ) $(EXTRAARFLAGS)

clean:
	rm -f $(OBJ) $(OUT)
