#----------------------------------------------
# Allen Aboytes
# aaboytes - 1478650
# CE156 - asgn-3
# Parsa
#------------------------------------------------------------------------------
# Makefile for ftp server
#------------------------------------------------------------------------------
SERVER = ftpcli
CLIENT = ftpser

CC = gcc
CFLAGS = -Wall

FTPF = ftp
LIB = pkt

DEV = -Wno-unused-variable

all : $(CLIENT) $(SERVER)
#-----------------------------------------------------------------------------
$(CLIENT) : src/$(CLIENT).o
	$(CC) -o bin/$(CLIENT) src/$(ADT).o src/$(CLIF).o src/$(CLIENT).o $(LFLAGS)

src/$(CLIENT).o : src/$(FTPF).o
	$(CC) -c $(CFLAGS) src/$(CLIENT).c $(DEV) -o $@
#----------------------------------------------------------------------------
$(SERVER) : src/$(SERVER).o
	$(CC) -o bin/$(SERVER) src/$(SERVF).o src/$(SERVER).o

src/$(SERVER).o : src/$(FTPF).o
	$(CC) -c $(CFLAGS) src/$(SERVER).c -o $@
#----------------------------------------------------------------------------
src/$(FTPF).o :
	$(CC) -c $(CFLAGS) src/$(FTPF).c -o $@
#----------------------------------------------------------------------------
check :
	valgrind --leak-check=full bin/$(SERVER)

cleans :
	rm -f bin/$(SERVER) src/*.o

cleanc :
	rm -f bin/$(CLIENT) src/*.o

clean: cleans cleanc

