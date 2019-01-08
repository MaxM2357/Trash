SRCS = msg-counter.c set-hash.c
OBJS = $(SRCS:%.c=%.o)
CC = gcc
PROG = msg-counter
FILE = test3.txt

CFLAGS = -Wall -Wextra -Wmissing-prototypes --pedantic -std=c99
LDFLAGS = -lm

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) -o $@ $(OBJS) $(LDFLAGS)

.PHONY: clean run

clean:
	$(RM) $(OBJS) $(PROG)

run: $(PROG)
	./$(PROG) $(FILE)

runwin: $(PROG)
	$(PROG).exe
