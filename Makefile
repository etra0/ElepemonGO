SRC = inih/ini.c
OBJ = $(SRC:.c=.o)
OUT = libinih.a
INCLUDES = -I..
CCFLAGS =-Wall -g -O2
EXEC=tarea1
CC=gcc

default: $(OUT)

compile: elepemon.o stack.o attacks.o main.c
	$(CC) $(CFLAGS) -L./ main.c *.o -linih -o bin/$(EXEC)

elepemon.o: elepemon.c
	$(CC) $(CFLAGS) $< -c

stack.o: stack.c
	$(CC) $(CFLAGS) $< -c

attacks.o: attacks.c
	$(CC) $(CFLAGS) $< -c

run:
	bin/$(EXEC)

.c.o:
	$(CC) $(INCLUDES) $(CCFLAGS) $(EXTRACCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ) $(EXTRAARFLAGS)

clean:
	rm -f $(OBJ) $(OUT)
