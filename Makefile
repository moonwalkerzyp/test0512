.SUFFIXES: .c .o

src=$(wildcard *.c ./src/*.c)
obj=$(patsubst %.c, %.o, $(src))

fdfs_test=test/fdfs_test
redis_api=test/redis_api
main=test/main

Targetfile=$(fdfs_test) $(redis_api) $(main)

all:$(Targetfile)

WORKDIR=.

CC=gcc
INCLDIR=$(WORKDIR)/incl
INCLFLAGE=-I$(WORKDIR)/incl -I/usr/local/include/hiredis/
LIBS=-lhiredis -lpthread

#-I/usr/include/fastfdfs -I/usr/include/fastcommon

CFLAGE=$(INCLFLAGE) -c -Wall -g

VPATH=$(WORKDIR)/src:./test

#$(Targetfile):fdfs_test.o   
#$(CC) $< -o $@

$(fdfs_test):fdfs_test.o make_log.o
	$(CC) $^ -o $@ $(LIBS)

$(redis_api):redis_api.o make_log.o
	$(CC) $^ -o $@ $(LIBS)

$(main):main.o make_log.o redis_op.o
	$(CC) $^ -o $@ $(LIBS)

.c.o:
#$(obj):%.o:%.c
	$(CC) $(CFLAGE) $<    


.PHONY:clean

clean:
	-rm -rf *.o
	-rm -rf $(Targetfile) 



