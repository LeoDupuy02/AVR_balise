CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g

SRC = pile.c AVR.c graphviz_handler.c AVR_Balise.c application.c test.c
OBJ = $(SRC:.c=.o)
DEPS = pile.h AVR.h AVR_Balise.h graphviz_handler.h application.h

EXEC = main

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o $(EXEC)

dotclean:
	rm -f *.dot

.PHONY: all clean dotclean
