/* Library implements client and server side functions */
#ifndef __FTP_H__
#define __FTP_H__

#include "netlib.h"

#define USAGE		"ftp> <client-cmd> [<cmd-arg>]"
#define UTERM		"ftp>"

/* max payload recieved from a chunk of a file */
#define MAXPAY	512

/* pkt struct macros */
#define CMDLEN	4 		/* command length in bytes */
#define MAXARG	255 	/* max length of args */
#define PKTSIZE	(2 + (CMDLEN) + (MAXARG))

/* packet structure definition */
typedef struct __attribute__ ((packed)) 
{
		char cmd[CMDLEN]; 		/* 4 bytes		: cmd */
		uint8_t status;				/* 1 byte 		: [reply status code] */
		uint8_t arglen;				/* 1 byte 		: [length of args] */
		char arg[MAXARG];		/* 255 bytes : [cmd message] */
} packet_t;

/* creates a listening socket to be used for incomming connections */
int listensocket(int);
/* sends cmd defined in packet */
void sendcmd(int, packet_t*);
/* returns packet buffered in socket */
packet_t* recvcmd(int);
/* sends a chunk of data, returns amount of bytes sent */
int sendchunk(int, char*);
/* recieves a chunk of data, returns pointer to chunk */
char* recvchunk(int);
/* sends a whole file, returns bytes sent */
int sendfile(int, int); 
/* recieves a whole file, returns bytes recvd */
int recvfile(int); 

#endif
