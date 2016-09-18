SRC = inih/ini.c
OBJ = $(SRC:.c=.o)
OUT = libinih.a
INCLUDES = -I..
CCFLAGS =-Wall -g -O2
EXEC=tarea1
CC=gcc
SRCCODE=src

default: $(OUT)

compile: elepemon_stack.o elepemon.o handler_stack.o attacks.o $(SRCCODE)/main.c
	$(CC) $(CFLAGS) -L./ $(SRCCODE)/main.c objects/*.o -linih -ldl -o bin/$(EXEC)

elepemon.o: $(SRCCODE)/elepemon.c
	$(CC) $(CFLAGS) $< -c -o objects/$@

elepemon_stack.o: $(SRCCODE)/elepemon_stack.c
	$(CC) $(CFLAGS) $< -c -o objects/$@

attacks.o: objects/handler_stack.o $(SRCCODE)/attacks.c
	$(CC) $(CFLAGS) $(SRCCODE)/attacks.c -c -o objects/$@

handler_stack.o: $(SRCCODE)/handler_stack.c
	$(CC) $(CFLAGS) $< -c -o objects/$@

run:
	bin/$(EXEC) attacks ELEPEMONES

.c.o:
	$(CC) $(INCLUDES) $(CCFLAGS) $(EXTRACCFLAGS) -c $< -o $@

$(OUT): $(OBJ)
	ar rcs $(OUT) $(OBJ) $(EXTRAARFLAGS)
	mkdir objects
	mkdir bin

clean:
	rm -f $(OBJ) $(OUT)
