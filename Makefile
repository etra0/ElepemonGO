SRC = inih/ini.c
OBJ = $(SRC:.c=.o)
OUT = libinih.a
INCLUDES = -I..
CCFLAGS =-Wall -g -O2
EXEC=tarea1
CC=gcc

default: $(OUT)

compile: elepemon.o stack.o attacks.o main.c
	$(CC) $(CFLAGS) -L./ main.c objects/*.o -linih -ldl -o bin/$(EXEC)

elepemon.o: elepemon.c
	$(CC) $(CFLAGS) $< -c -o objects/$@

stack.o: stack.c
	$(CC) $(CFLAGS) $< -c -o objects/$@

attacks.o: handler_stack.o attacks.c
	$(CC) $(CFLAGS) attacks.c -c -o objects/$@

handler_stack.o: handler_stack.c
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
