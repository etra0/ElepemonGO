SRC = inih/ini.c
OBJ = $(SRC:.c=.o)
OUT = libinih.a
INCLUDES = -I..
CCFLAGS =-Wall -g -O2
EXEC=tarea1
CC=gcc

default: $(OUT)

compile: elepemon.o main.c
	$(CC) $(CFLAGS) -L./ main.c $< -linih -o bin/$(EXEC)

elepemon.o: elepemon.c
	$(CC) $(CFLAGS) $< -c

run:
	bin/$(EXEC)

.c.o:
	$(CC) $(INCLUDES) $(CCFLAGS) $(EXTRACCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ) $(EXTRAARFLAGS)

clean:
	rm -f $(OBJ) $(OUT)
