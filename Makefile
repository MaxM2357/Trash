SRCS = main.c list.c
OBJS = $(SRCS:%.c=%.o)
CC = gcc
PROG = ex7


CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99
LDFLAGS = -lm

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.PHONY: clean run

clean:
	$(RM) $(OBJS) $(PROG)

run: $(PROG)
	./$(PROG)

runwin: $(PROG)
	$(PROG).exe
