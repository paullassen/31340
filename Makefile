CC = gcc -pthread 
CFLAGS = -Wall -O1    -I /usr/realtime/include -I /usr/local/include/sdlio 
LDFLAGS = -L /usr/realtime/lib -L /usr/local/include/sdlio -lcomedi -lm 
LDFLAGS1 = -L /usr/realtime/lib -L /usr/local/include/sdlio  -lm 
LIBS =  -lreadline -ltermcap -lcomedi

PROGS = 

all:	$(PROGS)

canonical:	canonical.o
	$(CC) $(LDFLAGS1) -o $@ $^ -lm


welcome:	welcome.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

ioexample:	ioexample.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

reaction_test:	reaction_test.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

scheduler:	scheduler.o
	$(CC) $(LDFLAGS) -o $@ $^ $(LIBS)

doc:	$(PROGS:=.ps)

%.ps:	%.c
	a2ps -Ma4 -1 -o $@ $<
#	a2ps -Ma4 -1 --sides=duplex -o $@ $<
