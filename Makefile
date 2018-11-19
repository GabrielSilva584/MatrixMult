CC = g++
CFLAGS = -g -Wall
SRCS = main.cpp
PROG = MultMatrix

LIBS = -pthread

$(PROG):$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm $(PROG)
