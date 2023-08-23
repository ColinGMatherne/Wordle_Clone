OBJS	= client.o server.o
OUT	= ../bin/client,../bin/server

OBJS0	= client.o
SOURCE0	= client.c
HEADER0	= client.h
OUT0	= ../bin/client

OBJS1	= server.o
SOURCE1	= server.c
HEADER1	= server.h
OUT1	= ../bin/server

CC	 = gcc
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: ../bin/client ../bin/server

../bin/client: $(OBJS0) $(LFLAGS)
	$(CC) -g $(OBJS0) -o $(OUT0)

../bin/server: $(OBJS1) $(LFLAGS)
	$(CC) -g $(OBJS1) -o $(OUT1)

client.o: client.c
	$(CC) $(FLAGS) client.c 

server.o: server.c
	$(CC) $(FLAGS) server.c 


clean:
	rm -f $(OBJS) $(OUT)

