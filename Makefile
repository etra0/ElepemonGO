SRC = inih/ini.c
OBJ = $(SRC:.c=.o)
OUT = libinih.a
INCLUDES = -I..
CCFLAGS =-Wall -g -O2
EXEC=tarea1
CC=gcc
SRC=src

default: $(OUT)

compile: elepemon.o stack.o attacks.o $(SRC)/main.c
	$(CC) $(CFLAGS) -L./ $(SRC)/main.c objects/*.o -linih -ldl -o bin/$(EXEC)

elepemon.o: $(SRC)/elepemon.c
	$(CC) $(CFLAGS) $< -c -o objects/$@

stack.o: $(SRC)/elepemon_stack.c
	$(CC) $(CFLAGS) $< -c -o objects/$@

attacks.o: objects/handler_stack.o $(SRC)/attacks.c
	$(CC) $(CFLAGS) $(SRC)/attacks.c -c -o objects/$@

handler_stack.o: $(SRC)/handler_stack.c
	$(CC) $(CFLAGS) $< -c -o objects/$@

run:
	bin/$(EXEC)

.c.o:
	$(CC) $(INCLUDES) $(CCFLAGS) $(EXTRACCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ) $(EXTRAARFLAGS)
	mkdir objects
	mkdir bin

clean:
	rm -f $(OBJ) $(OUT)
