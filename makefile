OBJ = main.o graphics.o add.o display.o handler.o init.o
EXEC: main graphics add display handler init
	gcc -o EXEC $(OBJ) -lpthread -lncurses
main: main.c defs.h
	gcc -c main.c
graphics: graphics.c defs.h
	gcc -c graphics.c
add: add.c defs.h
	gcc -c add.c
display: display.c defs.h
	gcc -c display.c
handler: handler.c defs.h
	gcc -c handler.c
init: init.c defs.h
	gcc -c init.c
clean: 
	rm -f $(OBJ)
