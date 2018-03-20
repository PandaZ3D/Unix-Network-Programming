#----------------------------------------------
# Allen Aboytes
# aaboytes - 1478650
# CE156 - asgn-3
# Parsa
#------------------------------------------------------------------------------
# Makefile for ftp client and server
#------------------------------------------------------------------------------
SERVER = ftp_client
CLIENT = ftp_server

CC = gcc
CFLAGS = -Wall

FTPF = ftp

DEV = -Wno-unused-variable

all : $(CLIENT) $(SERVER)
#-----------------------------------------------------------------------------
$(CLIENT) : src/$(CLIENT).o
	$(CC) -o bin/$(CLIENT)  src/$(FTPF).o src/$(CLIENT).o $(LFLAGS)

src/$(CLIENT).o : src/$(FTPF).o
	$(CC) -c $(CFLAGS) src/$(CLIENT).c $(DEV) -o $@
#----------------------------------------------------------------------------
$(SERVER) : src/$(SERVER).o
	$(CC) -o bin/$(SERVER) src/$(FTPF).o src/$(SERVER).o

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

