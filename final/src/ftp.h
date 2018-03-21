/* Library implements client and server side functions */
#ifndef __FTP_H__
#define __FTP_H__

#include "netlib.h"

#define USAGE	"ftp> <client-cmd> [<cmd-arg>]" 	/* 29 bytes long */
#define UTERM	("ftp> ") 					/* 5 bytes long */

#define ULEN	29 /* length of usage string is 29 bytes */

/* max payload recieved from a chunk of a file */
#define MAXPAY	512

/* pkt struct macros */
#define CMDLEN	4 	/* command length in bytes */
#define MAXARG	255 	/* max length of args */
#define PKTSIZE	(2 + (CMDLEN) + (MAXARG))

/* packet structure definition */
typedef struct __attribute__ ((packed)) 
{
		char cmd[CMDLEN]; 		/* 4 bytes	: cmd */
		uint8_t status;			/* 1 byte 	: [reply status code] */
		uint8_t arglen;			/* 1 byte	: [length of args] */
		char arg[MAXARG];		/* 255 bytes 	: [cmd message] */
} packet_t;

/* returns a generic TCP socket with custum options for debugging */
int setsocket(void);
/* creates a listening socket to be used for incomming connections */
int listensocket(int);
/* creates packet based on arguments */
packet_t* cmdpkt(int, char*, char*, uint8_t, uint8_t);
/* sends cmd defined in packet */
void sendcmd(int, packet_t*);
/* returns packet buffered in socket */
packet_t* recvcmd(int);
/* sends a chunk of data, returns amount of bytes sent */
int sendchunk(int, char*, int);
/* recieves a chunk of data, returns pointer to chunk */
int recvchunk(int, char*);
/* sends a whole file, returns bytes sent */
int sendfile(int, int); 
/* recieves a whole file, returns bytes recvd */
int recvfile(int, int);
/* function to do port calculation, returns struct with info */
socklen_t parseport(packet_t*, struct sockaddr_in*);
/* frees allocated packet struct */
void freepkt(packet_t*);
/* generic printf funciton for packets */
void printpkt(packet_t*);
 
#endif
