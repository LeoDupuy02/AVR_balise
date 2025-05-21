CC = gcc
CFLAGS = -Wall -Wextra -pedantic -std=c99 -g

SRC = test.c AVR.c
OBJ = $(SRC:.c=.o)
DEPS = AVR.h

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
