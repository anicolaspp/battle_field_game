CC=cc
CFLAGS=-Wall

SRC  =  FileReader.c main.c Parser.c RandomMoveStrategy.c SingleMoveStrategy.c Table.c Vector.c WinnerMoveStrategy.c
HDR  =	FileReader.h Parser.h RandomMoveStrategy.h SingleMoveStrategy.h Table.h Vector.h WinnerMoveStrategy.h
OBJ  =  $(SRC:.c=.o)

all:	Main

Main:	$(OBJ)
	@echo LINK $(OBJ) into $@
	$(CC) $(CFLAGS) $(OBJ) -o $@



clean:
	rm -f *.o Main

