.SUFFIXES: .c .o

src=$(wildcard *.c ./src/*.c)
obj=$(patsubst %.c, %.o, $(src))

Targetfile=fdfs_test 

fdfs_test=fdfs_test


all:$(Targetfile)

WORKDIR=.

CC=gcc
INCLDIR=$(WORKDIR)/incl
INCLFLAGE=-I$(WORKDIR)/incl 

#-I/usr/include/fastfdfs -I/usr/include/fastcommon

CFLAGE=$(INCLFLAGE) -c -Wall -g

VPATH=$(WORKDIR)/src

#$(Targetfile):fdfs_test.o   
#$(CC) $< -o $@

$(fdfs_test):fdfs_test.o make_log.o
	$(CC) $^ -o $@



.c.o:
	$(CC) $(CFLAGE) $<    


.PHONY:clean

clean:
	-rm -rf *.o
	-rm -rf $(Targetfile) 



