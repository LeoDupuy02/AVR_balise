CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g

SRC = main.c pile.c AVR.c AVR_balise.c
OBJ = $(SRC:.c=.o)
DEPS = AVR.h AVR_balise.h

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
